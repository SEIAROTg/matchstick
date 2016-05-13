#include "types_private.h"
#include "matchstick.h"
#include "destruct.h"

namespace _matchstick_destruct {

    using namespace _matchstick;

    void destruct_fsm_match(FSM_MATCH *match) {
        FSM_MATCH *cursor = match;
        FSM_MATCH *previous;
        while (cursor) {
            previous = cursor;
            cursor = cursor->next_match;
            delete previous;
        }
    }

    void destruct_fsm_rule(FSM_RULE *rule) {
        if (rule->type == FSM_RULE_TYPE_INCLUDE || rule->type == FSM_RULE_TYPE_EXCLUDE) {
            FSM_RULE_MATCH *real_rule = (FSM_RULE_MATCH *) rule;
            destruct_fsm_match(real_rule->first_match);
        } else if (rule->type == FSM_RULE_TYPE_COUNTER) {
            FSM_RULE_COUNTER *real_rule = (FSM_RULE_COUNTER *) rule;
            delete real_rule->counter;
            delete real_rule;
        }
    }

    void destruct_fsm_transition(FSM_TRANSITION *transition) {
        FSM_TRANSITION *cursor = transition;
        FSM_TRANSITION *previous;
        while (cursor) {
            previous = cursor;
            cursor = cursor->next_transition;
            destruct_fsm_rule(previous->rule);
            destruct_fsm_state(previous->next_state);
            delete previous;
        }
    }

    void destruct_fsm_state(FSM_STATE *state) {
        if (state) {
            FSM_TRANSITION *first_transition = state->first_transition;
            delete state;
            destruct_fsm_transition(first_transition);
        }
    }

}

namespace matchstick {

    void destruct_pattern(PATTERN *pattern) {

        using namespace _matchstick_destruct;

        REGEX *real_pattern = (struct REGEX *) pattern;
        destruct_fsm_state(real_pattern->first_state);

    }

}

