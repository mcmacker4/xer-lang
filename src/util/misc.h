#ifndef XERLANG_UTIL_H
#define XERLANG_UTIL_H

#include <stdio.h>
#include <stdint.h>
#include <malloc.h>
#include <process.h>

#define MAX(a, b) ((a) >= (b) ? (a) : (b))

void *xrealloc(void *ptr, size_t num_bytes);

void *xmalloc(size_t num_bytes);

#endif //XERLANG_UTIL_H
