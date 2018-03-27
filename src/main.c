#include "parse/parser.h"

int main() {

    parse("3+2+5"); //10
    parse("5-3+-1"); //1
    parse("5*3+2*2"); //19
    parse("6*-(2+1)/2"); //50

}