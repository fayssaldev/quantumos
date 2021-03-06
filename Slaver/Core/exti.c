/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "exti.h"
#include "gpio.h"


static EXTI_CallbackFunction_t EXTI_Function[16] = {0};


void EXTIx_Init(uint8_t Pin, EXTI_CallbackFunction_t function, EXTITrigger_TypeDef Trigger_Mode, uint8_t ChannelPriority)
{
    EXTI_InitTypeDef EXTI_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
    IRQn_Type EXTIx_IRQn;
    uint8_t Pinx;

    if(!IS_PIN(Pin))
        return;

    Pinx = Get_Pinx(Pin);

    if(Pinx > 15)
        return;

    EXTI_Function[Pinx] = function;

    
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
    SYSCFG_EXTILineConfig(Get_EXTI_PortSourceGPIOx(Pin), Get_EXTI_PinSourcex(Pin));

    EXTI_InitStructure.EXTI_Line = Get_EXTI_Linex(Pin);
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;）
    EXTI_InitStructure.EXTI_Trigger = Trigger_Mode;
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_Init(&EXTI_InitStructure);

    if(Pinx <= 1)
    {
        EXTIx_IRQn = EXTI0_1_IRQn;
    }
    else if(Pinx >= 2 && Pinx <= 3)
    {
        EXTIx_IRQn = EXTI2_3_IRQn;
    }
    else if(Pinx >= 4 && Pinx <= 15)
    {
        EXTIx_IRQn = EXTI4_15_IRQn;
    }

    NVIC_InitStructure.NVIC_IRQChannel = EXTIx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPriority = ChannelPriority;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
}


void attachInterrupt(uint8_t Pin, EXTI_CallbackFunction_t function, EXTITrigger_TypeDef Trigger_Mode)
{
    EXTIx_Init(
        Pin, 
        function, 
        Trigger_Mode, 
        EXTI_ChannelPriority_Default
    );
}

void detachInterrupt(uint8_t Pin)
{
    IRQn_Type EXTIx_IRQn;
    uint8_t Pinx;

    if(!IS_PIN(Pin))
        return;

    Pinx = Get_Pinx(Pin);

    if(Pinx > 15)
        return;
    
    if(Pinx <= 1)
    {
        EXTIx_IRQn = EXTI0_1_IRQn;
    }
    else if(Pinx >= 2 && Pinx <= 3)
    {
        EXTIx_IRQn = EXTI2_3_IRQn;
    }
    else if(Pinx >= 4 && Pinx <= 15)
    {
        EXTIx_IRQn = EXTI4_15_IRQn;
    }

    NVIC_DisableIRQ(EXTIx_IRQn);
}


void EXTI0_1_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line0) != RESET)
    {
        if(EXTI_Function[0]) EXTI_Function[0]();
        EXTI_ClearITPendingBit(EXTI_Line0);
    }
    if(EXTI_GetITStatus(EXTI_Line1) != RESET)
    {
        if(EXTI_Function[1]) EXTI_Function[1]();
        EXTI_ClearITPendingBit(EXTI_Line1);
    }
}


void EXTI2_3_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line2) != RESET)
    {
        if(EXTI_Function[2]) EXTI_Function[2]();
        EXTI_ClearITPendingBit(EXTI_Line2);
    }
    if(EXTI_GetITStatus(EXTI_Line3) != RESET)
    {
        if(EXTI_Function[3]) EXTI_Function[3]();
        EXTI_ClearITPendingBit(EXTI_Line3);
    }
}


void EXTI4_15_IRQHandler(void)
{
    if(EXTI_GetITStatus(EXTI_Line4) != RESET)
    {
        if(EXTI_Function[4]) EXTI_Function[4]();
        EXTI_ClearITPendingBit(EXTI_Line4);
    }
    if(EXTI_GetITStatus(EXTI_Line5) != RESET)
    {
        if(EXTI_Function[5]) EXTI_Function[5]();
        EXTI_ClearITPendingBit(EXTI_Line5);
    }
    if(EXTI_GetITStatus(EXTI_Line6) != RESET)
    {
        if(EXTI_Function[6]) EXTI_Function[6]();
        EXTI_ClearITPendingBit(EXTI_Line6);
    }
    if(EXTI_GetITStatus(EXTI_Line7) != RESET)
    {
        if(EXTI_Function[7]) EXTI_Function[7]();
        EXTI_ClearITPendingBit(EXTI_Line7);
    }
    if(EXTI_GetITStatus(EXTI_Line8) != RESET)
    {
        if(EXTI_Function[8]) EXTI_Function[8]();
        EXTI_ClearITPendingBit(EXTI_Line8);
    }
    if(EXTI_GetITStatus(EXTI_Line9) != RESET)
    {
        if(EXTI_Function[9]) EXTI_Function[9]();
        EXTI_ClearITPendingBit(EXTI_Line9);
    }

    if(EXTI_GetITStatus(EXTI_Line10) != RESET)
    {
        if(EXTI_Function[10]) EXTI_Function[10]();
        EXTI_ClearITPendingBit(EXTI_Line10);
    }
    if(EXTI_GetITStatus(EXTI_Line11) != RESET)
    {
        if(EXTI_Function[11]) EXTI_Function[11]();
        EXTI_ClearITPendingBit(EXTI_Line11);
    }
    if(EXTI_GetITStatus(EXTI_Line12) != RESET)
    {
        if(EXTI_Function[12]) EXTI_Function[12]();
        EXTI_ClearITPendingBit(EXTI_Line12);
    }
    if(EXTI_GetITStatus(EXTI_Line13) != RESET)
    {
        if(EXTI_Function[13]) EXTI_Function[13]();
        EXTI_ClearITPendingBit(EXTI_Line13);
    }
    if(EXTI_GetITStatus(EXTI_Line14) != RESET)
    {
        if(EXTI_Function[14]) EXTI_Function[14]();
        EXTI_ClearITPendingBit(EXTI_Line14);
    }
    if(EXTI_GetITStatus(EXTI_Line15) != RESET)
    {
        if(EXTI_Function[15]) EXTI_Function[15]();
        EXTI_ClearITPendingBit(EXTI_Line15);
    }
}
