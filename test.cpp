#include "temp.h"
void* npc_attack = NULL; //攻击者
void* npc_beattack = NULL; //受攻击者
random_device rd;
minstd_rand0 get_randomss(rd());//初始化随机数
int main()
{
    World world;
    world.Init();
    world.Loop();
    return 0;
}