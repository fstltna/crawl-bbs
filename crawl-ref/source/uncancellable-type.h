#pragma once

enum uncancellable_type
{
    UNC_ACQUIREMENT,           // arg is AQ_SCROLL
    UNC_DRAW_THREE,            // arg is inv slot of the deck
    UNC_STACK_FIVE,            // arg is inv slot of the deck
#if TAG_MAJOR_VERSION == 34
    UNC_MERCENARY,             // arg is mid of the monster
#endif
    UNC_POTION_PETITION,       // arg is ignored
    UNC_CALL_MERCHANT,         // arg is ignored
};
