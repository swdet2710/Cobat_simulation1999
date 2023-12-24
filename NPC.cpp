
#include "NPC.h"

int NPC::combat_readiness()
{
	buff* next;
	brightness = 0;
	live = npc_propertys.life;
	shield.sum = 0;
	if (bufflist_timepass != NULL)
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
	bufflist_byattack = NULL;
	bufflist_attack = NULL;
	bufflist_timepass = NULL;
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

void NPC::buff_to_property()
{
	buff* before, * now;
	npc_propertys = init_npc_propertys;
	fproperty k(npc_propertys);
	for (now = bufflist_attack, before = NULL; now != NULL; now = now->next)
	{
		if (now->propertys)
		{
			k.p[now->propertys] = (k.p[now->propertys] + now->result) * now->s_result;
		}
	}

	for (now = bufflist_byattack, before = NULL; now != NULL; now = now->next)
	{
		if (now->propertys)
		{
			k.p[now->propertys] = (k.p[now->propertys] + now->result) * now->s_result;
		}
	}

	for (now = bufflist_timepass, before = NULL; now != NULL; now = now->next)
	{
		if (now->propertys)
		{
			k.p[now->propertys] = (k.p[now->propertys] + now->result) * now->s_result;
		}
	}
}

void NPC::use_to_attack(NPC self, NPC* opponent,void (*p)(),int sum_of_opponent=1)
{
	npc_attack = &self;
	npc_beattack = opponent;
	p();
	buff_attack();
	for (int i = 0; i < sum_of_opponent; i++)
		(opponent + i)->by_attack();

}

void NPC::by_attack()
{
	buff* before, * now;
	for (now = bufflist_byattack, before = NULL; now != NULL; now = now->next)
	{
		if (now->p!=NULL)
		{
			now->p(now);
			if (now->sum == 0)
				remove_from_bufflist(now, before);
		}
	}
}

void NPC::buff_attack()
{
	buff* before, * now;
	
	for (now = bufflist_attack, before = NULL; now != NULL; now = now->next)
	{
		if (now->p != NULL)
		{
			now->p(now);
			if (now->sum == 0)
				remove_from_bufflist(now, before);
		}
	}
}

void NPC::by_timepass()
{
	buff *before,*now;
	for (now = bufflist_timepass, before = NULL; now != NULL; now = now->next)
	{
		if(now->functions == onset::After)
			if (now->p != NULL)
			{
				now->p(now);
				if (now->sum == 0)
					remove_from_bufflist(now, before);
			}
	}

	for (now = bufflist_attack, before=NULL; now != NULL; now = now->next)
	{
		if (now->passby == onset::After)
		{
			now->sum--;
			if (now->sum == 0)
				remove_from_bufflist(now, before);
		}
		before = now;
	}
	for (now = bufflist_byattack, before = NULL; now != NULL; now = now->next)
	{
		if (now->passby == onset::After)
		{
			now->sum--;
			if (now->sum == 0)
				remove_from_bufflist(now, before);
		}
		before = now;
	}
	for (now = bufflist_timepass, before = NULL; now != NULL; now = now->next)
	{
		if (now->passby == onset::After)
		{
			now->sum--;
			if (now->sum == 0)
				remove_from_bufflist(now, before);
		}
		before = now;
	}

}

void NPC::by_timebegin()
{
	buff* before, * now;
	buff_to_property();
	for (now = bufflist_attack, before = NULL; now != NULL; now = now->next)
	{
		if (now->passby == onset::Begin)
		{
			now->sum--;
			if (now->sum == 0)
				remove_from_bufflist(now, before);
		}
		before = now;
	}
	for (now = bufflist_timepass, before = NULL; now != NULL; now = now->next)
	{
		if (now->passby == onset::Begin)
		{
			now->sum--;
			if (now->sum == 0)
				remove_from_bufflist(now, before);
		}
		before = now;
	}
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
	if (attack_sum < npc_propertys.attack * 0.1f)
		attack_sum = npc_propertys.attack * 0.1f;
	return attack_sum;
}

float NPC::health(float attack, float scale)
{
	return attack * (1 + npc_propertys.treatment_rate) * (1 - npc_propertys.untreatment_rate) * scale;
}

float NPC::atack(float attack, float scale, property& opponenty,int attack_property,int attack_way)
{
	int propertys = npc_propertys.npc_property - opponenty.npc_property;//克制计算
	float f = 1;
	float sum = 0;
	if (npc_propertys.npc_property > 4 && propertys < 0)
		propertys = -propertys;
	if (propertys == 1 || propertys == 3)
		f = 1.3f;

	f *= attacks(attack, opponenty, attack_property);//攻防项
	sum = 1 + npc_propertys.trauma_addition - opponenty.trauma_relief;//增伤项
	if (sum < 0.3f)
		sum = 0.3f;
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
	critical_chance = (float)(get_randomss()%100);
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
	critical_chance = (float)(get_randomss() % 100);
	critical_chance = critical_chance / 100.0f;
	if (critical_chance < npc_propertys.critical_chance)
	{
		critical_chance = 1.0f + 0.3f * (npc_propertys.crit_damage - 1.0f);
//		if (critical_chance < 1.1)
//			return 1.1f;
		return critical_chance;
	}
	else
		return 1.0f;
	return 0.0f;
}
