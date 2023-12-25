#include "head.h"


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
