#pragma once

#include<iostream>
#include<random>
#include <fstream>
using namespace std;

#define Technique 1 //术法
#define Ritual 0 //仪式
#define Orgin 2 //本源
#define Realistic 1 //现实
#define Mental 0 //精神
#define Sum_property 19 //属性数量-1

//#define Tree 0 //木
//#define Animal 1 //兽
//#define Stone 2 //岩
//#define Star 3 //星
//#define	Quick 7 //灵
//#define Wisdom 17 //智
enum fnpc_propertys{ Tree, Animal, Stone, Star, Quick = 10, Wisdom };

extern void* npc_attack; //攻击者
extern void* npc_beattack; //受攻击者
extern random_device rd;
extern minstd_rand0 get_randomss;//初始化随机数


typedef struct __property {
	fnpc_propertys npc_property = Quick; //角色系 0
	float attack = 0; //攻击 1
	float life = 0; //生命上限 2
	float realistic_defense = 0; //现实防御 3
	float mental_defense = 0; //精神防御 4 
	float penetration_rate = 0; //穿透率 5
	float critical_chance = 0; //暴击率 注：应该设成小数 6
	float crit_damage = 0; //暴击创伤 注：应该设成小数 7
	float crit_resist_rate = 0; //抗暴率 注：应该设成小数 8
	float crit_defense = 0; //暴击防御 注：应该设成小数 9
	float trauma_addition = 0; //创伤加成 10
	float trauma_relief = 0; //受创减免 11
	float power_technique = 0; //术法威力 12
	float power_ritual = 0; //仪式威力 13
	float treatment_rate = 0; //治疗率 14
	float untreatment_rate = 0; //减疗率 15
	float leech_rate = 0; //吸血率 16
	float trauma_recovery = 0; //受创回复 17
	float power_orgin = 0; //本源伤害加成 18
	float coefficient = 1; //比例系数 19
	/*struct __property copy()
	{
		struct __property a;
		a.npc_property = npc_property;
		a.attack = attack;
		a.life = life;
		a.realistic_defense = realistic_defense;
		a.mental_defense = mental_defense;
		a.penetration_rate = penetration_rate;
		a.critical_chance = critical_chance;
		a.crit_damage = crit_damage;
		a.crit_resist_rate = crit_resist_rate;
		a.crit_defense = crit_defense;
		a.trauma_addition = trauma_addition;
		a.trauma_relief = trauma_relief;
		a.power_technique = power_technique;
		a.power_ritual = power_ritual;
		a.treatment_rate = treatment_rate;
		a.untreatment_rate = untreatment_rate;
		a.leech_rate = leech_rate;
		a.trauma_recovery = trauma_recovery;
		a.power_orgin = power_orgin;
		return a;
	}*/
}property;

union fproperty {
	property *fpropertys;
	float *p;
	fproperty(property* __fproperty) { fpropertys = __fproperty; p = &(__fproperty->attack); };
};

enum class onset{Not,Begin,After};
typedef struct __buff {
	int sum = 0; //层数
	int id = 0; //用于检索。
	int propertys = 0; //标记作用的属性,0代表不更改
	onset functions = onset::Not; //用于标记函数发动回合（1代表回合开始，2代表回合结束，其他表示不发动）
	onset passby = onset::After; //用于标记掉层方法
	float result = 0.0f; //以数值方式修改指定的属性值
	float s_result = 1.0f; //以百分比方式修改指定的属性值
	void (*p)(struct __buff* self) = NULL; //特殊效果函数，请使用全局变量中的当前伤害者和被伤害者确定使用者和被使用者
	struct __buff* next = NULL;
}buff;

void remove_from_bufflist(buff* bufflist, buff* before_bufflist);
void add_to_bufflist(buff*& bufflist, buff* buffself);

//typedef struct __card {
//	string name; //卡牌名字
//	void (*p)(NPC); //卡牌效果指针
//}card;
