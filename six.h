#pragma once

#include "NPC.h"
#include "card_detail.h"

class Six: public NPC
{
public:
    Six(): NPC("6")
    {
        // load_property();
        set_skills({new SixOne(1.0), new SixTwo(1.0, 5), new SixRitual(1.0, 6)});
    }
};