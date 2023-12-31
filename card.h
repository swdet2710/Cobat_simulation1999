#pragma once

#include "head.h"


enum class CardType
{
    Attack,
    Buff,
    Debuff,
    Heal,
    Counter,
    Special, // 律的调校，UTTU特殊卡，仪式（待定）
};

class CardBase
{
protected:
    int id;
    std::string name, short_name; // 卡牌名称，简称
    int level; // 阶数，有特殊合成效果的卡为0，大招等不可合成的卡为3
    bool can_be_use = true;  //标记卡牌是否被无效
    CardType type;
    NPC * main_t=nullptr; //卡牌的主要目标
    NPC * owner = NULL; //卡牌拥有者
public:
    int UsingWay = 0; //0指代仅可对敌方使用，1代表仅可对己方，其它为任意
    int get_id() { return id; }
    void set_use(bool t) { can_be_use = t; }
    std::string get_name() { return name; }
    std::string get_short_name() { return short_name; }
    int get_level() { return level; }
    void set_level(int _level) { level = _level; }
    CardType get_type() { return type; }

    CardBase() = delete;
    CardBase(int _id, std::string _name, std::string _short_name, int _level, CardType _type)
    : id(_id), name(_name), short_name(_short_name), level(_level), type(_type)
    { }
    virtual ~CardBase() = default;
    virtual CardBase* clone() = 0; // 用于备份手牌状态

    virtual void use(World& world, NPC& user, NPC& main_t) = 0; //定向Buff卡的主目标main_t为友方
};