#pragma once
#include"head.h"
class Attack
{
public:
	int attack_propertys_mr=Mental; //��������1(��ʵ�����񡢱�Դ)
	int attack_propertys_rt= Ritual;  //��������2(��ʽ������)
	int attack_card = 0;		  //�˺�Դ��������
	int attack = 1;				 //�˺�
	NPC* come_from=nullptr;//�˺���Դ
	std::vector<NPC*> come_to; //������
	Attack() { std::vector<NPC*> come_to; };

};

