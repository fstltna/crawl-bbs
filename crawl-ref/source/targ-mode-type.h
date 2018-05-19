#pragma once

enum targ_mode_type
{
    TARG_ANY,
    TARG_FRIEND,
    TARG_INJURED_FRIEND, // for healing
    TARG_HOSTILE,
    TARG_HOSTILE_SUBMERGED, // Target hostiles including submerged ones
    TARG_EVOLVABLE_PLANTS,  // Targeting mode for Fedhas' evolution
    TARG_BEOGH_GIFTABLE,    // For Beogh followers who can be given gifts
    TARG_MOVABLE_OBJECT,    // Movable objects only
    TARG_MOBILE_MONSTER,    // Non-stationary monsters
    TARG_NUM_MODES
};
