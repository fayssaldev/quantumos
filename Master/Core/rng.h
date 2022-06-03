/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#ifndef __RNG_H
#define __RNG_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcu_type.h"

uint32_t RNG_GetRandNum(void);
    
#ifdef __cplusplus
}
#endif

#endif
