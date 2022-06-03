﻿/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/


#include "dtostrf.h"

char *dtostrf (double val, signed char width, unsigned char prec, char *sout) {
    char fmt[20];
    sprintf(fmt, "%%%d.%df", width, prec);
    sprintf(sout, fmt, val);
    return sout;
}

