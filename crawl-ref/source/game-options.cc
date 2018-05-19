/*
 *  @file
 *  @brief Global game options controlled by the rcfile.
 */

#include "AppHdr.h"

#include "game-options.h"
#include "options.h"
#include "misc.h"
#include "tiles-build-specific.h"

static unsigned _curses_attribute(const string &field, string &error)
{
    if (field == "standout")               // probably reverses
        return CHATTR_STANDOUT;
    if (field == "bold")              // probably brightens fg
        return CHATTR_BOLD;
    if (field == "blink")             // probably brightens bg
        return CHATTR_BLINK;
    if (field == "underline")
        return CHATTR_UNDERLINE;
    if (field == "reverse")
        return CHATTR_REVERSE;
    if (field == "dim")
        return CHATTR_DIM;
    if (starts_with(field, "hi:")
        || starts_with(field, "hilite:")
        || starts_with(field, "highlight:"))
    {
        const int col = field.find(":");
        const int colour = str_to_colour(field.substr(col + 1));
        if (colour != -1)
            return CHATTR_HILITE | (colour << 8);

        error = make_stringf("Bad highlight string -- %s",
                             field.c_str());
    }
    else if (field != "none")
        error = make_stringf("Bad colour -- %s", field.c_str());
    return CHATTR_NORMAL;
}

/**
 * Read a maybe bool field. Accepts anything for the third value.
 */
maybe_bool read_maybe_bool(const string &field)
{
    // TODO: check for "maybe" explicitly or something?
    if (field == "true" || field == "1" || field == "yes")
        return MB_TRUE;

    if (field == "false" || field == "0" || field == "no")
        return MB_FALSE;

    return MB_MAYBE;
}

bool read_bool(const string &field, bool def_value)
{
    const maybe_bool result = read_maybe_bool(field);
    if (result != MB_MAYBE)
        return tobool(result, false);

    Options.report_error("Bad boolean: %s (should be true or false)", field.c_str());
    return def_value;
}


void BoolGameOption::reset() const { value = default_value; }

string BoolGameOption::loadFromString(string field, rc_line_type) const
{
    string error;
    const maybe_bool result = read_maybe_bool(field);
    if (result == MB_MAYBE)
    {
        return make_stringf("Bad %s value: %s (should be true or false)",
                            name().c_str(), field.c_str());
    }

    value = tobool(result, false);
    return "";
}

void ColourGameOption::reset() const { value = default_value; }

string ColourGameOption::loadFromString(string field, rc_line_type) const
{
    const int col = str_to_colour(field, -1, true, elemental);
    if (col == -1)
        return make_stringf("Bad %s -- %s\n", name().c_str(), field.c_str());

    value = col;
    return "";
}

void CursesGameOption::reset() const { value = default_value; }

string CursesGameOption::loadFromString(string field, rc_line_type) const
{
    string error;
    const unsigned result = _curses_attribute(field, error);
    if (!error.empty())
        return make_stringf("%s (for %s)", error.c_str(), name().c_str());

    value = result;
    return "";
}

#ifdef USE_TILE
TileColGameOption::TileColGameOption(VColour &val, std::set<std::string> _names,
                    string _default)
        : GameOption(_names), value(val),
          default_value(str_to_tile_colour(_default)) { }

void TileColGameOption::reset() const { value = default_value; }

string TileColGameOption::loadFromString(string field, rc_line_type) const
{
    value = str_to_tile_colour(field);
    return "";
}
#endif

void IntGameOption::reset() const { value = default_value; }

string IntGameOption::loadFromString(string field, rc_line_type) const
{
    int val = default_value;
    if (!parse_int(field.c_str(), val))
        return make_stringf("Bad %s: \"%s\"", name().c_str(), field.c_str());
    if (val < min_value)
        return make_stringf("Bad %s: %d < %d", name().c_str(), val, min_value);
    if (val > max_value)
        return make_stringf("Bad %s: %d > %d", name().c_str(), val, max_value);
    value = val;
    return "";
}

void StringGameOption::reset() const { value = default_value; }

string StringGameOption::loadFromString(string field, rc_line_type) const
{
    value = field;
    return "";
}

void ColourThresholdOption::reset() const { value = default_value; }

string ColourThresholdOption::loadFromString(string field,
                                             rc_line_type ltyp) const
{
    string error;
    const colour_thresholds result = parse_colour_thresholds(field, &error);
    if (!error.empty())
        return error;

    switch (ltyp)
    {
        case RCFILE_LINE_EQUALS:
            value = result;
            break;
        case RCFILE_LINE_PLUS:
        case RCFILE_LINE_CARET:
            value.insert(value.end(), result.begin(), result.end());
            stable_sort(value.begin(), value.end(), ordering_function);
            break;
        case RCFILE_LINE_MINUS:
            for (pair<int, int> entry : result)
                remove_matching(value, entry);
            break;
        default:
            die("Unknown rc line type for %s: %d!", name().c_str(), ltyp);
    }
    return "";
}

colour_thresholds
    ColourThresholdOption::parse_colour_thresholds(string field,
                                                   string* error) const
{
    colour_thresholds result;
    for (string pair_str : split_string(",", field))
    {
        const vector<string> insplit = split_string(":", pair_str);

        if (insplit.size() != 2)
        {
            const string failure = make_stringf("Bad %s pair: '%s'",
                                                name().c_str(),
                                                pair_str.c_str());
            if (!error)
                die("%s", failure.c_str());
            *error = failure;
            break;
        }

        const int threshold = atoi(insplit[0].c_str());

        const string colstr = insplit[1];
        const int scolour = str_to_colour(colstr, -1, true, false);
        if (scolour <= 0)
        {
            const string failure = make_stringf("Bad %s: '%s'",
                                                name().c_str(),
                                                colstr.c_str());
            if (!error)
                die("%s", failure.c_str());
            *error = failure;
            break;
        }

        result.push_back({threshold, scolour});
    }
    stable_sort(result.begin(), result.end(), ordering_function);
    return result;
}
