#include "World.h"
#include "./npcs/six.h"
void* npc_attack; //攻击者
void* npc_beattack; //受攻击者
random_device rd;
minstd_rand0 get_randomss(rd());//初始化随机数
int main()
{
	World mine;
	Six six;
	mine.add_NPC(&six);

}