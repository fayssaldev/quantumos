/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#ifndef __TIMER_H
#define __TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcu_type.h"
    
#define Timer_PreemptionPriority_Default 0
#define Timer_SubPriority_Default 3
#define IS_APB2_TIM(TIMx) (TIMx==TIM1||TIMx==TIM8||TIMx==TIM9||TIMx==TIM10||TIMx==TIM11)
    
typedef void(*Timer_CallbackFunction_t)(void);

void Timer_ClockCmd(TIM_TypeDef* TIMx, FunctionalState NewState);
void Timer_SetInterrupt(TIM_TypeDef* TIMx, uint32_t time, Timer_CallbackFunction_t function);
void Timer_SetInterruptTimeUpdate(TIM_TypeDef* TIMx, uint32_t time);
void Timer_SetInterruptFreqUpdate(TIM_TypeDef* TIMx, uint32_t freq);
uint32_t Timer_GetClockOut(TIM_TypeDef* TIMx);
void Timer_SetInterruptBase(
    TIM_TypeDef* TIMx, 
    uint16_t period, uint16_t prescaler, 
    Timer_CallbackFunction_t function, 
    uint8_t PreemptionPriority, uint8_t SubPriority
);

#define TimerClockCmd(TIMx,EN)                  Timer_ClockCmd(TIMx,EN)
#define TimerSet(TIMx,time,function)            Timer_SetInterrupt(TIMx,time,function)
#define Timer_Init(TIMx,time,function,pre,sub)  Timer_SetInterruptBase(TIMx,0xFF,0xFF,function,pre,sub),Timer_SetInterruptTimeUpdate(TIMx,time)
#define TimerSet_InterruptTimeUpdate(TIMx,time) Timer_SetInterruptTimeUpdate(TIMx,time)
    
#ifdef __cplusplus
}
#endif

#endif
