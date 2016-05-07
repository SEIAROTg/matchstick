#include "matchstick.h"

int ms_test (const MS_CHAR * pattern, const MS_CHAR * str, const char * flags) {
    MS_REGEX * compiled_pattern = ms_compile_pattern(pattern, flags);
    int ret = ms_test_compiled(compiled_pattern, str);
    ms_destruct_pattern(compiled_pattern);
    return ret;
}

int ms_search (const MS_CHAR * pattern, MS_CHAR ** str, const char * flags) {
    MS_REGEX * compiled_pattern = ms_compile_pattern(pattern, flags);
    int ret = ms_search_compiled(compiled_pattern, str);
    ms_destruct_pattern(compiled_pattern);
    return ret;
}

MS_MATCH * ms_match (const MS_CHAR * pattern, const MS_CHAR * str, const char * flags) {
    MS_REGEX * compiled_pattern = ms_compile_pattern(pattern, flags);
    MS_MATCH * ret = ms_match_compiled(compiled_pattern, str);
    ms_destruct_pattern(compiled_pattern);
    return ret;
}
