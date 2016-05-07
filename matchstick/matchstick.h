#ifndef MATCHSTICK_H
#define MATCHSTICK_H

#include "types.h"

/*
 *
 * Compile pattern in MS_CHAR* into MS_REGEX*
 *
 * Return the compiled pattern
 *
 */
MS_REGEX * ms_compile_pattern (const MS_CHAR * pattern, const char * flags);

/*
 *
 * Destroy a compiled pattern
 *
 */
void ms_destruct_pattern (MS_REGEX * pattern);

/*
 *
 * Test if str matches with pattern
 *
 * Return a boolean representation whether str matches with pattern
 *
 */
int ms_test_compiled (const MS_REGEX * pattern, const MS_CHAR * str);
int ms_test (const MS_CHAR * pattern, const MS_CHAR * str, const char * flags);

/*
 *
 * Search for the first match of pattern in str
 *
 * *str will be set to the beginning of the first match
 * Return the length of the match
 *
 */
int ms_search_compiled (const MS_REGEX * pattern, MS_CHAR ** str);
int ms_search (const MS_CHAR * pattern, MS_CHAR ** str, const char * flags);

/*
 *
 * Find matches of pattern in str
 *
 * Return found matches or NULL if no matches found
 *
 */
MS_MATCH * ms_match_compiled (const MS_REGEX * pattern, const MS_CHAR * str);
MS_MATCH * ms_match (const MS_CHAR * pattern, const MS_CHAR * str, const char * flags);

/*
 *
 * Destory a match
 *
 */
void ms_destruct_match (MS_MATCH * match);


#endif // MATCHSTICK_H
