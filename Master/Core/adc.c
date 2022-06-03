/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "adc.h"
#include "Arduino.h"

#define ADC_DMA_REGMAX 18


static uint8_t ADC_DMA_RegCnt = 0;


static uint16_t ADC_DMA_RegChannelList[ADC_DMA_REGMAX] = {0};


static uint16_t ADC_DMA_ConvertedValue[ADC_DMA_REGMAX] = {0};


static int16_t ADC_DMA_SearchChannel(uint16_t ADC_Channel)
{
    uint8_t index;

    for(index = 0; index < ADC_DMA_RegCnt; index++)
    {
        if(ADC_Channel == ADC_DMA_RegChannelList[index])
        {
            return index;
        }
    }
    return -1;
}


int16_t ADC_DMA_Register(uint8_t ADC_Channel)
{
    /
    static uint8_t IsInit = 0;
    if(!IsInit)
    {
        uint8_t i;
        for(i = 0; i < ADC_DMA_REGMAX; i++)
        {
            ADC_DMA_RegChannelList[i] = 0xFF;
        }
        IsInit = 1;
    }

    
    if(!IS_ADC_CHANNEL(ADC_Channel))
        return -1;

    
    if(ADC_DMA_SearchChannel(ADC_Channel) != -1)
        return -2;

    
    if(ADC_DMA_RegCnt >= ADC_DMA_REGMAX)
        return -3;

    
    ADC_DMA_RegChannelList[ADC_DMA_RegCnt] = ADC_Channel;

    
    ADC_DMA_RegCnt++;

    return ADC_DMA_RegCnt - 1;
}

static void ADC_DMA_Config()
{
    DMA_InitTypeDef DMA_InitStructure;

    DMA_DeInit(DMA2_Stream0);

    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA2, ENABLE); 
    while(DMA_GetCmdStatus(DMA2_Stream0) != DISABLE); 


    DMA_InitStructure.DMA_Channel = DMA_Channel_0;
    DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)&ADC1->DR; 
    DMA_InitStructure.DMA_Memory0BaseAddr    = (uint32_t)ADC_DMA_ConvertedValue;
    DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralToMemory;
    DMA_InitStructure.DMA_BufferSize = ADC_DMA_RegCnt;
    DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
    DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;
    DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
    DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
    DMA_InitStructure.DMA_Priority = DMA_Priority_High;
    DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
    DMA_InitStructure.DMA_FIFOMode = DMA_FIFOMode_Disable;
    DMA_InitStructure.DMA_FIFOThreshold = DMA_FIFOThreshold_HalfFull;
    DMA_InitStructure.DMA_MemoryBurst = DMA_MemoryBurst_Single;
    DMA_InitStructure.DMA_PeripheralBurst = DMA_PeripheralBurst_Single;
    DMA_Init(DMA2_Stream0, &DMA_InitStructure); 
    DMA_Cmd(DMA2_Stream0, ENABLE); 
}


void ADC_DMA_Init()
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef ADC_InitStructure;
    uint16_t index;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 

    ADC_DMA_Config();

    ADC_DeInit();
    
    
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
    ADC_CommonInitStructure.ADC_Mode          = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_Prescaler     = ADC_Prescaler_Div6;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_20Cycles;
    ADC_CommonInit(&ADC_CommonInitStructure);
    ADC_InitStructure.ADC_Resolution  = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ScanConvMode = ENABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign    = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_NbrOfConversion = ADC_DMA_RegCnt;
    ADC_Init(ADC1, &ADC_InitStructure); 

    ADC_Cmd(ADC1, ENABLE); 
    
    for(index = 0; index < ADC_DMA_RegCnt; index++)
    {
        ADC_RegularChannelConfig(
            ADC1,
            ADC_DMA_RegChannelList[index],
            index + 1,
            ADC_SampleTime_480Cycles
        );

        if(ADC_DMA_RegChannelList[index] == ADC_Channel_TempSensor)
        {
            ADC_TempSensorVrefintCmd(ENABLE);
        }
    }
    
    ADC_DMARequestAfterLastTransferCmd(ADC1, ENABLE); 
    ADC_DMACmd(ADC1, ENABLE); 
    ADC_SoftwareStartConv(ADC1);
}

uint16_t ADC_DMA_GetValue(uint8_t ADC_Channel)
{
    int16_t index;

    if(!IS_ADC_CHANNEL(ADC_Channel))
        return 0;

    index = ADC_DMA_SearchChannel(ADC_Channel);
    if(index == -1)
        return 0;

    return ADC_DMA_ConvertedValue[index];
}

void ADCx_Init(ADC_TypeDef* ADCx)
{
    ADC_CommonInitTypeDef ADC_CommonInitStructure;
    ADC_InitTypeDef       ADC_InitStructure;

    if(ADCx == ADC1)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC1, DISABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); 
    }
    else if(ADCx == ADC2)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC2, DISABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE); 
    }
    else if(ADCx == ADC3)
    {
        RCC_APB2PeriphResetCmd(RCC_APB2Periph_ADC3, DISABLE);
        RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC3, ENABLE); 
    }

    ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
    ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled; 
    ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div4;/*36Mhz*/
    ADC_CommonInit(&ADC_CommonInitStructure);

    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;//12
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;//
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;//
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;//
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;//
    ADC_InitStructure.ADC_NbrOfConversion = 1;//1
    ADC_Init(ADCx, &ADC_InitStructure);//


    ADC_Cmd(ADCx, ENABLE);//
}

uint16_t ADCx_GetValue(ADC_TypeDef* ADCx, uint8_t ADC_Channel)
{
    ADC_RegularChannelConfig(ADCx, ADC_Channel, 1, ADC_SampleTime_144Cycles);
    ADC_SoftwareStartConv(ADCx);
    while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC));
    return ADC_GetConversionValue(ADCx);
}
