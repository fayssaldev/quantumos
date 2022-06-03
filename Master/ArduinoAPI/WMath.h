/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#ifndef __WMATH_H
#define __WMATH_H

extern "C" {
#include "stdlib.h"
}

void randomSeed(unsigned long seed);
long random(long howbig);
long random(long howsmall, long howbig);

#endif
