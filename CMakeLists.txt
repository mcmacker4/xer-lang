cmake_minimum_required(VERSION 3.9)
project(XerLang C)

set(CMAKE_C_STANDARD 99)

add_executable(XerLang src/main.c src/parse/parser.h src/parse/parser.c src/token/keywords.c src/token/tokenizer.h src/token/tokenizer.c src/util/misc.h src/util/stretchy.h src/util/strintern.h src/util/strintern.c src/util/misc.c src/util/stretchy.c src/token/keywords.h)