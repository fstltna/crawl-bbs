#pragma once

#if TAG_MAJOR_VERSION == 34
enum item_type_id_state_type
{
    ID_UNKNOWN_TYPE = 0,
    ID_MON_TRIED_TYPE,
    ID_TRIED_TYPE,
    ID_TRIED_ITEM_TYPE,
    ID_KNOWN_TYPE,
    NUM_ID_STATE_TYPES
};
#endif
