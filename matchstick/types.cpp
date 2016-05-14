#include "types.h"


namespace _matchstick {

    FSM_MATCH::FSM_MATCH(enum FSM_MATCH_TYPE type) : type(type), next_match(NULL) {}

    FSM_MATCH_BASIC::FSM_MATCH_BASIC(enum FSM_MATCH_TYPE type) : FSM_MATCH(type) {};

    FSM_MATCH_EXACT::FSM_MATCH_EXACT(MS_CHAR const value) : FSM_MATCH(FSM_MATCH_TYPE_EXACT), value(value) {};

    FSM_MATCH_STRING::FSM_MATCH_STRING(MS_CHAR * const value) : FSM_MATCH(FSM_MATCH_TYPE_STRING), value(value) {};

    FSM_MATCH_STRING::~FSM_MATCH_STRING() {
        delete [] value;
    };

    FSM_MATCH_RANGE::FSM_MATCH_RANGE(MS_CHAR lower_bound, MS_CHAR upper_bound) :
            FSM_MATCH(FSM_MATCH_TYPE_RANGE),
            lower_bound(lower_bound),
            upper_bound(upper_bound)
    {};

    FSM_RULE::FSM_RULE(enum FSM_RULE_TYPE type) : type(type) {};

    FSM_RULE_BASIC::FSM_RULE_BASIC(enum FSM_RULE_TYPE type, struct FSM_MATCH *first_match) :
        FSM_RULE(type),
        first_match(first_match)
    {};

    FSM_RULE_BASIC::~FSM_RULE_BASIC() {
        if (first_match) {
            delete first_match;
        }
    }

    FSM_RULE_COUNTER::FSM_RULE_COUNTER(struct FSM_COUNTER *counter) :
            FSM_RULE(FSM_RULE_TYPE_COUNTER),
            counter(counter)
    {};

    FSM_RULE_COUNTER::~FSM_RULE_COUNTER()  {
        if (counter) {
            delete counter;
        }
    }

    FSM_COUNTER::FSM_COUNTER(enum FSM_COUNTER_TYPE type, enum FSM_COUNTER_MODE mode, unsigned int id) :
            type(type),
            mode(mode),
            id(id)
    {};

    FSM_COUNTER_ANY::FSM_COUNTER_ANY(enum FSM_COUNTER_MODE mode, unsigned int id) :
            FSM_COUNTER(FSM_COUNTER_TYPE_ANY, mode, id)
    {};

    FSM_COUNTER_EXACT::FSM_COUNTER_EXACT(enum FSM_COUNTER_MODE mode, unsigned int id, unsigned int value) :
            FSM_COUNTER(FSM_COUNTER_TYPE_EXACT, mode, id),
            value(value)
    {};

    FSM_COUNTER_MIN::FSM_COUNTER_MIN(enum FSM_COUNTER_MODE mode, unsigned int id, unsigned int min) :
            FSM_COUNTER(FSM_COUNTER_TYPE_MIN, mode, id),
            min(min)
    {};

    FSM_COUNTER_MAX::FSM_COUNTER_MAX(enum FSM_COUNTER_MODE mode, unsigned int id, unsigned int max) :
            FSM_COUNTER(FSM_COUNTER_TYPE_MAX, mode, id),
            max(max)
    {};

    FSM_COUNTER_RANGE::FSM_COUNTER_RANGE(enum FSM_COUNTER_MODE mode, unsigned int id, unsigned int min, unsigned int max) :
            FSM_COUNTER(FSM_COUNTER_TYPE_RANGE, mode, id),
            min(min),
            max(max)
    {};

    FSM_TRANSITION::FSM_TRANSITION(struct FSM_RULE *rule, struct FSM_STATE *next_state) :
            rule(rule),
            next_state(next_state),
            next_transition(NULL)
    {};

    FSM_TRANSITION::~FSM_TRANSITION()  {
        // The state pointed to by a counter increase rule should have been deleted elsewhere
        if (next_state &&
            !(
                    rule &&
                    rule -> type == FSM_RULE_TYPE_COUNTER &&
                    static_cast<FSM_RULE_COUNTER *> (rule) -> counter -> type == FSM_COUNTER_TYPE_INCREASE
            )
                ) {
            delete next_state;
        }
        if (rule) {
            delete rule;
        }
        if (next_transition) {
            delete next_transition;
        }
    }

    FSM_STATE::FSM_STATE() : first_transition(NULL) {};

    FSM_STATE::~FSM_STATE() {
        if (first_transition) {
            delete first_transition;
        }
    }

    REGEX::REGEX(struct FSM_STATE *first_state, unsigned int num_of_counters) :
            first_state(first_state),
            num_of_counters(num_of_counters)
    {};
    REGEX::~REGEX() {
        if (first_state) {
            delete first_state;
        }
    }

    MS_CHARS::MS_CHARS(MS_CHAR value) : value(value), next(NULL) {};

}
