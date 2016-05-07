#ifndef MATCHSTICK_TYPES_H
#define MATCHSTICK_TYPES_H

#include <wchar.h>

typedef wchar_t MS_CHAR;

typedef void MS_REGEX;

typedef struct MS_MATCH_GROUP {
    struct MS_GROUP * next;
    struct MS_CHAR * start;
    int length;
} MS_GROUP;

typedef struct MS_MATCH {
    struct MS_MATCH * next;
    struct MS_GROUP * first_group;
} MS_MATCH;

#endif //MATCHSTICK_TYPES_H
