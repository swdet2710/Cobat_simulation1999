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
	World one(1), two(1);
	int i = 1;
	Six six1, six2, six3;
	one.add_NPC(&six1);
	two.add_NPC(&six2);

	one.init(human_card_gui);
	two.init(human_card_gui);
	
	//add_to_bufflist(six1.bufflist_timepass, gettestbuff(i++)); //测试角色回合buff是否正常
	//add_to_bufflist(six1.bufflist_timepass, t); //测试角色回合buff是否正常
	
	while (one.my_world.size() && two.my_world.size())
	{
		// draw cards
		one.handtiles->draw();
		two.handtiles->draw();

		//six1.live = 0;  //测试角色阵亡是否有效
		one.by_timebegin();
		two.by_timebegin();
		one.p(&one, &two);
		// two.p(&two, &one);
		//if (six1.npc_propertys.attack != 251)
		//	std::cout << six1.npc_propertys.attack<< '\n';
		//else
		//	break;

		one.by_timepass();
		two.by_timepass();
	}
	
	//std::cout << six1.npc_propertys.attack;
}