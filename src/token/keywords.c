#include "keywords.h"

const char* keyword_func;
const char* keyword_var;
const char* keyword_int;
const char* keyword_float;
const char* keyword_char;
const char* keyword_string;
const char* keyword_struct;
const char* keyword_if;
const char* keyword_for;
const char* keyword_while;

void initKeywords() {
    keyword_func = str_intern("func");
    keyword_var = str_intern("var");
    keyword_int = str_intern("int");
    keyword_float = str_intern("float");
    keyword_char = str_intern("char");
    keyword_string = str_intern("string");
    keyword_struct = str_intern("struct");
    keyword_if = str_intern("if");
    keyword_for = str_intern("for");
    keyword_while = str_intern("while");
}

bool isKeyword(const char* str) {
    return str == keyword_func ||
        str == keyword_var ||
        str == keyword_int ||
        str == keyword_float ||
        str == keyword_char ||
        str == keyword_string ||
        str == keyword_struct ||
        str == keyword_if ||
        str == keyword_for ||
        str == keyword_while;
}