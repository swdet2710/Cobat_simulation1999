#pragma once
#include"head.h"
class Attack
{
public:
	int attack_propertys_mr=Mental; //攻击属性1(现实、精神、本源)
	int attack_propertys_rt= Ritual;  //攻击属性2(仪式、术法)
	int attack_card = 0;		  //伤害源卡的种类
	int attack = 1;				 //伤害
	NPC* come_from=nullptr;//伤害来源
	std::vector<NPC*> come_to; //作用者
	Attack() { std::vector<NPC*> come_to; };

};

