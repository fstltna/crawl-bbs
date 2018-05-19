#pragma once

enum seen_context_type
{
    SC_NONE,
    SC_JUST_SEEN,       // has already been announced this turn
    SC_NEWLY_SEEN,      // regular walking into view
    SC_ALREADY_SEEN,    // wasn't a threat before, is now
    SC_TELEPORT_IN,
    SC_FISH_SURFACES,                 // water/lava-only
    SC_NONSWIMMER_SURFACES_FROM_DEEP, // impossible?!?
    SC_UNCHARM,
    SC_DOOR,            // they opened a door
    SC_GATE,            // ... or a big door
    SC_LEAP_IN,         // leaps into view
    SC_UPSTAIRS,        // comes up the stairs
    SC_DOWNSTAIRS,      // comes down the stairs
    SC_ARCH,            // through the gate
    SC_ABYSS,           // abyss creation
    SC_THROWN_IN,       // thrown into view from the monster throw ability
};
