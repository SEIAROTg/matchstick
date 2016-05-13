#include "matchstick.h"
#include "types.h"
#include "compile.h"
#include "execute.h"

namespace matchstick {

    PATTERN::PATTERN(const MS_CHAR *pattern, const char *flags) {
        regex = static_cast<void *> (_matchstick_compile::compile_pattern(pattern, flags));
    }
    PATTERN::~PATTERN() {
        delete static_cast<_matchstick::REGEX *> (regex);
    }

    int test(const MS_CHAR *pattern, const MS_CHAR *str, const char *flags) {
        PATTERN compiled_pattern(pattern, flags);
        return compiled_pattern.test(str);
    }

    int search(const MS_CHAR *pattern, MS_CHAR **str, const char *flags) {
        PATTERN compiled_pattern(pattern, flags);
        return compiled_pattern.search(str);
    }

    MATCH *match(const MS_CHAR *pattern, const MS_CHAR *str, const char *flags) {
        PATTERN compiled_pattern(pattern, flags);
        return compiled_pattern.match(str);
    }

}
