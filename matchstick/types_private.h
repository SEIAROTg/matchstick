#ifndef MATCHSTICK_TYPES_PRIVATE_H
#define MATCHSTICK_TYPES_PRIVATE_H

#include "types.h"

enum MS_FSM_MATCH_TYPE {
    MS_FSM_MATCH_EXACT,         // a
    MS_FSM_MATCH_RANGE,         // a-z
    MS_FSM_MATCH_START,         // ^
    MS_FSM_MATCH_END,           // $
    MS_FSM_MATCH_ANY,           // .
    MS_FSM_MATCH_DIGIT,         // \d
    MS_FSM_MATCH_SPACE,         // \s
    MS_FSM_MATCH_WORD,          // \w
    MS_FSM_MATCH_BOUNDARY,      // \b
    MS_FSM_MATCH_NONDIGIT,      // \D
    MS_FSM_MATCH_NONSPACE,      // \S
    MS_FSM_MATCH_NONWORD,       // \W
    MS_FSM_MATCH_NONBOUNDARY,   // \B
};

struct MS_FSM_MATCH {
    enum MS_FSM_MATCH_TYPE type;
    struct MS_FSM_MATCH * next_match;
};

struct MS_FSM_MATCH_EXACT {
    enum MS_FSM_MATCH_TYPE type;
    struct MS_FSM_MATCH * next_match;
    MS_CHAR value;
};

struct MS_FSM_MATCH_RANGE {
    enum MS_FSM_MATCH_TYPE type;
    struct MS_FSM_MATCH * next_match;
    MS_CHAR lower_bound;
    MS_CHAR upper_bound;
};

enum MS_FSM_RULE_TYPE {
    MS_FSM_RULE_INCLUDE,
    MS_FSM_RULE_EXCLUDE,
    MS_FSM_RULE_COUNTER,
};

struct MS_FSM_RULE {
    enum MS_FSM_RULE_TYPE type;
};

struct MS_FSM_RULE_MATCH {
    enum MS_FSM_RULE_TYPE type;
    struct MS_FSM_MATCH * first_match;
};

struct MS_FSM_RULE_COUNTER {
    enum MS_FSM_RULE_TYPE type;
    struct MS_FSM_COUNTER * counter;
};

enum MS_FSM_COUNTER_TYPE {
    MS_FSM_COUNTER_INCREASE,
    MS_FSM_COUNTER_ANY,         // *
    MS_FSM_COUNTER_NONZERO,     // +
    MS_FSM_COUNTER_ZEROONE,     // ?
    MS_FSM_COUNTER_EXACT,       // {10}
    MS_FSM_COUNTER_MAX,         // {,10}
    MS_FSM_COUNTER_MIN,         // {10,}
    MS_FSM_COUNTER_RANGE,       // {10,20}
};

struct MS_FSM_COUNTER {
    enum MS_FSM_COUNTER_TYPE type;
    unsigned int id;
};

struct MS_FSM_COUNTER_VALUE {
    enum MS_FSM_COUNTER_TYPE type;
    unsigned int id;
    unsigned int value;
};

struct MS_FSM_COUNTER_RANGE {
    enum MS_FSM_COUNTER_TYPE type;
    unsigned int id;
    unsigned int min;
    unsigned int max;
};

struct MS_FSM_TRANSITION {
    struct MS_FSM_RULE * rule;
    struct MS_FSM_STATE * next_state;
    struct MS_FSM_TRANSITION * next_transition;
};

struct MS_FSM_STATE {
    struct MS_FSM_TRANSITION * first_transition;
};

struct MS_REGEX {
    struct MS_FSM_STATE * first_state;
    unsigned int num_of_counters;
};

#endif //MATCHSTICK_TYPES_PRIVATE_H
