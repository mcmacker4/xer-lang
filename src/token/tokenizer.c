#include "tokenizer.h"


static char* stream;

int charToHexVal[256] = {
        ['0'] = 0,
        ['1'] = 1,
        ['2'] = 2,
        ['3'] = 3,
        ['4'] = 4,
        ['5'] = 5,
        ['6'] = 6,
        ['7'] = 7,
        ['8'] = 8,
        ['9'] = 9,
        ['A'] = 10, ['a'] = 10,
        ['B'] = 11, ['b'] = 11,
        ['C'] = 12, ['c'] = 12,
        ['D'] = 13, ['d'] = 13,
        ['E'] = 14, ['e'] = 14,
        ['F'] = 15, ['f'] = 15,
};

char escapeSeqToChar[256] = {
        ['a'] = '\a',
        ['b'] = '\b',
        ['f'] = '\f',
        ['n'] = '\n',
        ['r'] = '\r',
        ['t'] = '\t',
        ['v'] = '\v',
        ['\\'] = '\\',
        ['\''] = '\'',
        ['"'] = '\"',
        ['?'] = '\?',
};

bool ishexchar(char c) {
    switch(toupper(c)) {
        case 'A': case 'B': case 'C':
        case 'D': case 'E': case 'F':
            return true;
        default:
            return false;
    }
}

void syntax_error(const char* msg) {
    fprintf(stderr, msg);
    exit(-1);
}

void setTokenizerStream(char *str) {
    stream = str;
}

void scanNumber(Token *token) {
    int value = 0;
    if(*stream == '0') {
        stream++;
        if(toupper(*stream) == 'X') {
            stream++;
            while(isdigit(*stream) || ishexchar(*stream)) {
                value <<= 4;
                value += charToHexVal[*stream];
                stream++;
            }
        } else if(isdigit(*stream)) {
            syntax_error("Integers cannot start with leading zeroes.");
        }
    } else {
        while(isdigit(*stream)) {
            value *= 10;
            value += charToHexVal[*stream];
            stream++;
        }
    }
    token->kind = TK_INT;
    token->intVal = value;
}

void scanChar(Token *token) {
    assert(*stream == '\'');
    stream++;
    char val = *stream;
    if(val == '\\') {
        stream++;
        val = escapeSeqToChar[*stream];
    }
    token->kind = TK_CHAR;
    token->charVal = val;
}

void scanString(Token *token) {
    assert(*stream == '"');
    char* str = NULL;
    stream++;
    while(*stream && *stream != '"') {

        char val = *stream;

        if(*stream == '\n')
            syntax_error("Strings cannot be multiline.");

        if(*stream == '\\') {
            stream++;
            val = escapeSeqToChar[*stream];
        }

        stream++;
        buf_push(str, val);

    }

    buf_push(str, 0);

    token->kind = TK_STRING;
    token->stringVal = str;

}

void scanName(Token *token) {
    while(isalnum(*stream) | *stream == '_')
        stream++;
    token->stringVal = str_intern_range(token->start, stream);
    token->kind = isKeyword(token->stringVal) ? TK_KEYWORD : TK_IDENTIFIER;
}

void nextToken(Token *token) {
    token->start = stream;
    switch(*stream) {
        case '0': case '1': case '2': case '3': case '4':
        case '5': case '6': case '7': case '8': case '9': {
            scanNumber(token);
            break;
        }
        case 'a': case 'b': case 'c': case 'd': case 'e':
        case 'f': case 'g': case 'h': case 'i': case 'j':
        case 'k': case 'l': case 'm': case 'n': case 'o':
        case 'p': case 'q': case 'r': case 's': case 't':
        case 'u': case 'v': case 'w': case 'x': case 'y':
        case 'z': case 'A': case 'B': case 'C': case 'D':
        case 'E': case 'F': case 'G': case 'H': case 'I':
        case 'J': case 'K': case 'L': case 'M': case 'N':
        case 'O': case 'P': case 'Q': case 'R': case 'S':
        case 'T': case 'U': case 'V': case 'W': case 'X':
        case 'Y': case 'Z': case '_': {
            scanName(token);
            break;
        }
        case '\'':
            scanChar(token);
            break;
        case '"': {
            scanString(token);
            break;
        }
        case ' ': case '\t': case '\r': case '\b':
        default: {
            token->kind = (TokenKind) *stream;
            stream++;
        }
    }
    token->end = stream;
}

void describeToken(TokenKind kind, char* dest, size_t n) {
    switch(kind) {
        case TK_IDENTIFIER:
            snprintf(dest, n, "IDENTIFIER");
        case TK_INT:
            snprintf(dest, n, "INTEGER");
        default:
            if(kind < 128 && isprint(kind))
                snprintf(dest, n, "%c", kind);
            else
                snprintf(dest, n, "<ASCII %d>", kind);
    }
}