#pragma once
#include "NPC.h"
#include "card_handtiles.h"
typedef struct __law {
    int socre=0;    //����
    int socreofway[4] = {0,0,0,0};      //�ӷֹ���
    CardBase* one =nullptr;    //�ɵ�С����
    CardBase* two = nullptr;   //�ɵĴ���
}law;
class World
{
public:
    std::vector<NPC*> my_world;  //�ҷ������б�
    HandTiles *handtiles = nullptr; //����
    World* enemie =nullptr;//�з�
    law my_law; //��
    buff* world_buff = nullptr;     //�ҷ�����buff
    int max_npc = 1; //��������ɫ������֮�⻹���油
    //int time_npc = 0; //ʵʱ��ɫ����
    std::vector<NPC*>(*p)(World* enemies) = nullptr; //ѡ�ƺ���
    //int round_cnt = 0;
    void add_NPC(NPC*); //��ӽ�ɫ
    void combat_readiness(); //��Ϸ��ʼ��ʼ��
    void by_timepass(); //�غϽ���ʱ����
    void by_timebegin(); //�غϿ�ʼʱ�ж�
    NPC* select_sub_target(World*enemies,NPC* main_t);//�趨����Ŀ��
    World() {};
    ~World() {
        if (handtiles != nullptr)
            delete handtiles;
    }
    void init();
    CardBase* request_card();
};

