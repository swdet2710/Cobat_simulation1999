#pragma once
#include "NPC.h"
#include "card_handtiles.h"
typedef struct __law {
    int socre=0;    //����
    int socreofway[4];      //�ӷֹ���
    CardBase* one =nullptr;    //�ɵ�С����
    CardBase* two = nullptr;   //�ɵĴ���
}law;
class World
{
public:
    vector<NPC*> my_world;  //�ҷ������б�
    HandTiles* handtiles = nullptr; //����
    law my_law; //��
    buff* world_buff = nullptr;     //�ҷ�����buff
    int max_npc = 1; //��������ɫ������֮�⻹���油
    int time_npc = 0; //ʵʱ��ɫ����
    vector<NPC*>(*p)(World*self, World* enemies); //ѡ�ƺ���
    //int round_cnt = 0;
    void add_NPC(NPC*);
    int combat_readiness(); //��Ϸ��ʼ��ʼ��
    void by_timepass(); //�غϽ���ʱ����
    void by_timebegin(); //�غϿ�ʼʱ�ж�
    ~World() {
        if (handtiles != nullptr)
            delete handtiles;
    }
    void init(World self);
    CardBase* request_card();
};

