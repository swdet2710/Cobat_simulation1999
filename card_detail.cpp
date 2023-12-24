#include "card_detail.h"

#include "temp.h"

void SixOne::use(World& world, NPC& user, NPC& main_t)
{
    std::cout << user.get_name() << " use " << name << " on " << main_t.get_name() << std::endl;
    // if(!world.is_alive(&main_t)) {
    //     // TODO
    // }

    // 选择次要目标
    NPC *sub_t = world.select_sub_target(&main_t);

    // 造成伤害 TODO
    // user.attack()

    // 造成debuff TODO
    // main_t.add_buffs(debuffs);
    // sub_t->add_buffs(debuffs);

    // 增加灵光
    // user.set_brightness(user.get_brightness() + 1);
}

void SixTwo::use(World& world, NPC& user, NPC& main_t)
{
    std::cout << user.get_name() << " use " << name << " on " << main_t.get_name() << std::endl;
    // if(!world.is_alive(&main_t)) {
    //     // TODO
    // }

    // 造成buff TODO
    // main_t.add_buff(?);
    // main_t.add_buff(?);
    // if(user.get_brightness() >= bri_thresh) {
    //     user.set_brightness(user.get_brightness() - bri_thresh);
    //     main_t.add_buff(?);
    // }
}

void SixRitual::use(World& world, NPC& user, NPC& main_t)
{
    std::cout << user.get_name() << " use " << name << " on " << main_t.get_name() << std::endl;
    // TODO
}