#ifndef MATCHSTICK_TYPES_PRIVATE_H
#define MATCHSTICK_TYPES_PRIVATE_H

#include "types.h"

namespace _matchstick {

    using namespace matchstick;

    enum FSM_MATCH_TYPE {
        FSM_MATCH_TYPE_EXACT,         // a
        FSM_MATCH_TYPE_RANGE,         // a-z
        FSM_MATCH_TYPE_START,         // ^
        FSM_MATCH_TYPE_END,           // $
        FSM_MATCH_TYPE_ANY,           // .
        FSM_MATCH_TYPE_DIGIT,         // \d
        FSM_MATCH_TYPE_SPACE,         // \s
        FSM_MATCH_TYPE_WORD,          // \w
        FSM_MATCH_TYPE_BOUNDARY,      // \b
        FSM_MATCH_TYPE_NONDIGIT,      // \D
        FSM_MATCH_TYPE_NONSPACE,      // \S
        FSM_MATCH_TYPE_NONWORD,       // \W
        FSM_MATCH_TYPE_NONBOUNDARY,   // \B
    };

    struct FSM_MATCH {
        enum FSM_MATCH_TYPE type;
        struct FSM_MATCH *next_match;
    };

    struct FSM_MATCH_EXACT : public FSM_MATCH {
        MS_CHAR value;
    };

    struct FSM_MATCH_RANGE : public FSM_MATCH {
        MS_CHAR lower_bound;
        MS_CHAR upper_bound;
    };

    enum FSM_RULE_TYPE {
        FSM_RULE_TYPE_INCLUDE,
        FSM_RULE_TYPE_EXCLUDE,
        FSM_RULE_TYPE_COUNTER,
    };

    struct FSM_RULE {
        enum FSM_RULE_TYPE type;
    };

    struct FSM_RULE_MATCH : public FSM_RULE {
        struct FSM_MATCH *first_match;
    };

    struct FSM_RULE_COUNTER : public FSM_RULE {
        struct FSM_COUNTER *counter;
    };

    enum FSM_COUNTER_TYPE {
        FSM_COUNTER_TYPE_INCREASE,
        FSM_COUNTER_TYPE_ANY,         // *
        FSM_COUNTER_TYPE_NONZERO,     // +
        FSM_COUNTER_TYPE_ZEROONE,     // ?
        FSM_COUNTER_TYPE_EXACT,       // {10}
        FSM_COUNTER_TYPE_MAX,         // {,10}
        FSM_COUNTER_TYPE_MIN,         // {10,}
        FSM_COUNTER_TYPE_RANGE,       // {10,20}
    };

    struct FSM_COUNTER {
        enum FSM_COUNTER_TYPE type;
        unsigned int id;
    };

    struct FSM_COUNTER_VALUE : public FSM_COUNTER {
        unsigned int value;
    };

    struct FSM_COUNTER_RANGE : public FSM_COUNTER {
        unsigned int min;
        unsigned int max;
    };

    struct FSM_TRANSITION {
        struct FSM_RULE *rule;
        struct FSM_STATE *next_state;
        struct FSM_TRANSITION *next_transition;
    };

    struct FSM_STATE {
        struct FSM_TRANSITION *first_transition;
    };

    struct REGEX {
        struct FSM_STATE *first_state;
        unsigned int num_of_counters;
    };
}

#endif //MATCHSTICK_TYPES_PRIVATE_H
