
#include "NPC.h"
#include "head.h"
#include "toml/parser.hpp"

#include <toml.hpp>


int NPC::combat_readiness()
{
	buff* next;
	brightness = 0;
	live = init_npc_propertys.life;
	shield.sum = 0;
	if (bufflist_timepass != NULL)
		for (buff* i = bufflist_timepass; i != NULL; i = next)
		{
			next = i->next;
			delete i;
		}
	if (bufflist_attack != NULL)
		for (buff* i = bufflist_attack; i != NULL; i = next)
		{
			next = i->next;
			delete i;
		}
	if (bufflist_byattack != NULL)
		for (buff* i = bufflist_byattack; i != NULL; i = next)
		{
			next = i->next;
			delete i;
		}
	bufflist_byattack = NULL;
	bufflist_attack = NULL;
	bufflist_timepass = NULL;
	return 0;
}

int NPC::load_property()
{
	auto data = toml::parse("data/NPC/" + name + ".toml"); // may throw

	auto &inp = init_npc_propertys;
	inp.npc_property = (fnpc_propertys)data["type"].as_integer();
	inp.attack = data["attack"].as_integer();
	inp.life = data["life"].as_integer();
	inp.realistic_defense = data["realistic_defense"].as_integer();
	inp.mental_defense = data["mental_defense"].as_integer();
	inp.penetration_rate = data["penetration_rate"].as_integer();
	inp.critical_chance = data["critical_chance"].as_floating();
	inp.crit_damage = data["crit_damage"].as_floating();
	inp.crit_resist_rate = data["crit_resist_rate"].as_floating();
	inp.crit_defense = data["crit_defense"].as_floating();
	inp.trauma_addition = data["trauma_addition"].as_integer();
	inp.trauma_relief = data["trauma_relief"].as_integer();
	inp.power_technique = data["power_technique"].as_integer();
	inp.power_ritual = data["power_ritual"].as_integer();
	inp.treatment_rate = data["treatment_rate"].as_integer();
	inp.untreatment_rate = data["untreatment_rate"].as_integer();
	inp.leech_rate = data["leech_rate"].as_integer();
	inp.trauma_recovery = data["trauma_recovery"].as_integer();
	inp.power_origin = data["power_origin"].as_integer();
	inp.coefficient = data["coefficient"].as_integer();

	std::cout << "NPC " << name << " 载入成功, 攻击力: " << init_npc_propertys.attack << std::endl;
	return 0;
}

void NPC::buff_to_property()
{
	buff* before, * now;
	npc_propertys = init_npc_propertys;
	fproperty k(&npc_propertys);
	for (now = bufflist_attack, before = NULL; now != NULL; now = now->next)
	{
		if (now->propertys)
		{
			k.p[now->propertys-1] = (k.p[now->propertys - 1] + now->result) * now->s_result;
		}
	}

	for (now = bufflist_byattack, before = NULL; now != NULL; now = now->next)
	{
		if (now->propertys)
		{
			k.p[now->propertys - 1] = (k.p[now->propertys - 1] + now->result) * now->s_result;
		}
	}
	for (now = bufflist_timepass, before = NULL; now != NULL; now = now->next)
	{
		if (now->propertys)
		{
			k.p[now->propertys - 1] = (k.p[now->propertys - 1] + now->result) * now->s_result;
		}
	}
}

void NPC::use_to_attack( NPC* opponent,void (*p)(),int sum_of_opponent)
{
	npc_attack = this;
	npc_beattack = opponent;
	p();
	buff_attack();
	for (int i = 0; i < sum_of_opponent; i++)
		(opponent + i)->by_attack();

}

void NPC::by_attack()
{
	loop_bufflist_functions(bufflist_byattack);
}

void NPC::buff_attack()
{
	loop_bufflist_functions(bufflist_byattack);
}

void NPC::by_timepass()
{
	loop_bufflist_functions(bufflist_timepass,onset::After);
	loop_bufflist(bufflist_attack, onset::After);
	loop_bufflist(bufflist_byattack, onset::After);
	loop_bufflist(bufflist_timepass, onset::After);
}

void NPC::by_timebegin()
{
	loop_bufflist(bufflist_attack, onset::Begin);
	loop_bufflist(bufflist_byattack, onset::Begin);
	loop_bufflist(bufflist_timepass, onset::Begin);
	loop_bufflist_functions(bufflist_timepass, onset::Begin);
	buff_to_property();
}

float NPC::attacks(float attack, property& opponent, int attack_property)
{
	float attack_sum = 0;
	switch (attack_property)
	{
	case Realistic:
		attack_sum = attack - opponent.realistic_defense * (1 - npc_propertys.penetration_rate);
		break;
	case Mental:
		attack_sum = attack - opponent.mental_defense * (1 - npc_propertys.penetration_rate);
		break;
	case Orgin:
		attack_sum = attack;
		break;
	default:
		throw "未知法术属性！！";
		break;
	}
	if (attack_sum < npc_propertys.attack * 0.1f)
		attack_sum = npc_propertys.attack * 0.1f;
	return attack_sum;
}

float NPC::health(float attack, float scale)
{
	return attack * (1 + npc_propertys.treatment_rate) * (1 - npc_propertys.untreatment_rate) * scale;
}

float NPC::atack(float attack, float scale, property& opponenty,int attack_property,int attack_way)
{
	int propertys = npc_propertys.npc_property - opponenty.npc_property;//克制计算
	float f = 1;
	float sum = 0;
	if (npc_propertys.npc_property > 4 && propertys < 0)
		propertys = -propertys;
	if (propertys == 1 || propertys == 3)
		f = 1.3f;

	f *= attacks(attack, opponenty, attack_property);//攻防项
	sum = 1 + npc_propertys.trauma_addition - opponenty.trauma_relief;//增伤项
	if (sum < 0.3f)
		sum = 0.3f;
	f *= sum * scale;
	switch (attack_way)
	{
	case Orgin:
		return f * npc_propertys.power_origin;
	case Ritual:
		return f * npc_propertys.power_ritual;
	case Technique:
		return f * npc_propertys.power_technique;
	default:
		throw "未知法术释放属性！！" ;
		break;
	}
	return f;
}

float NPC::critical_check(property& opponent)
{
	float critical_chance;
	critical_chance = (float)(get_randomss()%100);
	critical_chance /= 100;
	if (critical_chance < npc_propertys.critical_chance - opponent.crit_resist_rate)
	{
		critical_chance = 1 + npc_propertys.crit_damage - opponent.crit_defense;
		if (critical_chance < 1.1)
			return 1.1f;
		return critical_chance;
	}
	else
		return 1.0f;
}

float NPC::health_critical_check()
{
	float critical_chance;
	critical_chance = (float)(get_randomss() % 100);
	critical_chance = critical_chance / 100.0f;
	if (critical_chance < npc_propertys.critical_chance)
	{
		critical_chance = 1.0f + 0.3f * (npc_propertys.crit_damage - 1.0f);
//		if (critical_chance < 1.1)
//			return 1.1f;
		return critical_chance;
	}
	else
		return 1.0f;
	return 0.0f;
}
