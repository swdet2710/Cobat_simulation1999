#include "World.h"

void World::add_NPC(NPC*npc)
{
    my_world.push_back(npc);
    //time_npc++;
    npc->world = this;
}

void World::combat_readiness()
{

    std::vector<NPC*>::iterator f = my_world.begin();
    while (f != my_world.end())
    {
        (*f)->combat_readiness();
        f++;
    } 
}

void World::by_timepass()
{
    std::vector<NPC*>::iterator f = my_world.begin();
    while (f != my_world.end())
    {
        
        (*f)->by_timepass();
        f++;
        
    } 
    f = my_world.begin();

    while (f != my_world.end())
    {
        
        if ((*f)->live <= 0)
        {
            std::cout << (*f)->get_name() << "已经阵亡\n";
            my_world.erase(f);
            f = my_world.begin();
            continue;
        }
        f++;
    } 
    
}

void World::by_timebegin()
{
    std::vector<NPC*>::iterator f = my_world.begin();
    
    while (f != my_world.end())
    {
        (*f)->by_timebegin();
        f++;
    } 
}

void World::init()
{
    handtiles = new HandTiles(*this,max_npc);
    combat_readiness();
}

CardBase* World::request_card()
{
    NPC* user = my_world[get_randomss() % my_world.size()];
    return user->skills[get_randomss() % (user->skills.size() - 1)]->clone(); // 除去大招
}

NPC* World::select_sub_target(World*enemies,NPC* main_t)
{
    if (enemies->my_world.size() <= 1) {
        return nullptr;
    }
    while (true) {
        int index = rand() % enemies->my_world.size();
        if (enemies->my_world[index] != main_t) {
            return enemies->my_world[index];
        }
    }
}