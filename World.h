#pragma once
#include "NPC.h"
#include "card_handtiles.h"
typedef struct __law {
    int socre=0;    //分数
    int socreofway[4] = {0,0,0,0};      //加分规则
    CardBase* one =nullptr;    //律的小技能
    CardBase* two = nullptr;   //律的大技能
}law;
class World
{
    void use_one_card();
public:
    std::vector<NPC*> my_world;  //我方队伍列表
    HandTiles *handtiles = nullptr; //手牌
    World* enemie =nullptr;//敌方
    law* my_law = nullptr; //律
    buff* world_buff = nullptr;     //我方场景buff
    int max_npc; //最大上阵角色，除此之外还有替补
    //int time_npc = 0; //实时角色数量
    void(*p)(World* self,World* enemies) = nullptr; //选牌函数
    //int round_cnt = 0;
    void add_NPC(NPC*); //添加角色
    void combat_readiness(); //游戏开始初始化
    void by_timepass(); //回合结束时触发
    void by_timebegin(); //回合开始时判定
    NPC* select_sub_target(World*enemies,NPC* main_t);//设定额外目标
    World(int max_npcs) {
        max_npc = max_npcs;
        
    };
    ~World() {
        if (handtiles != nullptr)
            delete handtiles;
    }
    void init(void(*p)(World* self, World* enemies));
    CardBase* request_card();
    void use_card();
};

