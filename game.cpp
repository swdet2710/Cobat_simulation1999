#include "World.h"
#include "./npcs/six.h"
void* npc_attack; //������
void* npc_beattack; //�ܹ�����
random_device rd;
minstd_rand0 get_randomss(rd());//��ʼ�������
int main()
{
	World mine;
	Six six;
	mine.add_NPC(&six);

}