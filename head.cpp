
#include "head.h"
void* npc_attack=nullptr; //攻击者
void* npc_beattack=nullptr; //受攻击者
std::random_device rd;
std::minstd_rand0 get_randomss(rd());//初始化随机数

void loop_bufflist(buff*& bufflist, onset passby)
{
	buff* before, **now;
	for (now = &bufflist, before = NULL; (*now) != NULL; )
	{
		
		if ((*now)->passby == passby ||passby == onset::Alawys)
		{
			(*now)->sum--;
				
			if ((*now)->sum == 0)
				remove_from_bufflist((*now), before);
		}
		before = (*now);
		if ((*now))
			now = &(*now)->next;
	}
}

void loop_bufflist_functions(buff*& bufflist, onset passby)
{
	buff* before, **now;
	for (now = &bufflist, before = NULL; (*now) != NULL; )
	{
		if ((*now)->functions == passby || passby == onset::Alawys)
			if ((*now)->p != NULL)
			{
				(*now)->p((*now));
				if ((*now)->sum == 0)
					remove_from_bufflist((*now), before);
			}
		before = (*now);
		if ((*now))
			now = &(*now)->next;
	}
}


void remove_from_bufflist(buff* &bufflist, buff* before_bufflist)
{
	if (before_bufflist != NULL)
		before_bufflist->next = bufflist->next;
	delete bufflist;
	if (before_bufflist == NULL)
		bufflist = NULL;
}

void add_to_bufflist(buff*& bufflist, buff* buffself)
{
	if (bufflist == NULL)
		bufflist = buffself;
	else
		for (buff* i = bufflist,*j=NULL; i != NULL; j=i,i = i->next)
		{
			if (i->id == buffself->id)
			{
				
				if (buffself->result > i->result || buffself->s_result == i->s_result)
				{
					buffself->next = i->next;
					if (j)
					{
						j->next = buffself;
						
					}
					else
						bufflist = buffself;
					delete i;
					return;
				}
				else if (buffself->result == i->result && buffself->s_result == i->s_result)
					if(buffself->sum>i->sum)
					{
						
						buffself->next = i->next;
						if (j)
						{
							j->next = buffself;
							
						}
						else
							bufflist = buffself;
						delete i;
						return;
					}
			}
			
			if (i->next == NULL)
			{
				i->next = buffself;
				i = i->next;
				return;
			}if (i->next == NULL)
			{
				i->next = buffself;
				i = i->next;
				return;
			}
		}
			

}
