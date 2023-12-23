
#include "head.h"

class NPC
{
public:
	string name;
	int brightness; //灵光
	float live; //剩余生命
	buff shield; //护盾
	property init_npc_propertys; //初始角色属性
	property npc_propertys; //每回合时角色属性
	buff *bufflist_timepass = NULL; //回合buff
	//buff*bufflist_workpass; //消耗buff
	buff* bufflist_attack = NULL; //受到攻击时buff
	//buff* debufflist_timepass; //回合debuff
	//buff* debufflist_workpass; //消耗debuff
	//buff* debufflist_attack; //受到攻击时debuff
	NPC(string names) {
		name = names;
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
	}

	int combat_readiness(); //游戏开始初始化

	int load_property(); //从文件载入角色信息

	void buff_to_property(); //刷新属性

	void by_attack(NPC self,NPC opponent); //受到攻击时触发

	void by_timepass(); //回合结束时触发

	void by_timebegin(); //回合开始时判定

	float attacks(float attack,property&opponent,int attack_property); //攻防项计算

	float health(float attack,float scale); //未暴击的治疗计算（攻击或损失血量，倍率）

	float atack(float attack, float scale,property& opponent,int attack_property,int attack_way); //攻击计算（攻击，倍率,对方面板,法术属性，释放属性）

	float critical_check(property& opponent); //攻击暴击运算

	float health_critical_check(); //治疗暴击运算

};

