#pragma once
#include "head.h"
void* npc_attack; //攻击者
void* npc_beattack; //受攻击者
random_device rd;
minstd_rand0 get_randomss(rd());//初始化随机数
void remove_from_bufflist(buff* bufflist, buff* before_bufflist)
{
	if (before_bufflist != NULL)
		before_bufflist->next = bufflist->next;
	delete bufflist;
}

void add_to_bufflist(buff*& bufflist, buff* buffself)
{
	if (bufflist == NULL)
		bufflist = buffself;
	else
		for (buff* i = bufflist; i != NULL; i = i->next)
			if (i->next == NULL)
			{
				i->next = buffself;
				i = i->next;
			}
}
