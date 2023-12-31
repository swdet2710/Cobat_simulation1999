#pragma once
#include "card.h"
#include "head.h"
struct Passion
{
	int passion=0;
	int max_passion = 5;
	Passion operator+(int a)
	{
		passion += a;
		if (passion > max_passion)
			passion = max_passion;
		return *this;
	}
};

class NPC
{
private:
	std::string name;
	property init_npc_propertys; //初始角色属性
	int load_property(); //从文件载入角色信息
	
	
	void buff_attack(); //攻击时触发
	float attacks(float attack, property& opponent, int attack_property); //攻防项计算
	float critical_check(property& opponent); //攻击暴击运算
public:
	NPC(std::string names) {
		name = names;
		load_property();
	}
	~NPC() {
		buff* next;
		if(bufflist_timepass!=NULL)
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
	}
	int brightness; //灵光
	int passion;	//激情
	float live; //剩余生命
	buff shield; //护盾
	World* world=nullptr;//阵营
	
	property npc_propertys; //每回合时角色属性
	buff *bufflist_timepass = NULL; //回合buff
	buff* bufflist_byattack = NULL; //受到攻击后buff
	buff* bufflist_attack = NULL; //攻击后buff

	std::array<CardBase*, 3> skills; // 技能组，0 1为一二技能，2为大招

	std::string get_name() const { return name; }
	void set_skills(std::array<CardBase*, 3> _skills) { skills = _skills; }

	int combat_readiness(); //游戏开始初始化

	void buff_to_property(); //刷新属性

	void use_to_attack(NPC* opponent, void (*p)(), int sum_of_opponent = 1); //攻击时调用

	void by_timepass(); //回合结束时触发
	void by_attack(); //受到攻击时触发
	void by_timebegin(); //回合开始时判定

	float health(float attack,float scale); //未暴击的治疗计算（攻击或损失血量，倍率）

	float atack(float attack, float scale,property& opponent,int attack_property,int attack_way); //攻击计算（攻击，倍率,对方面板,法术属性，释放属性）

	float health_critical_check(); //治疗暴击运算

};

