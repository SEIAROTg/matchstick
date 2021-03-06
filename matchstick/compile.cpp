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

    const MS_CHAR pick_char(MS_CHAR **cursor, int in_charset) {
        MS_CHAR *pos;
        if (in_charset) {
            pos = wcsrchr(INVALID_CHAR_CHARSET, **cursor);
        } else {
            pos = wcsrchr(INVALID_CHAR_N_CHARSET, **cursor);
        }
        if (pos) {
            return (MS_CHAR) 0;
        } else {
            MS_CHAR ret;
            MS_CHAR *temp_cursor = *cursor;
            ret = pick_escaped_char(&temp_cursor, in_charset);
            if (temp_cursor == *cursor) {
                ++*cursor;
                return *temp_cursor;
            } else {
                *cursor = temp_cursor;
                return ret;
            }
        }
    }

    MS_CHAR * const pick_string(MS_CHAR **cursor) {
        MS_CHAIN<MS_CHAR> chars;
        MS_CHAR picked_char;
        MS_CHAR *temp_cursor = *cursor;
        do {
            *cursor = temp_cursor;
            picked_char = pick_char(&temp_cursor, 0);
            if (temp_cursor != *cursor) {
                chars.push(picked_char);
            }
        } while (temp_cursor != *cursor);
        if (chars.size) {
            chars.push('\0');
            return chars.to_array();
        } else {
            return NULL;
        }
    }

    FSM_MATCH * const pick_range_match(MS_CHAR **cursor) {
        MS_CHAR * temp_cursor = *cursor;
        MS_CHAR min = pick_char(&temp_cursor, 1);
        MS_CHAR max;
        if (temp_cursor == *cursor || *temp_cursor != '-' || *temp_cursor == ']') {
            return NULL;
        } else {
            // to avoid CLion from thinking temp_cursor == temp_cursor2 to be always true
            MS_CHAR * temp_cursor2 = temp_cursor + 1;
            ++temp_cursor;
            if (*temp_cursor == ']') {
                return NULL;
            } else {
                max = pick_char(&temp_cursor2, 1);
                if (temp_cursor == temp_cursor2) {
                    return NULL;
                } else {
                    *cursor = temp_cursor2;
                    FSM_MATCH_RANGE *match = new FSM_MATCH_RANGE(min, max);
                    return static_cast<FSM_MATCH *> (match);
                }
            }
        }
    }

    // assumed to be in charset
    FSM_MATCH * const pick_char_match(MS_CHAR **cursor) {
        MS_CHAR * temp_cursor = *cursor;
        MS_CHAR c = pick_char(&temp_cursor, 1);
        if (temp_cursor == *cursor) {
            return NULL;
        } else {
            FSM_MATCH_EXACT * match = new FSM_MATCH_EXACT(c);
            return static_cast<FSM_MATCH *> (match);
        }
    }

    FSM_RULE * const pick_charset(MS_CHAR **cursor) {
        FSM_RULE_TYPE rule_type;
        FSM_RULE_BASIC * rule;
        FSM_MATCH * first_match = NULL;
        FSM_MATCH * match_cursor = NULL;
        if (**cursor != '[') {
            return NULL;
        } else {
            ++*cursor;
            if (**cursor == '^') {
                ++*cursor;
                rule_type = FSM_RULE_TYPE_EXCLUDE;
            } else {
                rule_type = FSM_RULE_TYPE_INCLUDE;
            }
            MS_CHAR * temp_cursor;
            FSM_MATCH * match;
            while (**cursor != ']') {
                match = NULL;
                temp_cursor = *cursor;
                if (temp_cursor == *cursor) {
                    match = pick_range_match(cursor);
                }
                if (temp_cursor == *cursor) {
                    match = pick_char_match(cursor);
                }
                if (!match) {
                    if (first_match) {
                        delete first_match;
                    }
                    return NULL;
                } else {
                    if (match_cursor) {
                        match_cursor->next_match = match;
                        match_cursor = match_cursor->next_match;
                    } else {
                        match_cursor = match;
                        first_match = match;
                    }
                }
            }
            if (first_match) {
                rule = new FSM_RULE_BASIC(rule_type, first_match);
                return static_cast<FSM_RULE *> (rule);
            } else {
                return NULL;
            }
        }
    }
    unsigned int pick_number(MS_CHAR **cursor) {
        if (**cursor < '0' || **cursor > '9') {
            return INVALID_NUM;
        } else {
            unsigned int num = 0;
            while (**cursor >= '0' && **cursor <= '9') {
                num *= 10;
                num += **cursor - '0';
                ++*cursor;
            }
            return num;
        }
    }

    enum FSM_COUNTER_MODE pick_counter_mode(MS_CHAR **cursor) {
        switch (**cursor) {
            case '?':
                ++*cursor;
                return FSM_COUNTER_MODE_RELUCTANT;
                break;
            case '+':
                ++*cursor;
                return FSM_COUNTER_MODE_POSSESSIVE;
                break;
            default:
                return FSM_COUNTER_MODE_GREEDY;
        }
    }

    FSM_COUNTER *pick_counter(MS_CHAR **cursor, unsigned int *counter_cursor) {
        FSM_COUNTER * counter = NULL;
        if (**cursor == '*') {
            // any
            ++*cursor;
            counter = static_cast<FSM_COUNTER *> (
                    new FSM_COUNTER_ANY(pick_counter_mode(cursor), *counter_cursor++)
            );
        } else if (**cursor == '?') {
            // zero or one
            ++*cursor;
            counter = static_cast<FSM_COUNTER *> (
                    new FSM_COUNTER_RANGE(pick_counter_mode(cursor), *counter_cursor++, 0, 1)
            );
        } else if (**cursor == '+') {
            // one or more
            ++*cursor;
            counter = static_cast<FSM_COUNTER *> (
                    new FSM_COUNTER_MIN(pick_counter_mode(cursor), *counter_cursor++, 1)
            );
        } else if (**cursor == '{') {
            MS_CHAR *temp_cursor = *cursor;
            ++temp_cursor;
            unsigned int min = pick_number(&temp_cursor);
            if (min != INVALID_NUM && *temp_cursor == '}') {
                // exact
                *cursor = temp_cursor + 1;
                counter = static_cast<FSM_COUNTER *> (
                        new FSM_COUNTER_EXACT(pick_counter_mode(cursor), *counter_cursor++, min)
                );
            } else if (*temp_cursor == ',') {
                unsigned int max = pick_number(&temp_cursor);
                if (*temp_cursor == '}') {
                    if (min != INVALID_NUM && max != INVALID_NUM) {
                        // range
                        *cursor = temp_cursor + 1;
                        counter = static_cast<FSM_COUNTER *> (
                                new FSM_COUNTER_RANGE(pick_counter_mode(cursor), *counter_cursor++, min, max)
                        );
                    } else if (min != INVALID_NUM) {
                        // min
                        *cursor = temp_cursor + 1;
                        counter = static_cast<FSM_COUNTER *> (
                                new FSM_COUNTER_MIN(pick_counter_mode(cursor), *counter_cursor++, min)
                        );
                    } else if (max != INVALID_NUM) {
                        // max
                        *cursor = temp_cursor + 1;
                        counter = static_cast<FSM_COUNTER *> (
                                new FSM_COUNTER_MAX(pick_counter_mode(cursor), *counter_cursor++, max)
                        );
                    }
                }
            }
        }
        return counter;
    }
    using namespace _matchstick;

}
