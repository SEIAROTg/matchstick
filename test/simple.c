#include <stdio.h>

#include "../matchstick/matchstick.h"

int main () {
    wchar_t * pattern = L"foo[A-Za-z\\d]{3}";
    wchar_t * tests[] = {
        L"",
        L"asdasdasd",
        L"fooAa0",
        L"barAa0",
        L"fooAa0Aa0",
        L"foo00",
    };
    printf("%lu\n", sizeof tests);
    MS_REGEX * regex;
    regex = ms_compile_pattern(pattern, "");
    printf("PATTERN COMPILED - \"%ls\"", pattern);
    int n = sizeof(tests) / sizeof(wchar_t *);
    for (int i = 0; i < n; ++i) {
        printf("TEST #%d RESULT: %d FOR \"%ls\"\n", i, ms_test_compiled(regex, tests[i]), tests[i]);
    }
    ms_destruct_pattern(regex);
    return 0;
}