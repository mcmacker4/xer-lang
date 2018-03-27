//
// Created by McMacker4 on 18/03/2018.
//

#ifndef XERLANG_TOKENIZER_H
#define XERLANG_TOKENIZER_H

#include <ctype.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "keywords.c"
#include "../util/strintern.h"
#include "../util/stretchy.h"

typedef enum TokenKind {
    TK_INT = 128,
    TK_FLOAT,
    TK_CHAR,
    TK_STRING,
    TK_IDENTIFIER,
    TK_KEYWORD
} TokenKind;

typedef struct Token {
    TokenKind kind;
    const char *start;
    const char *end;
    union {
        int intVal;
        const char* stringVal;
        char charVal;
    };
} Token;

void setTokenizerStream(char *str);
void nextToken(Token *token);

void describeToken(TokenKind kind, char* dest, size_t n);

#endif //XERLANG_TOKENIZER_H
