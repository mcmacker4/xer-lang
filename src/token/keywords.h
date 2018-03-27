//
// Created by McMacker4 on 27/03/2018.
//

#ifndef XERLANG_KEYWORDS_H
#define XERLANG_KEYWORDS_H

#include <stdbool.h>
#include "../util/strintern.h"

void initKeywords();
bool isKeyword(const char* str);

#endif //XERLANG_KEYWORDS_H
