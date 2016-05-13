//
// Created by SEIAROTg on 5/7/16.
//

#ifndef MATCHSTICK_DESTRUCT_H
#define MATCHSTICK_DESTRUCT_H

namespace _matchstick_destruct {

    using namespace _matchstick;

    void destruct_fsm_match(FSM_MATCH *match);
    void destruct_fsm_rule(FSM_RULE *rule);
    void destruct_fsm_transition(FSM_TRANSITION *transition);
    void destruct_fsm_state(FSM_STATE *state);

}
#endif //MATCHSTICK_DESTRUCT_H
