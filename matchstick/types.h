#ifndef MATCHSTICK_TYPES_H
#define MATCHSTICK_TYPES_H

#include <wchar.h>

namespace matchstick {

    typedef wchar_t MS_CHAR;

    typedef void PATTERN;

    struct MATCH_GROUP {
        MATCH_GROUP *next;
        MS_CHAR *start;
        int length;
    };

    struct MATCH {
        MATCH *next;
        MATCH_GROUP *first_group;
    };

}

#endif //MATCHSTICK_TYPES_H
