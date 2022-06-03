/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "timer.h"


typedef enum
{
    TIMER1, TIMER2, TIMER3, TIMER4, TIMER5, TIMER6, TIMER7, TIMER8,
    TIMER9, TIMER10, TIMER11, TIMER12, TIMER13, TIMER14, TIMER_MAX
} TIMER_Type;


static Timer_CallbackFunction_t TIMx_Function[TIMER_MAX] = {0};


void Timer_ClockCmd(TIM_TypeDef* TIMx, FunctionalState NewState)
{
    if(TIMx == TIM1)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, NewState);
    }
    else if(TIMx == TIM2)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, NewState);
    }
    else if(TIMx == TIM3)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, NewState);
    }
    else if(TIMx == TIM4)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, NewState);
    }
    else if(TIMx == TIM5)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM5, NewState);
    }
    else if(TIMx == TIM6)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, NewState);
    }
    else if(TIMx == TIM7)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM7, NewState);
    }
    else if(TIMx == TIM8)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM8, NewState);
    }
    else if(TIMx == TIM9)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM9, NewState);
    }
    else if(TIMx == TIM10)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM10, NewState);
    }
    else if(TIMx == TIM11)
    {
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM11, NewState);
    }
    else if(TIMx == TIM12)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM12, NewState);
    }
    else if(TIMx == TIM13)
    {
        RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM13, NewState);
    }
    else
    {
        if(TIMx == TIM14)
        {
            RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM14, NewState);
        }
    }
}


#define CLOCK_ABS(x) (((x)>0)?(x):-(x))


static float Qsqrt(float number)
{
    long i;
    float x2, y;
    const float threehalfs = 1.5f;
    x2 = number * 0.5f;
    y  = number;
    i  = *(long*)&y;
    i  = 0x5f3759df - (i >> 1);
    y  = *(float*)&i;
    y  = y * (threehalfs - (x2 * y * y));
    y  = y * (threehalfs - (x2 * y * y));
    return 1.0f / y;
}


static int32_t Timer_FreqToArrPsc(
    uint32_t freq, uint32_t clock,
    uint16_t *period, uint16_t *prescaler
)
{
    uint32_t prodect;
    uint16_t psc, arr;
    uint16_t max_error = 0xFFFF;

    if(freq == 0 || freq > clock)
        goto failed;

    
    prodect = clock / freq;

    
    psc = Qsqrt(prodect);

    
    for(; psc > 1; psc--)
    {
        for(arr = psc; arr < 0xFFFF; arr++)
        {
            
            int32_t newerr = arr * psc - prodect;
            newerr = CLOCK_ABS(newerr);
            if(newerr < max_error)
            {
                
                max_error = newerr;
                
                *period = arr;
                *prescaler = psc;
                
                if(max_error == 0)
                    goto success;
            }
        }
    }

    
success:
    return (freq - clock / ((*period) * (*prescaler)));

    
failed:
    return (freq - clock);
}


static void Timer_TimeToArrPsc(
    uint32_t time, uint32_t clock,
    uint16_t *period, uint16_t *prescaler
)
{
    uint32_t cyclesPerMicros = clock / 1000000U;
    uint32_t prodect = time * cyclesPerMicros;
    uint16_t arr, psc;

    if(prodect < cyclesPerMicros * 30)
    {
        arr = 10;
        psc = prodect / arr;
    }
    else if(prodect < 65535 * 1000)
    {
        arr = prodect / 1000;
        psc = prodect / arr;
    }
    else
    {
        arr = prodect / 20000;
        psc = prodect / arr;
    }
    *period = arr;
    *prescaler = psc;
}


void Timer_SetInterrupt(TIM_TypeDef* TIMx, uint32_t time, Timer_CallbackFunction_t function)
{
    uint16_t period, prescaler;
    uint32_t clock = (IS_APB2_TIM(TIMx) ? F_CPU : (F_CPU / 2));

    if(!IS_TIM_ALL_PERIPH(TIMx) || time == 0)
        return;

    
    Timer_TimeToArrPsc(
        time,
        clock,
        &period,
        &prescaler
    );

    
    Timer_SetInterruptBase(
        TIMx,
        period,
        prescaler,
        function,
        Timer_PreemptionPriority_Default,
        Timer_SubPriority_Default
    );
}


void Timer_SetInterruptFreqUpdate(TIM_TypeDef* TIMx, uint32_t freq)
{
    uint16_t period, prescaler;
    uint32_t clock = (IS_APB2_TIM(TIMx) ? F_CPU : (F_CPU / 2));

    if(!IS_TIM_ALL_PERIPH(TIMx) || freq == 0)
        return;

    Timer_FreqToArrPsc(
        freq,
        clock,
        &period,
        &prescaler
    );
    TIM_SetAutoreload(TIMx, period - 1);
    TIM_PrescalerConfig(TIMx, prescaler - 1, TIM_PSCReloadMode_Immediate);
}


