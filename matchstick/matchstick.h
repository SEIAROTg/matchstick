#ifndef MATCHSTICK_H
#define MATCHSTICK_H

#include "types.h"

namespace matchstick {

    /*
     *
     * Compile pattern in MS_CHAR* into REGEX*
     *
     * Return the compiled pattern
     *
     */
    PATTERN *compile_pattern(const MS_CHAR *pattern, const char *flags);

    /*
     *
     * Destroy a compiled pattern
     *
     */
    void destruct_pattern(PATTERN *pattern);

    /*
     *
     * Test if str matches with pattern
     *
     * Return a boolean representation whether str matches with pattern
     *
     */
    int test(const PATTERN *pattern, const MS_CHAR *str);

    int test(const MS_CHAR *pattern, const MS_CHAR *str, const char *flags);

    /*
     *
     * Search for the first match of pattern in str
     *
     * *str will be set to the beginning of the first match
     * Return the length of the match
     *
     */
    int search(const PATTERN *pattern, MS_CHAR **str);

    int search(const MS_CHAR *pattern, MS_CHAR **str, const char *flags);

    /*
     *
     * Find matches of pattern in str
     *
     * Return found matches or NULL if no matches found
     *
     */
    MATCH *match(const PATTERN *pattern, const MS_CHAR *str);

    MATCH *match(const MS_CHAR *pattern, const MS_CHAR *str, const char *flags);

    /*
     *
     * Destory a match
     *
     */
    void destruct_match(MATCH *match);

}

#endif // MATCHSTICK_H
