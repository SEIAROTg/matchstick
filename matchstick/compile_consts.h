namespace _matchstick_compile {

    const MS_CHAR *ESCAPE = L"abtrvfne0";
    const MS_CHAR *ESCAPE_DECODED = L"\a\b\t\r\v\f\n\e\0";

    const MS_CHAR *SPECIAL_MATCH = L"^$.";
    const enum FSM_MATCH_TYPE SPECIAL_MATCH_TYPE[] = {
            FSM_MATCH_TYPE_START,
            FSM_MATCH_TYPE_END,
            FSM_MATCH_TYPE_ANY,
    };

    const MS_CHAR *SPECIAL_SLASH_MATCH = L"bdswBDSW";
    const enum FSM_MATCH_TYPE SPECIAL_SLASH_MATCH_TYPE[] = {
            FSM_MATCH_TYPE_BOUNDARY,
            FSM_MATCH_TYPE_DIGIT,
            FSM_MATCH_TYPE_SPACE,
            FSM_MATCH_TYPE_WORD,
            FSM_MATCH_TYPE_NONBOUNDARY,
            FSM_MATCH_TYPE_NONDIGIT,
            FSM_MATCH_TYPE_NONSPACE,
            FSM_MATCH_TYPE_NONWORD,
    };

}
