/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/


#ifndef __DTOSTRF_H
#define	__DTOSTRF_H
#include "stdio.h"
#ifdef __cplusplus
extern "C" {
#endif

char *dtostrf (double val, signed char width, unsigned char prec, char *sout);

#ifdef __cplusplus
}
#endif

#endif
