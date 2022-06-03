/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "gpio.h"

const PinInfo_TypeDef PIN_MAP[PIN_MAX] =
{

    {GPIOA, TIM2, ADC1,  GPIO_Pin_0, 1, ADC_Channel_0}, /* PA0 */
    {GPIOA, TIM2, ADC1,  GPIO_Pin_1, 2, ADC_Channel_1}, /* PA1 */
    {GPIOA, TIM2, ADC1,  GPIO_Pin_2, 3, ADC_Channel_2}, /* PA2 */
    {GPIOA, TIM2, ADC1,  GPIO_Pin_3, 4, ADC_Channel_3}, /* PA3 */
    {GPIOA, NULL, ADC1,  GPIO_Pin_4, 0, ADC_Channel_4}, /* PA4 */
    {GPIOA, NULL, ADC1,  GPIO_Pin_5, 0, ADC_Channel_5}, /* PA5 */
    {GPIOA, TIM3, ADC1,  GPIO_Pin_6, 1, ADC_Channel_6}, /* PA6 */
    {GPIOA, TIM3, ADC1,  GPIO_Pin_7, 2, ADC_Channel_7}, /* PA7 */
    {GPIOA, TIM1, NULL,  GPIO_Pin_8, 1, ADC_Channel_X}, /* PA8 */
    {GPIOA, TIM1, NULL,  GPIO_Pin_9, 2, ADC_Channel_X}, /* PA9 */
    {GPIOA, TIM1, NULL, GPIO_Pin_10, 3, ADC_Channel_X}, /* PA10 */
    {GPIOA, TIM1, NULL, GPIO_Pin_11, 4, ADC_Channel_X}, /* PA11 */
    {GPIOA, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PA12 */
    {GPIOA, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PA13 */
    {GPIOA, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PA14 */
    {GPIOA, TIM2, NULL, GPIO_Pin_15, 1, ADC_Channel_X}, /* PA15 */

    {GPIOB, TIM3, ADC1,  GPIO_Pin_0, 3, ADC_Channel_8}, /* PB0 */
    {GPIOB, TIM3, ADC1,  GPIO_Pin_1, 4, ADC_Channel_9}, /* PB1 */
    {GPIOB, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PB2 */
    {GPIOB, TIM2, NULL,  GPIO_Pin_3, 2, ADC_Channel_X}, /* PB3 */
    {GPIOB, TIM3, NULL,  GPIO_Pin_4, 1, ADC_Channel_X}, /* PB4 */
    {GPIOB, TIM3, NULL,  GPIO_Pin_5, 2, ADC_Channel_X}, /* PB5 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_6, 1, ADC_Channel_X}, /* PB6 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_7, 2, ADC_Channel_X}, /* PB7 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_8, 3, ADC_Channel_X}, /* PB8 */
    {GPIOB, TIM4, NULL,  GPIO_Pin_9, 4, ADC_Channel_X}, /* PB9 */
    {GPIOB, TIM2, NULL, GPIO_Pin_10, 3, ADC_Channel_X}, /* PB10 */
    {GPIOB, TIM2, NULL, GPIO_Pin_11, 4, ADC_Channel_X}, /* PB11 */
    {GPIOB, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PB12 */
    {GPIOB, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PB13 */
    {GPIOB, TIM12, NULL, GPIO_Pin_14, 1, ADC_Channel_X},/* PB14 */
    {GPIOB, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PB15 */

    {GPIOC, NULL, ADC1,  GPIO_Pin_0, 0, ADC_Channel_10},/* PC0 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_1, 0, ADC_Channel_11},/* PC1 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_2, 0, ADC_Channel_12},/* PC2 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_3, 0, ADC_Channel_13},/* PC3 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_4, 0, ADC_Channel_14},/* PC4 */
    {GPIOC, NULL, ADC1,  GPIO_Pin_5, 0, ADC_Channel_15},/* PC5 */
    {GPIOC, TIM3, NULL,  GPIO_Pin_6, 1, ADC_Channel_X}, /* PC6 */
    {GPIOC, TIM3, NULL,  GPIO_Pin_7, 2, ADC_Channel_X}, /* PC7 */
    {GPIOC, TIM3, NULL,  GPIO_Pin_8, 3, ADC_Channel_X}, /* PC8 */
    {GPIOC, TIM3, NULL,  GPIO_Pin_9, 4, ADC_Channel_X}, /* PC9 */
    {GPIOC, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PC10 */
    {GPIOC, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PC11 */
    {GPIOC, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PC12 */
    {GPIOC, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PC13 */
    {GPIOC, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PC14 */
    {GPIOC, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PC15 */

    {GPIOD, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PD0 */
    {GPIOD, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PD1 */
    {GPIOD, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PD2 */
    {GPIOD, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PD3 */
    {GPIOD, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PD4 */
    {GPIOD, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X}, /* PD5 */
    {GPIOD, NULL, NULL,  GPIO_Pin_6, 0, ADC_Channel_X}, /* PD6 */
    {GPIOD, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PD7 */
    {GPIOD, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PD8 */
    {GPIOD, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PD9 */
    {GPIOD, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PD10 */
    {GPIOD, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PD11 */
    {GPIOD, TIM4, NULL, GPIO_Pin_12, 1, ADC_Channel_X}, /* PD12 */
    {GPIOD, TIM4, NULL, GPIO_Pin_13, 2, ADC_Channel_X}, /* PD13 */
    {GPIOD, TIM4, NULL, GPIO_Pin_14, 3, ADC_Channel_X}, /* PD14 */
    {GPIOD, TIM4, NULL, GPIO_Pin_15, 4, ADC_Channel_X}, /* PD15 */

    {GPIOE, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PE0 */
    {GPIOE, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PE1 */
    {GPIOE, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PE2 */
    {GPIOE, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PE3 */
    {GPIOE, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PE4 */
    {GPIOE, TIM9, NULL,  GPIO_Pin_5, 1, ADC_Channel_X}, /* PE5 */
    {GPIOE, TIM9, NULL,  GPIO_Pin_6, 2, ADC_Channel_X}, /* PE6 */
    {GPIOE, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PE7 */
    {GPIOE, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PE8 */
    {GPIOE, TIM1, NULL,  GPIO_Pin_9, 1, ADC_Channel_X}, /* PE9 */
    {GPIOE, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PE10 */
    {GPIOE, TIM1, NULL, GPIO_Pin_11, 2, ADC_Channel_X}, /* PE11 */
    {GPIOE, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PE12 */
    {GPIOE, TIM1, NULL, GPIO_Pin_13, 3, ADC_Channel_X}, /* PE13 */
    {GPIOE, TIM1, NULL, GPIO_Pin_14, 4, ADC_Channel_X}, /* PE14 */
    {GPIOE, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PE15 */

    {GPIOF, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PF0 */
    {GPIOF, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PF1 */
    {GPIOF, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PF2 */
    {GPIOF, NULL, ADC3,  GPIO_Pin_3, 0, ADC_Channel_9}, /* PF3 */
    {GPIOF, NULL, ADC3,  GPIO_Pin_4, 0, ADC_Channel_14},/* PF4 */
    {GPIOF, NULL, ADC3,  GPIO_Pin_5, 0, ADC_Channel_15},/* PF5 */
    {GPIOF, TIM10, ADC3,  GPIO_Pin_6, 1, ADC_Channel_4}, /* PF6 */
    {GPIOF, TIM11, ADC3,  GPIO_Pin_7, 1, ADC_Channel_5}, /* PF7 */
    {GPIOF, TIM13, ADC3,  GPIO_Pin_8, 1, ADC_Channel_6}, /* PF8 */
    {GPIOF, TIM14, ADC3,  GPIO_Pin_9, 1, ADC_Channel_7}, /* PF9 */
    {GPIOF, NULL, ADC3, GPIO_Pin_10, 0, ADC_Channel_8}, /* PF10 */
    {GPIOF, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PF11 */
    {GPIOF, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PF12 */
    {GPIOF, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PF13 */
    {GPIOF, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PF14 */
    {GPIOF, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PF15 */

    {GPIOG, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PG0 */
    {GPIOG, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PG1 */
    {GPIOG, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PG2 */
    {GPIOG, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PG3 */
    {GPIOG, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PG4 */
    {GPIOG, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X}, /* PG5 */
    {GPIOG, NULL, NULL,  GPIO_Pin_6, 0, ADC_Channel_X}, /* PG6 */
    {GPIOG, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PG7 */
    {GPIOG, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PG8 */
    {GPIOG, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PG9 */
    {GPIOG, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PG10 */
    {GPIOG, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PG11 */
    {GPIOG, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PG12 */
    {GPIOG, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PG13 */
    {GPIOG, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PG14 */
    {GPIOG, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PG15 */

    {GPIOH, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PH0 */
    {GPIOH, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PH1 */
    {GPIOH, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PH2 */
    {GPIOH, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PH3 */
    {GPIOH, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PH4 */
    {GPIOH, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X}, /* PH5 */
    {GPIOH, NULL, NULL,  GPIO_Pin_6, 0, ADC_Channel_X}, /* PH6 */
    {GPIOH, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PH7 */
    {GPIOH, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PH8 */
    {GPIOH, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PH9 */
    {GPIOH, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PH10 */
    {GPIOH, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PH11 */
    {GPIOH, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PH12 */
    {GPIOH, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PH13 */
    {GPIOH, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PH14 */
    {GPIOH, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PH15 */

    {GPIOI, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PI0 */
    {GPIOI, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PI1 */
    {GPIOI, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PI2 */
    {GPIOI, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PI3 */
    {GPIOI, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PI4 */
    {GPIOI, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X}, /* PI5 */
    {GPIOI, NULL, NULL,  GPIO_Pin_6, 0, ADC_Channel_X}, /* PI6 */
    {GPIOI, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PI7 */
    {GPIOI, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PI8 */
    {GPIOI, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PI9 */
    {GPIOI, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PI10 */
    {GPIOI, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PI11 */
    {GPIOI, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PI12 */
    {GPIOI, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PI13 */
    {GPIOI, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PI14 */
    {GPIOI, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PI15 */

    {GPIOJ, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PJ0 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PJ1 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PJ2 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PJ3 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PJ4 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X}, /* PJ5 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_6, 0, ADC_Channel_X}, /* PJ6 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PJ7 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PJ8 */
    {GPIOJ, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PJ9 */
    {GPIOJ, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PJ10 */
    {GPIOJ, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PJ11 */
    {GPIOJ, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PJ12 */
    {GPIOJ, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PJ13 */
    {GPIOJ, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PJ14 */
    {GPIOJ, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PJ15 */

    {GPIOK, NULL, NULL,  GPIO_Pin_0, 0, ADC_Channel_X}, /* PK0 */
    {GPIOK, NULL, NULL,  GPIO_Pin_1, 0, ADC_Channel_X}, /* PK1 */
    {GPIOK, NULL, NULL,  GPIO_Pin_2, 0, ADC_Channel_X}, /* PK2 */
    {GPIOK, NULL, NULL,  GPIO_Pin_3, 0, ADC_Channel_X}, /* PK3 */
    {GPIOK, NULL, NULL,  GPIO_Pin_4, 0, ADC_Channel_X}, /* PK4 */
    {GPIOK, NULL, NULL,  GPIO_Pin_5, 0, ADC_Channel_X}, /* PK5 */
    {GPIOK, NULL, NULL,  GPIO_Pin_6, 0, ADC_Channel_X}, /* PK6 */
    {GPIOK, NULL, NULL,  GPIO_Pin_7, 0, ADC_Channel_X}, /* PK7 */
    {GPIOK, NULL, NULL,  GPIO_Pin_8, 0, ADC_Channel_X}, /* PK8 */
    {GPIOK, NULL, NULL,  GPIO_Pin_9, 0, ADC_Channel_X}, /* PK9 */
    {GPIOK, NULL, NULL, GPIO_Pin_10, 0, ADC_Channel_X}, /* PK10 */
    {GPIOK, NULL, NULL, GPIO_Pin_11, 0, ADC_Channel_X}, /* PK11 */
    {GPIOK, NULL, NULL, GPIO_Pin_12, 0, ADC_Channel_X}, /* PK12 */
    {GPIOK, NULL, NULL, GPIO_Pin_13, 0, ADC_Channel_X}, /* PK13 */
    {GPIOK, NULL, NULL, GPIO_Pin_14, 0, ADC_Channel_X}, /* PK14 */
    {GPIOK, NULL, NULL, GPIO_Pin_15, 0, ADC_Channel_X}, /* PK15 */
};

/**
  * @brief  GPIO初始化
  * @param  GPIOx: GPIO地址
  * @param  GPIO_Pin_x: GPIO对应位
  * @param  GPIO_Mode_x: GPIO模式
  * @param  GPIO_Speed_x: GPIO速度
  * @retval 无
  */
void GPIOx_Init(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin_x, pinMode_TypeDef pinMode_x, GPIOSpeed_TypeDef GPIO_Speed_x)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    uint32_t RCC_AHB1Periph_GPIOx;
    GPIOMode_TypeDef GPIO_Mode_x;
    GPIOOType_TypeDef GPIO_OType_x;
    GPIOPuPd_TypeDef GPIO_PuPd_x;

    if(GPIOx == GPIOA)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOA;
    else if(GPIOx == GPIOB)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOB;
    else if(GPIOx == GPIOC)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOC;
    else if(GPIOx == GPIOD)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOD;
    else if(GPIOx == GPIOE)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOE;
    else if(GPIOx == GPIOF)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOF;
    else if(GPIOx == GPIOG)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOG;
    else if(GPIOx == GPIOH)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOH;
    else if(GPIOx == GPIOI)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOI;
    else if(GPIOx == GPIOJ)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOJ;
    else if(GPIOx == GPIOK)RCC_AHB1Periph_GPIOx = RCC_AHB1Periph_GPIOK;
    else return;

    if(pinMode_x == INPUT)
    {
        GPIO_Mode_x  = GPIO_Mode_IN;
        GPIO_PuPd_x  = GPIO_PuPd_NOPULL;
    }
    else if(pinMode_x == INPUT_PULLUP)
    {
        GPIO_Mode_x  = GPIO_Mode_IN;
        GPIO_PuPd_x  = GPIO_PuPd_UP;
    }
    else if(pinMode_x == INPUT_PULLDOWN)
    {
        GPIO_Mode_x  = GPIO_Mode_IN;
        GPIO_PuPd_x  = GPIO_PuPd_DOWN;
    }
    else if(pinMode_x == INPUT_ANALOG)
    {
        GPIO_Mode_x  = GPIO_Mode_AN;
        GPIO_PuPd_x  = GPIO_PuPd_NOPULL;
    }
    else if(pinMode_x == OUTPUT)
    {
        GPIO_Mode_x  = GPIO_Mode_OUT;
        GPIO_OType_x = GPIO_OType_PP;
        GPIO_PuPd_x  = GPIO_PuPd_NOPULL;
    }
    else if(pinMode_x == OUTPUT_OPEN_DRAIN)
    {
        GPIO_Mode_x  = GPIO_Mode_OUT;
        GPIO_OType_x = GPIO_OType_OD;
        GPIO_PuPd_x  = GPIO_PuPd_NOPULL;
    }
    else if(pinMode_x == OUTPUT_AF)
    {
        GPIO_Mode_x  = GPIO_Mode_AF;
        GPIO_OType_x = GPIO_OType_PP;
        GPIO_PuPd_x  = GPIO_PuPd_NOPULL;
    }
    else
    {
        return;
    }

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_x;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_x;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_x;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_x;

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOx, ENABLE);
    GPIO_Init(GPIOx, &GPIO_InitStructure);
}

/**
  * @brief  获取当前引脚对应的GPIOx编号
  * @param  Pin: 引脚编号
  * @retval 无
  */
uint8_t GPIO_GetPortNum(uint8_t Pin)
{
    if(PIN_MAP[Pin].GPIOx == GPIOA)return 0;
    else if(PIN_MAP[Pin].GPIOx == GPIOB)return 1;
    else if(PIN_MAP[Pin].GPIOx == GPIOC)return 2;
    else if(PIN_MAP[Pin].GPIOx == GPIOD)return 3;
    else if(PIN_MAP[Pin].GPIOx == GPIOE)return 4;
    else if(PIN_MAP[Pin].GPIOx == GPIOF)return 5;
    else if(PIN_MAP[Pin].GPIOx == GPIOG)return 6;
    else if(PIN_MAP[Pin].GPIOx == GPIOH)return 7;
    else if(PIN_MAP[Pin].GPIOx == GPIOI)return 8;
    else if(PIN_MAP[Pin].GPIOx == GPIOJ)return 9;
    else if(PIN_MAP[Pin].GPIOx == GPIOK)return 10;
    else return 0xFF;
}

/**
  * @brief  获取当前引脚对应的 PinSource
  * @param  GPIO_Pin_x: GPIO对应位
  * @retval 无
  */
uint8_t GPIO_GetPinSource(uint16_t GPIO_Pin_x)
{
    uint16_t PinSource = 0;
    while(GPIO_Pin_x > 1)
    {
        GPIO_Pin_x >>= 1;
        PinSource++;
    }
    return PinSource;
}

/**
  * @brief  获取当前引脚对应的编号
  * @param  Pin: 引脚编号
  * @retval 无
  */
uint8_t GPIO_GetPinNum(uint8_t Pin)
{
    return GPIO_GetPinSource(PIN_MAP[Pin].GPIO_Pin_x);
}