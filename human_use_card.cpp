#include"human_use_card.h"
#include "toml/value.hpp"

#include <cstdlib>
#include <algorithm>
#include <fstream>
#include <system_error>
#include <toml.hpp>

void human_card(World* self, World* enemies) {
	std::vector<NPC*>::iterator f = self->my_world.begin();
	int i = 0, change = 1,choose;
	std::cout << "我方角色列表：";
	while (f != self->my_world.end())
	{
		std::cout << i << "-" << (*f)->get_name() << "  ";
		f++; i++;
	}
	std::cout << "\n敌方角色列表：";
	f = enemies->my_world.begin();
	while (f != enemies->my_world.end())
	{
		std::cout << i << "-" << (*f)->get_name() << "  ";
		f++; i++;
	}
	std::cout << "\n手牌概览：" << self->handtiles->summary() << std::endl;
	std::cin >> choose;
}

NPC* find_user(CardBase *tile, const std::vector<NPC*> &users)
{
	for(auto user: users) {
		for(auto card: user->skills) {
			if(card->get_id() == tile->get_id()) {
				return user;
			}
		}
	}
	return nullptr;
}

void human_card_gui(World *self, World *enemies)
{
	// pass situation
	std::string sit_fname = "temp/situation.toml";
	std::string result_fname = "temp/result.toml";

	toml::array ally(self->my_world.size());
	std::transform(
		self->my_world.begin(), self->my_world.end(), ally.begin(),
		[](NPC *npc) { return npc->get_name(); }
	);
	toml::array enemy(enemies->my_world.size());
	std::transform(
		enemies->my_world.begin(), enemies->my_world.end(), enemy.begin(),
		[](NPC *npc) { return npc->get_name(); }
	);
	toml::array tiles, levels;
	self->handtiles->dump_tiles(tiles, levels);

	const toml::value sit_data {
		{ "ally", {
			{ "team", ally }
		} },
		{ "enemy", {
			{ "team", enemy }
		} },
		{ "handtiles", {
			{ "rhythm", { 0, 0, 50 } }, // TODO
			{ "num_actions", self->my_world.size() }, // TODO: it's a bug
			{ "tiles", tiles },
			{ "levels", levels }
		} }
	};

	std::ofstream sit_file(sit_fname);
	assert(sit_file.good());
	sit_file << sit_data;
	sit_file.close();

	// write default result (failing)
	toml::value fail_result { { "ok", false } };
	std::ofstream result_out(result_fname);
	assert(result_out.good());
	result_out << fail_result;
	result_out.close();

	// call gui
	int res = std::system(("python frontend/human_card_gui.py " + sit_fname + " " + result_fname).c_str());
	assert(res == 0);

	// read result
	auto result = toml::parse(result_fname);
	assert(result["ok"].as_boolean());

	for(auto op: result["operations"].as_array()) {
		std::string op_type = op["type"].as_string();
		if(op_type == "choose") {
			int index = op["index"].as_integer();
			int main_t = op["to"].as_integer();
			self->handtiles->choose(index, self->my_world[main_t]); // TODO: handle skills targeting allies
		} else if(op_type == "move") {
			continue; // TODO
		} else if(op_type == "rhythm_shuffle") {
			continue; // TODO
		} else if(op_type == "rhythm_promote") {
			continue; // TODO
		}
	}

	auto chosen = self->handtiles->discharge();
	for(auto op: chosen) {
		CardBase *tile = op.first;
		NPC *t = op.second;
		NPC *user = find_user(tile, self->my_world);
		if(user == nullptr) {
			continue;
		}
		tile->use(*self, *user, *t);
		// world->post_use(tile, t);

		delete tile;
	}
}