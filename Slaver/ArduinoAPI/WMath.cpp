/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "WMath.h"


void randomSeed(unsigned long seed)
{
    if (seed != 0) {
        srand(seed);
    }
}


long random(long howbig)
{
    if (howbig == 0) {
        return 0;
    }
    return rand() % howbig;
}


long random(long howsmall, long howbig)
{
    if (howsmall >= howbig) {
        return howsmall;
    }
    long diff = howbig - howsmall;
    return random(diff) + howsmall;
}

unsigned int makeWord(unsigned int w) {
    return w;
}
unsigned int makeWord(unsigned char h, unsigned char l) {
    return (h << 8) | l;
}
