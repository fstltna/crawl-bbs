#pragma once

enum description_level_type
{
    DESC_THE,
    DESC_A,
    DESC_YOUR,
    DESC_PLAIN,
    DESC_ITS,
    DESC_INVENTORY_EQUIP,
    DESC_INVENTORY,

    // Partial item names.
    DESC_BASENAME,                     // Base name of item subtype
    DESC_QUALNAME,                     // Name without articles, quantities,
                                       // enchantments.
    DESC_DBNAME,                       // Name with which to look up item
                                       // description in the db.

    DESC_NONE
};
