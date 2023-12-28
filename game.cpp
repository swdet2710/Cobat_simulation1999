#include"game.h"
buff *gettestbuff(int i)
{
	buff* t = new buff;
	t->id = 0;
	t->propertys = 1;
	t->result = -float(i*10);
	t->sum = 4;
	t->next = NULL;
	return t;
}

void runs()
{
	World one, two;
	int i = 1;
	Six six1, six2, six3;
	one.add_NPC(&six1);
	two.add_NPC(&six2);

	one.init();
	two.init();
	buff* t = new buff;
	t->id = 1;
	t->propertys = 1;
	t->result = -float(i * 10);
	t->sum = 3;
	t->next = NULL;
	
	add_to_bufflist(six1.bufflist_timepass, gettestbuff(i++)); //���Խ�ɫ�غ�buff�Ƿ�����
	add_to_bufflist(six1.bufflist_timepass, t); //���Խ�ɫ�غ�buff�Ƿ�����
	
	while (one.my_world.size() && two.my_world.size())
	{
		//six1.live = 0;  //���Խ�ɫ�����Ƿ���Ч
		one.by_timebegin();
		if (six1.npc_propertys.attack != 251)
			std::cout << six1.npc_propertys.attack<< '\n';
		else
			break;
		one.by_timepass();
	}
	
	std::cout << six1.npc_propertys.attack;
}