#include "parser.h"

Token token;

__forceinline bool isToken(TokenKind kind) {
    return token.kind == kind;
}

bool matchToken(TokenKind kind) {
    if(isToken(kind)) {
        nextToken(&token);
        return true;
    } else {
        return false;
    }
}

bool expectToken(TokenKind kind) {
    if(isToken(kind)) {
        nextToken(&token);
        return true;
    } else {
        char exp[20]; describeToken(kind, exp, 20);
        char got[20]; describeToken(token.kind, exp, 20);
        fprintf(stderr, "Expected token %s but got %s", exp, got);
        return false;
    }
}

/*
 * expr3 = INT | ('(', expr0, ')');
 * expr2 = ['-'] expr3;
 * expr1 = expr2, {('*' | '/'), expr2};
 * expr0 = expr1, {('+' | '-'), expr1};
 * expr = expr0
 */

int parseExpr0();

int parseExpr3() {
    int result = 0;
    if(matchToken(TK_INT)) {
        result = token.intVal;
    } else if(matchToken('(')) {
        result = parseExpr0();
        expectToken(')');
    }
    return result;
}

int parseExpr2() {
    if(isToken('-')) {
        nextToken(&token);
        return -parseExpr3();
    } else {
        return parseExpr3();
    }
}

int parseExpr1() {
    int res = parseExpr2();
    while(isToken('*') || isToken('/')) {
        if (matchToken('*')) {
            res *= parseExpr2();
        } else if (matchToken('/')) {
            res /= parseExpr2();
        }
    }
    return res;
}

int parseExpr0() {
    int res = parseExpr1();
    while(isToken('+') || isToken('-')) {
        if (matchToken('+')) {
            res += parseExpr1();
        } else if (matchToken('-')) {
            res -= parseExpr1();
        }
    }
    return res;
}

int parseExpr() {
    nextToken(&token);
    parseExpr0();
}

void parse(char* str) {
    setTokenizerStream(str);
    int result = parseExpr();
    printf("Expression Result: %d\n", result);
}