uint32_t Timer_GetClockOut(TIM_TypeDef* TIMx)
{
    uint32_t clock = (IS_APB2_TIM(TIMx) ? F_CPU : (F_CPU / 2));
    if(!IS_TIM_ALL_PERIPH(TIMx))
        return 0;

    return (clock / ((TIMx->ARR + 1) * (TIMx->PSC + 1)));
}


void Timer_SetInterruptTimeUpdate(TIM_TypeDef* TIMx, uint32_t time)
{
    uint16_t period, prescaler;
    uint32_t clock = (IS_APB2_TIM(TIMx) ? F_CPU : (F_CPU / 2));

    if(!IS_TIM_ALL_PERIPH(TIMx))
        return;

    Timer_TimeToArrPsc(
        time,
        clock,
        &period,
        &prescaler
    );

    TIM_SetAutoreload(TIMx, period - 1);
    TIM_PrescalerConfig(TIMx, prescaler - 1, TIM_PSCReloadMode_Immediate);
}


void Timer_SetInterruptBase(
    TIM_TypeDef* TIMx,
    uint16_t period, uint16_t prescaler,
    Timer_CallbackFunction_t function,
    uint8_t PreemptionPriority, uint8_t SubPriority
)
{
    TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    uint8_t TIMx_IRQn;
    TIMER_Type TIMERx;

    if(!IS_TIM_ALL_PERIPH(TIMx))
        return;

#define TIMx_IRQn_DEF(n,x_IRQn)\
do{\
    if(TIMx == TIM##n)\
    {\
        TIMERx = TIMER##n;\
        TIMx_IRQn = x_IRQn;\
    }\
}\
while(0)

    
    TIMx_IRQn_DEF(1, TIM1_UP_TIM10_IRQn);
    TIMx_IRQn_DEF(2, TIM2_IRQn);
    TIMx_IRQn_DEF(3, TIM3_IRQn);
    TIMx_IRQn_DEF(4, TIM4_IRQn);
    TIMx_IRQn_DEF(5, TIM5_IRQn);
//    TIMx_IRQn_DEF(6, TIM6_DAC_IRQn);
    TIMx_IRQn_DEF(7, TIM7_IRQn);
    TIMx_IRQn_DEF(8, TIM8_UP_TIM13_IRQn);
    TIMx_IRQn_DEF(9, TIM1_BRK_TIM9_IRQn);
    TIMx_IRQn_DEF(10, TIM1_UP_TIM10_IRQn);
    TIMx_IRQn_DEF(11, TIM1_TRG_COM_TIM11_IRQn);
    TIMx_IRQn_DEF(12, TIM8_BRK_TIM12_IRQn);
    TIMx_IRQn_DEF(13, TIM8_UP_TIM13_IRQn);
    TIMx_IRQn_DEF(14, TIM8_TRG_COM_TIM14_IRQn);

    if(TIMx_IRQn == 0)
        return;

    /*register callback function*/
    TIMx_Function[TIMERx] = function;

    /*Enable PeriphClock*/
    TIM_DeInit(TIMx);
    Timer_ClockCmd(TIMx, ENABLE);

    TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
    TIM_TimeBaseStructure.TIM_Period = period - 1;         
    TIM_TimeBaseStructure.TIM_Prescaler = prescaler - 1;  
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;     //TDTS = Tck_tim
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
    TIM_TimeBaseInit(TIMx, &TIM_TimeBaseStructure); 
    NVIC_InitStructure.NVIC_IRQChannel = TIMx_IRQn;  //TIM
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;  
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;  
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
    NVIC_Init(&NVIC_InitStructure);  

    TIM_ClearFlag(TIMx, TIM_FLAG_Update);
    TIM_ITConfig(TIMx, TIM_IT_Update, ENABLE);  
}

#define TIMx_IRQHANDLER(n) \
do{\
    if (TIM_GetITStatus(TIM##n, TIM_IT_Update) != RESET)\
    {\
        if(TIMx_Function[TIMER##n]) TIMx_Function[TIMER##n]();\
        TIM_ClearITPendingBit(TIM##n, TIM_IT_Update);\
    }\
}while(0)


void TIM1_UP_TIM10_IRQHandler(void)   //TIM1中断
{
    TIMx_IRQHANDLER(1);
    TIMx_IRQHANDLER(10);
}


void TIM2_IRQHandler(void)
{
    TIMx_IRQHANDLER(2);
}


void TIM3_IRQHandler(void)
{
    TIMx_IRQHANDLER(3);
}


void TIM4_IRQHandler(void)
{
    TIMx_IRQHANDLER(4);
}


void TIM5_IRQHandler(void)
{
    TIMx_IRQHANDLER(5);
}


void TIM6_DAC_IRQHandler(void)
{
    TIMx_IRQHANDLER(6);
}


void TIM7_IRQHandler(void)
{
    TIMx_IRQHANDLER(7);
}


void TIM8_UP_TIM13_IRQHandler(void)
{
    TIMx_IRQHANDLER(8);
    TIMx_IRQHANDLER(13);
}
