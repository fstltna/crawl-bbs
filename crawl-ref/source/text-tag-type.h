#pragma once

// Ordering of tags is important: higher values cover up lower ones.
enum text_tag_type
{
    TAG_NAMED_MONSTER = 0,
    TAG_TUTORIAL      = 1,
    TAG_CELL_DESC     = 2,
    TAG_MAX,
};
