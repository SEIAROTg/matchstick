#include <cstdio>

#include "../matchstick/matchstick.h"

int main () {
    const wchar_t * pattern = L"foo[A-Za-z\\d]{3}";
    const wchar_t * tests[] = {
        L"",
        L"asdasdasd",
        L"fooAa0",
        L"barAa0",
        L"fooAa0Aa0",
        L"foo00",
    };
    printf("%lu\n", sizeof tests);
    matchstick::PATTERN regex(pattern, "");
    printf("PATTERN COMPILED - \"%ls\"", pattern);
    int n = sizeof(tests) / sizeof(wchar_t *);
    for (int i = 0; i < n; ++i) {
        printf("TEST #%d RESULT: %d FOR \"%ls\"\n", i, regex.test(tests[i]), tests[i]);
    }
    return 0;
}