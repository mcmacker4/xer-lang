#include "stretchy.h"

void *buf__grow(const void *buf, size_t new_len, size_t elem_size) {
    assert(buf_cap(buf) <= (SIZE_MAX - 1) / 2);
    //calculate new capacity (exponential growth)
    size_t new_cap = MAX(1 + 2*buf_cap(buf), new_len);
    assert(new_len <= new_cap);
    assert(new_cap <= (SIZE_MAX - offsetof(BufHdr, buf)) / elem_size);
    //calculate the total new size of the header including the two `size_t` len and cap
    size_t new_size = offsetof(BufHdr, buf) + new_cap*elem_size;
    BufHdr *new_hdr;
    if(buf) {
        //buf is not null, reallocate
        new_hdr = xrealloc(buf__hdr(buf), new_size);
    } else {
        //buf is null, allocate without zeroing out (performance)
        new_hdr = xmalloc(new_size);
        new_hdr->len = 0;
    }
    new_hdr->cap = new_cap;
    return new_hdr->buf;
}