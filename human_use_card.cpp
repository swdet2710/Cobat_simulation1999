

#include"human_use_card.h"


void human_card(World* self, World* enemies) {
std::vector<NPC*>::iterator f = self->my_world.begin();
int i = 0, change = 1,choose;
std::cout << "�ҷ���ɫ�б�";
while (f != self->my_world.end())
{
	std::cout << i << "-" << (*f)->get_name() << "  ";
	f++; i++;
}
std::cout << "\n�з���ɫ�б�";
f = enemies->my_world.begin();
while (f != enemies->my_world.end())
{
	std::cout << i << "-" << (*f)->get_name() << "  ";
	f++; i++;
}
std::cout << "\n���Ƹ�����" << self->handtiles->summary() << std::endl;
std::cin >> choose;
}