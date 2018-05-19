#pragma once

#include "char-set-type.h"
#include "dungeon-char-type.h"
#include "dungeon-feature-type.h"

void init_char_table(char_set_type set);

dungeon_char_type get_feature_dchar(dungeon_feature_type feat);
char32_t dchar_glyph(dungeon_char_type dchar);

string stringize_glyph(char32_t glyph);

dungeon_char_type dchar_by_name(const string &name);
