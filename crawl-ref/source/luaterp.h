#pragma once

#include "clua.h"
#include "dlua.h"

void debug_terp_dlua(CLua &vm = dlua);
bool luaterp_running();
