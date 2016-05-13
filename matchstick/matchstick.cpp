#include "matchstick.h"

namespace matchstick {
    
    int test(const MS_CHAR *pattern, const MS_CHAR *str, const char *flags) {
        PATTERN *compiled_pattern = compile_pattern(pattern, flags);
        int ret = test(compiled_pattern, str);
        destruct_pattern(compiled_pattern);
        return ret;
    }

    int search(const MS_CHAR *pattern, MS_CHAR **str, const char *flags) {
        PATTERN *compiled_pattern = compile_pattern(pattern, flags);
        int ret = search(compiled_pattern, str);
        destruct_pattern(compiled_pattern);
        return ret;
    }

    MATCH *match(const MS_CHAR *pattern, const MS_CHAR *str, const char *flags) {
        PATTERN *compiled_pattern = compile_pattern(pattern, flags);
        MATCH *ret = match(compiled_pattern, str);
        destruct_pattern(compiled_pattern);
        return ret;
    }

    void destruct_match(MATCH *match) {

    }

}
