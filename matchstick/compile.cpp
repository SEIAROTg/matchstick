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

    FSM_MATCH * const pick_special_slash_match(MS_CHAR **cursor, int in_charset) {
        FSM_MATCH *match = NULL;
        MS_CHAR *pos;
        MS_CHAR *temp_cursor = *cursor;
        if (**cursor == '\\') {
            ++temp_cursor;
            if (!(*temp_cursor == 'b' && in_charset) && (pos = wcsrchr(SPECIAL_SLASH_MATCH, **cursor))) {
                match = new FSM_MATCH_BASIC(SPECIAL_SLASH_MATCH_TYPE[pos - SPECIAL_SLASH_MATCH]);
                ++temp_cursor;
                *cursor = temp_cursor;
            }
        }
        return match;
    }

    const MS_CHAR pick_escaped_char(MS_CHAR **cursor, int in_charset) {
        MS_CHAR *pos;
        MS_CHAR *temp_cursor = *cursor;
        if (**cursor == '\\') {
            ++temp_cursor;
            if (!(*temp_cursor == 'b' && !in_charset) && (pos = wcsrchr(ESCAPE, **cursor))) {
                ++temp_cursor;
                *cursor = temp_cursor;
                return ESCAPE_DECODED[pos - ESCAPE];
            } else {
                return (MS_CHAR) 0;
            }
        } else {
            return (MS_CHAR) 0;
        }
    }
    using namespace _matchstick;

}
