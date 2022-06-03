/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "adc.h"


void ADCx_Init(ADC_TypeDef* ADCx)
{
    ADC_InitTypeDef ADC_InitStructure;
    if(ADCx == ADC1)RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
    ADC_DeInit(ADCx);
    ADC_StructInit(&ADC_InitStructure);
    ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
    ADC_InitStructure.ADC_ContinuousConvMode = ENABLE; 
    ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward; 
    ADC_Init(ADCx, &ADC_InitStructure);
    ADC_Cmd(ADCx, ENABLE);
    while(!ADC_GetFlagStatus(ADCx, ADC_FLAG_ADEN));
}


uint16_t Get_ADC(ADC_TypeDef* ADCx, uint32_t ADC_Channel)
{
    uint16_t ADCConvertedValue;
    //Select channel to scan
    ADC_ChannelConfig(ADCx, ADC_Channel, ADC_SampleTime_41_5Cycles);
    // ADC1 regular Software Start Conv
    ADC_StartOfConversion(ADCx);
    // Wait for end of conversion
    while(ADC_GetFlagStatus(ADCx, ADC_FLAG_EOC) == RESET);
    //Get value
    ADCConvertedValue = ADC_GetConversionValue(ADCx);
    //Stop conversion and return ADC value.
    ADC_StopOfConversion(ADCx);
    return(ADCConvertedValue);
}
