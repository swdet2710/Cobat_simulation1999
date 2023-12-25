#include "World.h"

void World::add_NPC(NPC*npc)
{
    my_world.push_back(npc);
    time_npc++;
}

int World::combat_readiness()
{
    vector<NPC*>::iterator f = my_world.begin();
    do
    {
        (*f)->combat_readiness();
        f++;
    } while (f != my_world.end());
    return 0;
}

void World::by_timepass()
{
    vector<NPC*>::iterator f = my_world.begin();
    do
    {
        (*f)->by_timepass();
        f++;
    } while (f != my_world.end());

    f = my_world.begin();
    do
    {
        (*f)->by_timepass();
        if ((*f)->live <= 0)
        {
            move(f);
            f = my_world.begin();
            continue;
        }
        f++;
    } while (f != my_world.end());
}

void World::by_timebegin()
{
    vector<NPC*>::iterator f = my_world.begin();
    do
    {
        (*f)->by_timebegin();
        f++;
    } while (f != my_world.end());
}

void World::init(World self)
{
    handtiles = new HandTiles(self,time_npc);
}

CardBase* World::request_card()
{
    NPC* user = my_world[get_randomss() % my_world.size()];
    return user->skills[get_randomss() % (user->skills.size() - 1)]->clone(); // 除去大招
}