#ifndef XERLANG_STRINTERN_H
#define XERLANG_STRINTERN_H

#include <stdint.h>
#include <stddef.h>

typedef struct Intern {
    size_t len;
    const char *str;
} Intern;

const char *str_intern_range(const char *start, const char *end);
const char *str_intern(const char *str);

#endif //XERLANG_STRINTERN_H
