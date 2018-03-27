#include <mem.h>
#include "strintern.h"
#include "stretchy.h"

static Intern *interns;

const char *str_intern_range(const char *start, const char *end) {
    size_t len = end - start;
    for(Intern *it = interns; it != buf_end(interns); it++) {
        if(it->len == len && strncmp(it->str, start, len) == 0) {
            return it->str;
        }
    }
    char *str = xmalloc(len + 1);
    memcpy(str, start, len);
    str[len] = 0;
    buf_push(interns, (Intern){len, str});
    return str;
}

const char *str_intern(const char *str) {
    return str_intern_range(str, str + strlen(str));
}