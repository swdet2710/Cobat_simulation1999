#pragma once
#include "NPC.h"
#include "card_handtiles.h"
typedef struct __law {
    int socre=0;    //分数
    int socreofway[4];      //加分规则
    CardBase* one =nullptr;    //律的小技能
    CardBase* two = nullptr;   //律的大技能
}law;
class World
{
public:
    vector<NPC*> my_world;  //我方队伍列表
    HandTiles* handtiles = nullptr; //手牌
    law my_law; //律
    buff* world_buff = nullptr;     //我方场景buff
    int max_npc = 1; //最大上阵角色，除此之外还有替补
    int time_npc = 0; //实时角色数量
    vector<NPC*>(*p)(World*self, World* enemies); //选牌函数
    //int round_cnt = 0;
    void add_NPC(NPC*);
    int combat_readiness(); //游戏开始初始化
    void by_timepass(); //回合结束时触发
    void by_timebegin(); //回合开始时判定
    ~World() {
        if (handtiles != nullptr)
            delete handtiles;
    }
    void init(World self);
    CardBase* request_card();
};

