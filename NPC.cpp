#include "NPC.h"

int NPC::combat_readiness()
{
	free(bufflist_timepass);
	free(bufflist_workpass);
	bufflist_timepass = new buff[100];
	bufflist_workpass = new buff[100];
	debufflist_timepass = new buff[100];
	debufflist_workpass = new buff[100];
	brightness = 0;
	live = npc_propertys.life;
	shield.sum = 0;
	return 0;
}

int NPC::load_property()
{
	ifstream files;
	
	files.open(name);
	if (!files.is_open())
	{
		cout << "未找到该文件" << endl;
		return 1;
	}
	fproperty t(init_npc_propertys);
	for (int i = 0; i < Sum_property; i++)
		files >> t.p[i];
	files.close();
	return 0;
}

float NPC::attacks(float attack, property& opponent, int attack_property)
{
	float attack_sum = 0;
	switch (attack_property)
	{
	case Realistic:
		attack_sum = attack - opponent.realistic_defense * (1 - npc_propertys.penetration_rate);
		break;
	case Mental:
		attack_sum = attack - opponent.mental_defense * (1 - npc_propertys.penetration_rate);
		break;
	case Orgin:
		attack_sum = attack;
		break;
	default:
		throw "未知法术属性！！";
		break;
	}
	if (attack_sum < npc_propertys.attack * 0.1)
		attack_sum = npc_propertys.attack * 0.1;
	return attack_sum;
}

float NPC::health(float attack, float scale)
{
	return attack * (1 + npc_propertys.treatment_rate) * (1 - npc_propertys.untreatment_rate) * scale;
}

float NPC::atack(float attack, float scale, property& opponenty,int attack_property,int attack_way)
{
	float f = npc_propertys.npc_property - opponenty.npc_property;//克制计算
	float sum = 0;
	if (f == 1.0 || f == 3.0 || f == 10.0 || f == -10.0)
		f = 1.3;
	else
		f = 1.0;
	f *= attacks(attack, opponenty, attack_property);//攻防项
	sum = 1 + npc_propertys.trauma_addition - opponenty.trauma_relief;//增伤项
	if (sum < 0.3)
		sum = 0.3;
	f *= sum * scale;
	switch (attack_way)
	{
	case Orgin:
		return f * npc_propertys.power_orgin;
	case Ritual:
		return f * npc_propertys.power_ritual;
	case Technique:
		return f * npc_propertys.power_technique;
	default:
		throw "未知法术释放属性！！" ;
		break;
	}
	return f;
}

float NPC::critical_check(property& opponent)
{
	float critical_chance;
	random_device rd;
	minstd_rand0 get_randomss(rd());//初始化随机数
	critical_chance = get_randomss()%100;
	critical_chance /= 100;
	if (critical_chance < npc_propertys.critical_chance - opponent.crit_resist_rate)
	{
		critical_chance = 1 + npc_propertys.crit_damage - opponent.crit_defense;
		if (critical_chance < 1.1)
			return 1.1f;
		return critical_chance;
	}
	else
		return 1.0f;
}

float NPC::health_critical_check()
{
	float critical_chance;
	random_device rd;
	minstd_rand0 get_randomss(rd());//初始化随机数
	critical_chance = get_randomss() % 100;
	critical_chance /= 100;
	if (critical_chance < npc_propertys.critical_chance)
	{
		critical_chance = 1.0 + 0.3 * (npc_propertys.crit_damage - 1.0);
//		if (critical_chance < 1.1)
//			return 1.1f;
		return critical_chance;
	}
	else
		return 1.0f;
	return 0.0f;
}
