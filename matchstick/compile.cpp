#include "matchstick.h"
#include "types.h"
#include "compile.h"
#include "compile_consts.h"

namespace _matchstick_compile {

    FSM_MATCH * const pick_special_match(MS_CHAR **cursor) {
        FSM_MATCH *match = NULL;
        MS_CHAR *pos;
        if ((pos = wcsrchr(SPECIAL_MATCH, **cursor))) {
            match = new FSM_MATCH_BASIC(SPECIAL_MATCH_TYPE[pos - SPECIAL_MATCH]);
            ++*cursor;
        }
        return match;
    }
    using namespace _matchstick;

}
