#pragma once

enum beh_type
{
    BEH_SLEEP,
    BEH_WANDER,
    BEH_SEEK,
    BEH_FLEE,
    BEH_CORNERED,                      //  wanting to flee, but blocked by an
                                       //  obstacle or monster
#if TAG_MAJOR_VERSION == 34
    BEH_PANIC,                         //  like flee but without running away
    BEH_LURK,                          //  stay still until discovered or
                                       //  enemy close by
#endif
    BEH_RETREAT,                       //  like flee but when cannot attack
    BEH_WITHDRAW,                      //  an ally given a command to withdraw
                                       //  (will not respond to attacks)
    NUM_BEHAVIOURS,                    //  max # of legal states
    BEH_CHARMED,                       //  hostile-but-charmed; creation only
    BEH_FRIENDLY,                      //  used during creation only
    BEH_GOOD_NEUTRAL,                  //  creation only
    BEH_STRICT_NEUTRAL,
    BEH_NEUTRAL,                       //  creation only
    BEH_HOSTILE,                       //  creation only
    BEH_GUARD,                         //  creation only - monster is guard
    BEH_COPY,                          //  creation only - copy from summoner
};
