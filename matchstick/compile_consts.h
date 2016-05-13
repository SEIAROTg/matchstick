namespace _matchstick_compile {

    const MS_CHAR *SPECIAL_MATCH = L"^$.";
    const enum FSM_MATCH_TYPE SPECIAL_MATCH_TYPE[] = {
            FSM_MATCH_TYPE_START,
            FSM_MATCH_TYPE_END,
            FSM_MATCH_TYPE_ANY,
    };

}
