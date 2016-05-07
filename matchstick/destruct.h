//
// Created by SEIAROTg on 5/7/16.
//

#ifndef MATCHSTICK_DESTRUCT_H
#define MATCHSTICK_DESTRUCT_H

void ms_destruct_fsm_match (struct MS_FSM_MATCH * match);
void ms_destruct_fsm_rule (struct MS_FSM_RULE * rule);
void ms_destruct_fsm_transition (struct MS_FSM_TRANSITION * transition);
void ms_destruct_fsm_state (struct MS_FSM_STATE * state);

#endif //MATCHSTICK_DESTRUCT_H
