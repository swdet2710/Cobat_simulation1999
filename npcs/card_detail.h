#pragma once

#include "card.h"

// 6的技能组
class SixOne: public CardBase
{
    std::vector<buff> debuffs = {}; // TODO
    float scale;
public:
    SixOne(float _scale, int _level=1)
    : CardBase(1, "6::律与戒", "六1", _level, CardType::Debuff),
      scale(_scale)
    { }
    SixOne* clone() override { return new SixOne(*this); }

    void use(World& world, NPC& user, NPC& main_t) override;
};

class SixTwo: public CardBase
{
    std::vector<buff> buffs = {}; // TODO
    float scale;
    int bri_thresh; // 消耗灵光赋予咒语强化的阈值
public:
    SixTwo(float _scale, int _bri_thresh, int _level=1)
    : CardBase(2, "6::职与责", "六2", _level, CardType::Buff),
      scale(_scale), bri_thresh(_bri_thresh)
    { }
    SixTwo* clone() override { return new SixTwo(*this); }

    void use(World& world, NPC& user, NPC& main_t) override;
};

class SixRitual: public CardBase
{
    float scale;
    int bri_thresh; // 消耗灵光的阈值
public:
    SixRitual(float _scale, int _bri_thresh)
    : CardBase(3, "6::亘古亘今的启示", "六大", 3, CardType::Special),
      scale(_scale), bri_thresh(_bri_thresh)
    { }
    SixRitual* clone() override { return new SixRitual(*this); }

    void use(World& world, NPC& user, NPC& main_t) override;
};
