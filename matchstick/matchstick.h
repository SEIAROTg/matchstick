#ifndef MATCHSTICK_H
#define MATCHSTICK_H

#include <cwchar>

namespace matchstick {

    typedef wchar_t MS_CHAR;

    struct MATCH_GROUP {
        MATCH_GROUP *next;
        MS_CHAR *start;
        int length;
    };

    struct MATCH {
        MATCH *next;
        MATCH_GROUP *first_group;
    };

    int test(const MS_CHAR *pattern, const MS_CHAR *str, const char *flags);
    int search(const MS_CHAR *pattern, MS_CHAR **str, const char *flags);
    MATCH *match(const MS_CHAR *pattern, const MS_CHAR *str, const char *flags);

    struct PATTERN {
    private:
        void * regex;
    public:
        PATTERN(const MS_CHAR *pattern, const char *flags);
        ~PATTERN();
        int test(const MS_CHAR *str);
        int search(MS_CHAR **str);
        MATCH *match(const MS_CHAR *str);
    };

}

#endif // MATCHSTICK_H
