# Matchstick

Yet another regular expression engine in C++

## API

### Compile pattern

Compile a regular expression in string into FSM

```C++
matchstick::PATTERN::PATTERN(const wchar_t *pattern, const char *flags);
```

### Test

Test whether a string matches the regular expression

Return zero for match, non-zero for mismatch

```C++
unsigned int matchstick::PATTERN::test(const wchar_t *str);
unsigned int matchstick::test(const wchar_t *pattern, const wchar_t *str, const char *flags);
```

### Search

Search for the first match starting at `str`

Return the length of match and set `*str` to the beginning of match

If no match found, `(unsigned int) -1` will be returned.

```C++
unsigned int matchstick::PATTERN::search(wchar_t **str);
unsigned int matchstick::search(const wchar_t *pattern, wchar_t **str, const char *flags);
```

### Match

Search for matching groups

Return match groups

```C++
matchstick::MATCH *matchstick::PATTERN::match(const wchar_t *str);
matchstick::MATCH *matchstick::match(const wchar_t *pattern, const wchar_t *str, const char *flags);
```

### Match Groups

#### Get group by index

```C++
const matchstick::MATCH_GROUP &operator [] (const matchstick::MATCH &match, unsigned int index);
```

#### Get group by name

```C++
const matchstick::MATCH_GROUP &operator [] (const matchstick::MATCH &match, wchar_t *index);
```

### Match Group

```C++
wchar_t *matchstick::MATCH_GROUP::start;
unsigned int matchstick::MATCH_GROUP::length;
```

## Features

### Flags

| Flag              | Syntax | Support   |
| ----------------- | ------ | --------- |
| global            | `g`    | NO        |
| multiline         | `m`    | PLAN      |
| case insensitive  | `i`    | PLAN      |
| ignore whitespace | `x`    | PLAN      |
| single line       | `s`    | PLAN      |
| unicode           | `u`    | LONG-TERM |
| extended          | `X`    | NO        |
| ungreedy          | `U`    | PLAN      |
| anchor            | `A`    | PLAN      |

### Anchors

| Anchor                 | Syntax | Support |
| ---------------------- | ------ | ------- |
| start of string        | `^`    | PLAN    |
| end of string          | `$`    | PLAN    |
| start of match         | `\G`   | PLAN    |
| start of string        | `\A`   | PLAN    |
| end of string          | `\Z`   | PLAN    |
| absolute end of string | `\z`   | PLAN    |
| word boundary          | `\b`   | PLAN    |
| non-word-boundary      | `\B`   | PLAN    |

### Escape

| Escape    | Syntax | Support |
| --------- | ------ | ------- |
| bell      | `\a`   | PLAN    |
| backspace | `\b`   | PLAN    |
| tab       | `\t`   | PLAN    |
| return    | `\r`   | PLAN    |
| form feed | `\f`   | PLAN    |
| new line  | `\n`   | PLAN    |
| escape    | `\e`   | PLAN    |
| null      | `\0`   | PLAN    |

### Meta

| Meta                      | Syntax     | Support   |
| ------------------------- | ---------- | --------- |
| any character             | `.`        | PLAN      |
| whitespace                | `\s`       | PLAN      |
| non-whitespace            | `\S`       | PLAN      |
| digit                     | `\d`       | PLAN      |
| non-digit                 | `\D`       | PLAN      |
| word                      | `\w`       | PLAN      |
| non-word                  | `\W`       | PLAN      |
| vertical whitespace       | `\v`       | PLAN      |
| non-vertical-whitespace   | `\V`       | PLAN      |
| horizontal whitespace     | `\h`       | PLAN      |
| non-horizontal whitespace | `\H`       | PLAN      |
| unicode character         | `\uYYYY`   | LONG-TERM |
| hex character             | `\xYY`     | PLAN      |
| octal character           | `\DDD`     | PLAN      |
| back reference            | `\N`       | PLAN      |
| back reference            | `\gN`      | PLAN      |
| back reference            | `\g{N}`    | PLAN      |
| back reference            | `\k<name>` | PLAN      |
| back reference            | `\k'name'` | PLAN      |
| back reference            | `\k{name}` | PLAN      |
| control character         | `\cY`      | PLAN      |
| reset match               | `\K`       | PLAN      |
| quote                     | `\Q…\E`    | LONG-TERM |

### Quantifiers

| Quantifier      | Syntax      | Support |
| --------------- | ----------- | ------- |
| any             | `*`         | PLAN    |
| zero or one     | `?`         | PLAN    |
| one or more     | `+`         | PLAN    |
| exact           | `{n}`       | PLAN    |
| min             | `{min,}`    | PLAN    |
| max             | `{,max}`    | PLAN    |
| range           | `{min,max}` | PLAN    |
| greedy/ungreedy | `?`         | PLAN    |
| possessive      | `+`         | PLAN    |

### Charset

| Charset            | Syntax         | Support |
| ------------------ | -------------- | ------- |
| basic              | `[abc]`        | PLAN    |
| except             | `[\^abc]`      | PLAN    |
| range              | `[a-z]`        | PLAN    |
| lowercase          | `[[:lower:]]`  | PLAN    |
| uppercase          | `[[:upper:]]`  | PLAN    |
| letters            | `[[:alpha:]]`  | PLAN    |
| digits             | `[[::digit:]]` | PLAN    |
| letters and digits | `[[:alnum:]]`  | PLAN    |
| ascii              | `[[:ascii:]]`  | PLAN    |
| blank              | `[[:blank:]]`  | PLAN    |
| non-blank          | `[[:graph:]]`  | PLAN    |
| control characters | `[[:cntrl:]]`  | PLAN    |
| punctuation        | `[[:punct:]]`  | PLAN    |
| whitespace         | `[[:space:]]`  | PLAN    |
| word               | `[[:word:]]`   | PLAN    |
| hex digits         | `[[:xdigit:]]` | PLAN    |

### Grouping

| Grouping            | Syntax               | Support |
| ------------------- | -------------------- | ------- |
| capture             | `()`                 | PLAN    |
| non-capture         | `(?:)`               | PLAN    |
| atomic              | `(?>)`               | PLAN    |
| either              | `(A|B)`              | PLAN    |
| comment             | `(?#)`               | PLAN    |
| name                | `(?'name')`          | PLAN    |
| name                | `(?<name>)`          | PLAN    |
| name                | `(?P<name>)`         | PLAN    |
| set flags           | `(?flags)`           | PLAN    |
| condition           | `(?(condition)A|B)`  | PLAN    |
| recurse             | `(?R)`               | NO      |
| recurse             | `(?n)`               | NO      |
| recurse             | `(?&name)`           | NO      |
| recurse             | `(?&P>name)`         | NO      |
| back reference      | `(?&P=name)`         | PLAN    |
| positive lookahead  | `(?=)`               | PLAN    |
| negative lookahead  | `(?!)`               | PLAN    |
| positive lookbehind | `(?<=)`              | NO      |
| positive lookbehind | `(?<!)`              | NO      |