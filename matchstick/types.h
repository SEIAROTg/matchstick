#ifndef MATCHSTICK_TYPES_H
#define MATCHSTICK_TYPES_H

#include "matchstick.h"

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
        const enum FSM_MATCH_TYPE type;
        struct FSM_MATCH *next_match;
        FSM_MATCH(enum FSM_MATCH_TYPE type);
        virtual ~FSM_MATCH() {
            if (next_match) {
                delete next_match;
            }
        }
    };

    struct FSM_MATCH_BASIC : public FSM_MATCH {
        FSM_MATCH_BASIC(enum FSM_MATCH_TYPE type);
    };

    struct FSM_MATCH_EXACT : public FSM_MATCH {
        MS_CHAR * const value;
        FSM_MATCH_EXACT(MS_CHAR *value);
        ~FSM_MATCH_EXACT();
    };

    struct FSM_MATCH_RANGE : public FSM_MATCH {
        const MS_CHAR lower_bound;
        const MS_CHAR upper_bound;
        FSM_MATCH_RANGE(MS_CHAR lower_bound, MS_CHAR upper_bound);
    };

    enum FSM_RULE_TYPE {
        FSM_RULE_TYPE_INCLUDE,
        FSM_RULE_TYPE_EXCLUDE,
        FSM_RULE_TYPE_COUNTER,
    };

    struct FSM_RULE {
        const enum FSM_RULE_TYPE type;
        FSM_RULE(enum FSM_RULE_TYPE type);
        virtual ~FSM_RULE() {};
    };

    struct FSM_RULE_BASIC : public FSM_RULE {
        struct FSM_MATCH * const first_match;
        FSM_RULE_BASIC(enum FSM_RULE_TYPE type, struct FSM_MATCH *first_match);
        ~FSM_RULE_BASIC();
    };

    struct FSM_RULE_COUNTER : public FSM_RULE {
        struct FSM_COUNTER * const counter;
        FSM_RULE_COUNTER(struct FSM_COUNTER *counter);
        ~FSM_RULE_COUNTER();
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
        const enum FSM_COUNTER_TYPE type;
        const unsigned int id;
        FSM_COUNTER(enum FSM_COUNTER_TYPE type, unsigned int id);
        virtual ~FSM_COUNTER() {};
    };

    struct FSM_COUNTER_BASIC : public FSM_COUNTER {
        FSM_COUNTER_BASIC(enum FSM_COUNTER_TYPE type, unsigned int id);
    };

    struct FSM_COUNTER_EXACT : public FSM_COUNTER {
        const unsigned int value;
        FSM_COUNTER_EXACT(unsigned int id, unsigned int value);
    };

    struct FSM_COUNTER_MIN : public FSM_COUNTER {
        const unsigned int min;
        FSM_COUNTER_MIN(unsigned int id, unsigned int min);
    };

    struct FSM_COUNTER_MAX : public FSM_COUNTER {
        const unsigned int max;
        FSM_COUNTER_MAX(unsigned int id, unsigned int max);
    };

    struct FSM_COUNTER_RANGE : public FSM_COUNTER {
        const unsigned int min;
        const unsigned int max;
        FSM_COUNTER_RANGE(unsigned int id, unsigned int min, unsigned int max);
    };

    struct FSM_TRANSITION {
        struct FSM_RULE * const rule;
        struct FSM_STATE * const next_state;
        struct FSM_TRANSITION *next_transition;
        FSM_TRANSITION(struct FSM_RULE *rule, struct FSM_STATE *next_state);
        ~FSM_TRANSITION();
    };

    struct FSM_STATE {
        struct FSM_TRANSITION *first_transition;
        FSM_STATE();
        ~FSM_STATE();
    };

    struct REGEX {
        struct FSM_STATE * const first_state;
        const unsigned int num_of_counters;
        REGEX(struct FSM_STATE *first_state, unsigned int num_of_counters);
        ~REGEX();
    };

    struct MS_CHARS {
        const MS_CHAR value;
        struct CHAR_CHAIN *next;
        MS_CHARS(MS_CHAR value);
    };
}

#endif //MATCHSTICK_TYPES_H
