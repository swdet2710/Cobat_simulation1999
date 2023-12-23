#pragma once
#include "card.h"
#include "head.h"
#include <fstream>
#include <array>
class NPC
{
public:
	string name;
	int brightness; //灵光
	float live; //剩余生命
	buff shield; //护盾
	property init_npc_propertys; //初始角色属性
	property npc_propertys; //每回合时角色属性
	buff *bufflist_timepass; //回合buff
	buff*bufflist_workpass; //消耗buff
	buff* debufflist_timepass; //回合debuff
	buff* debufflist_workpass; //消耗debuff
	std::array<CardBase*, 3> skills; // 技能组

	NPC(string names) {
		name = names;
		bufflist_timepass = new buff[100];
		bufflist_workpass = new buff[100];
		debufflist_timepass = new buff[100];
		debufflist_workpass = new buff[100];
	}

	int combat_readiness(); //游戏开始初始化

	int load_property(); //从文件载入角色信息

	float attacks(float attack,property&opponent,int attack_property); //攻防项计算

	float health(float attack,float scale); //未暴击的治疗计算（攻击或损失血量，倍率）

	float atack(float attack, float scale,property& opponent,int attack_property,int attack_way); //攻击计算（攻击，倍率,对方面板,法术属性，释放属性）

	float critical_check(property& opponent); //攻击暴击运算

	float health_critical_check(); //治疗暴击运算

	void set_skills(std::array<CardBase*, 3> _skills) { skills = _skills; }

};

