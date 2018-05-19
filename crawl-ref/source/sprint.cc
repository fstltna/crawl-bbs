#include "AppHdr.h"

#include "sprint.h"

#include "religion.h"

int sprint_modify_exp(int exp)
{
    return exp * SPRINT_MULTIPLIER;
}

int sprint_modify_exp_inverse(int exp)
{
    return div_rand_round(exp, SPRINT_MULTIPLIER);
}

int sprint_modify_piety(int piety)
{
    // usk is tactical, oka gives bonus piety for scary monsters (all of them)
    if (you_worship(GOD_OKAWARU) || you_worship(GOD_USKAYAW))
        return piety;

    if (you_worship(GOD_ASHENZARI)
        || you_worship(GOD_NEMELEX_XOBEH)
        || you_worship(GOD_HEPLIAKLQANA)
        || you_worship(GOD_RU))
    {
        return piety * SPRINT_MULTIPLIER * 3; // exploration piety
    }

    return piety * SPRINT_MULTIPLIER;
}
