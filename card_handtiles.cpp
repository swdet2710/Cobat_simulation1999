#include "card_handtiles.h"
#include "World.h"

CardBase* HandTiles::request_card()
{
    return world.request_card();
}

int HandTiles::choose(int index, NPC *main_t)
{
    if(chosen.size() >= world.my_world.size()) {
        return -2;
    }
    if(index < 0 || index >= tiles.size()) {
        return -1;
    }
    chosen.emplace_back(tiles[index], main_t);
    tiles.erase(tiles.begin() + index);
    check_merge(index - 1);
    return chosen.size();
}

std::string HandTiles::summary()
{
    std::stringstream ss;

    ss << "Chosen:";
    for(auto c: chosen) {
        ss << '\t' << c.first->get_short_name();
    }
    ss << '\n';
    
    ss << "Tiles:";
    for(int i = 0; i < tiles.size(); ++i) {
        ss << '\t' << i << '.' << tiles[i]->get_short_name();
    }
    ss << '\n';
    ss << "Level:";
    for(auto tile: tiles) {
        ss << '\t' << tile->get_level();
    }

    return ss.str();
}

void HandTiles::check_merge(int index)
{
    if(index < 0 || index >= tiles.size() - 1) {
        return;
    }

    int level1 = tiles[index]->get_level();
    int level2 = tiles[index+1]->get_level();
    if(!(level2 == 1 || level2 == 2)) { // 必须是1阶或2阶的正常卡
        return;
    }
    if(tiles[index]->get_id() == tiles[index + 1]->get_id()) { // 正常合成
        if(level1 != level2) { // 阶数不同不可合成
            return;
        }
    } else if(level2 == 0) { // 特殊合成
        switch(tiles[index+1]->get_id()) {
        // case ??: // 律的调校
        //     if(level1 == 1) {
        //         break;
        //     } else {
        //         return;
        //     }
        // case ??: // 伟大乐队
        //     break;
        default:
            return;
        }
    } else {
        return;
    }

    // 可合成
    tiles[index]->set_level(level1+1);
    delete tiles[index+1]; tiles.erase(tiles.begin() + index + 1);
    check_merge(index);
}