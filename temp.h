#pragma once

// 暂时用于测试的一些代码

#include "NPC.h"
#include "card.h"
#include "card_detail.h"
#include "card_handtiles.h"
#include "NPC_detail.h"
#include <cstdlib>
#include <iostream>

class World
{
public:
    std::vector<NPC*> enemies;
    std::vector<NPC*> friends;
    HandTiles *handtiles = nullptr;
    NPC* main_target = nullptr;
    int round_cnt = 0;

    NPC* select_sub_target(NPC *main_t)
    {
        if(enemies.size() <= 1) {
            return nullptr;
        }
        while(true) {
            int index = rand() % enemies.size();
            if(enemies[index] != main_t) {
                return enemies[index];
            }
        }
    }
    NPC* find_user(CardBase *tile)
    {
        for(auto user: friends) {
            for(auto card: user->skills) {
                if(card->get_id() == tile->get_id()) {
                    return user;
                }
            }
        }
        return nullptr;
    }

    CardBase* request_card()
    {
        NPC *user = friends[rand() % friends.size()];
        return user->skills[rand() % (user->skills.size()-1)]->clone(); // 除去大招
    }
    int get_tiles_max()
    {
        switch (friends.size()) {
        case 1:
            return 4;
        case 2:
            return 5;
        case 3:
            // TODO: 考虑候补时7张
            return 6;
        case 4:
            return 8;
        default:
            std::cerr << "Invalid friends size" << std::endl;
            exit(-1);
        }
    }
    std::vector<CardBase*> get_init_tiles()
    {
        int max_size = get_tiles_max();
        switch(max_size) {
        case 4: {
            NPC *npc = friends[0];
            return std::vector<CardBase*> {
                npc->skills[0]->clone(),
                npc->skills[1]->clone(),
                npc->skills[0]->clone(),
                npc->skills[1]->clone(),
            };
        }
        default:
            std::cerr << "Invalid max_size" << std::endl;
            exit(-1);
        }
    }

    void Init()
    {
        round_cnt = 0;
        enemies.push_back(new NPC("Enemy1"));
        enemies.push_back(new NPC("Enemy2"));
        enemies.push_back(new NPC("Enemy3"));
        main_target = enemies[0];

        friends.push_back(new Six);

        handtiles = new HandTiles(*this, get_tiles_max());

        auto tiles = get_init_tiles();
        handtiles->reset(tiles);
    }
    bool Round()
    {
        std::cout << "Round " << ++round_cnt << std::endl;
        // TODO
        // if(!is_alive(main_target)) {
        //     main_target = enemies[0];
        // }
        std::string cmd;
        while(
            (std::cout << '\n' << handtiles->summary() << "\nTimekeeper>>> " << std::flush) &&
            (std::cin >> cmd)
        ) {
            if(cmd == "target") {
                int index;
                std::cin >> index;
                if(index < 0 || index >= enemies.size()) {
                    std::cout << "Invalid index" << std::endl;
                    continue;
                }
                main_target = enemies[index];
            } else if(cmd == "choose") {
                int index;
                std::cin >> index;
                int res = handtiles->choose(index, main_target);
                if(res == -1) {
                    std::cout << "Invalid index" << std::endl;
                } else if(res == -2) {
                    std::cout << "Reach action points limit" << std::endl;
                } else {
                    std::cout << "Chosen " << res << " tiles" << std::endl;
                }
            } else if(cmd == "discharge") {
                if(handtiles->get_chosen().size() < friends.size()) {
                    std::cout << "Not enough tiles" << std::endl;
                    continue;
                }
                auto chosen = handtiles->discharge();
                for(auto c: chosen) {
                    // world->pre_use(tile, t);
                    NPC *user = find_user(c.first);
                    if(user == nullptr) {
                        continue;
                    }
                    c.first->use(*this, *user, *c.second);
                    // world->post_use(tile, t);
                }
                return true;
            } else if(cmd == "summary") {
                std::cout << handtiles->summary() << std::endl;
            } else if(cmd == "exit") {
                exit(0);
            } else {
                std::cout << "Invalid command" << std::endl;
            }
        }
        return false;
    }
    void Loop()
    {
        while(Round());
    }
};