#include <stdlib.h>

#include "types_private.h"
#include "matchstick.h"
#include "destruct.h"

void ms_destruct_fsm_match (struct MS_FSM_MATCH * match) {
    struct MS_FSM_MATCH * cursor = match;
    struct MS_FSM_MATCH * previous;
    while (cursor) {
        previous = cursor;
        cursor = cursor -> next_match;
        free(previous);
    }
}

void ms_destruct_fsm_rule (struct MS_FSM_RULE * rule) {
    if (rule -> type == MS_FSM_RULE_INCLUDE || rule -> type == MS_FSM_RULE_EXCLUDE) {
        struct MS_FSM_RULE_MATCH * real_rule = (struct MS_FSM_RULE_MATCH *) rule;
        ms_destruct_fsm_match(real_rule -> first_match);
    } else if (rule -> type == MS_FSM_RULE_COUNTER) {
        struct MS_FSM_RULE_COUNTER * real_rule = (struct MS_FSM_RULE_COUNTER *) rule;
        free(real_rule -> counter);
        free(real_rule);
    }
}

void ms_destruct_fsm_transition (struct MS_FSM_TRANSITION * transition) {
    struct MS_FSM_TRANSITION * cursor = transition;
    struct MS_FSM_TRANSITION * previous;
    while (cursor) {
        previous = cursor;
        cursor = cursor -> next_transition;
        ms_destruct_fsm_rule(previous -> rule);
        ms_destruct_fsm_state(previous -> next_state);
        free(previous);
    }
}

void ms_destruct_fsm_state (struct MS_FSM_STATE * state) {
    if (state) {
        struct MS_FSM_TRANSITION * first_transition = state -> first_transition;
        free(state);
        ms_destruct_fsm_transition(first_transition);
    }
}

void ms_destruct_pattern (MS_REGEX * pattern) {
    struct MS_REGEX * real_pattern = (struct MS_REGEX *) pattern;
    ms_destruct_fsm_state(real_pattern -> first_state);
}
