/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "exti.h"


static EXTI_CallbackFunction_t EXTI_Function[16] = {0};


static IRQn_Type EXTI_GetIRQn(uint8_t Pin)
{
    IRQn_Type EXTIx_IRQn;
    uint8_t Pinx = GPIO_GetPinNum(Pin);

    if(Pinx <= 4)
    {
        switch(Pinx)
        {
        case 0:
            EXTIx_IRQn = EXTI0_IRQn;
            break;
        case 1:
            EXTIx_IRQn = EXTI1_IRQn;
            break;
        case 2:
            EXTIx_IRQn = EXTI2_IRQn;
            break;
        case 3:
            EXTIx_IRQn = EXTI3_IRQn;
            break;
        case 4:
            EXTIx_IRQn = EXTI4_IRQn;
            break;
        }
    }
    else if(Pinx >= 5 && Pinx <= 9)
        EXTIx_IRQn = EXTI9_5_IRQn;
    else if(Pinx >= 10 && Pinx <= 15)
        EXTIx_IRQn = EXTI15_10_IRQn;
    
    return EXTIx_IRQn;
}


void EXTIx_Init(uint8_t Pin, EXTI_CallbackFunction_t function, EXTITrigger_TypeDef Trigger_Mode, uint8_t PreemptionPriority, uint8_t SubPriority)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    uint8_t Pinx;

    if(!IS_PIN(Pin))
        return;

    Pinx = GPIO_GetPinNum(Pin);

    if(Pinx > 15)
        return;
    
    EXTI_Function[Pinx] = function;

    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(EXTI_GetPortSourceGPIOx(Pin), EXTI_GetPinSourcex(Pin));

    EXTI_InitStructure.EXTI_Line = EXTI_GetLine(Pin);
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = Trigger_Mode;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);     

    NVIC_InitStructure.NVIC_IRQChannel = EXTI_GetIRQn(Pin);                    
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = PreemptionPriority;     
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = SubPriority;                
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;                     
    NVIC_Init(&NVIC_InitStructure);
}

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void attachInterrupt(uint8_t Pin, EXTI_CallbackFunction_t function, EXTITrigger_TypeDef Trigger_Mode)
{
    EXTIx_Init(Pin, function, Trigger_Mode, EXTI_PreemptionPriority_Default, EXTI_SubPriority_Default);
}

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void detachInterrupt(uint8_t Pin)
{
    if(!IS_PIN(Pin))
        return;
    
    NVIC_DisableIRQ(EXTI_GetIRQn(Pin));
}

#define EXTIx_IRQHANDLER(n) \
do{\
    if(EXTI_GetITStatus(EXTI_Line##n) != RESET)\
    {\
        if(EXTI_Function[n]) EXTI_Function[n]();\
        EXTI_ClearITPendingBit(EXTI_Line##n);\
    }\
}while(0)

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void EXTI0_IRQHandler(void)
{
    EXTIx_IRQHANDLER(0);
}

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void EXTI1_IRQHandler(void)
{
    EXTIx_IRQHANDLER(1);
}

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void EXTI2_IRQHandler(void)
{
    EXTIx_IRQHANDLER(2);
}

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void EXTI3_IRQHandler(void)
{
    EXTIx_IRQHANDLER(3);
}

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void EXTI4_IRQHandler(void)
{
    EXTIx_IRQHANDLER(4);
}

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void EXTI9_5_IRQHandler(void)
{
    EXTIx_IRQHANDLER(5);
    EXTIx_IRQHANDLER(6);
    EXTIx_IRQHANDLER(7);
    EXTIx_IRQHANDLER(8);
    EXTIx_IRQHANDLER(9);
}

/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

void EXTI15_10_IRQHandler(void)
{
    EXTIx_IRQHANDLER(10);
    EXTIx_IRQHANDLER(11);
    EXTIx_IRQHANDLER(12);
    EXTIx_IRQHANDLER(13);
    EXTIx_IRQHANDLER(14);
    EXTIx_IRQHANDLER(15);
}
