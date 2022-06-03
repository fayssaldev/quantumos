/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "Tone.h"
#include "Arduino.h"

static TIM_TypeDef *ToneTimer_Last = 0, *ToneTimer = ToneTimer_Default;
static bool IsToneEnable = false;
static uint8_t tone_Pin;
static uint32_t tone_StopTimePoint;


void tone_TimerHandler()
{
    togglePin(tone_Pin);
    if(millis() > tone_StopTimePoint && !IsToneEnable)
    {
        noTone(tone_Pin);
    }
}


void toneSetTimer(TIM_TypeDef* TIMx)
{
    ToneTimer = TIMx;
}


void tone(uint8_t Pin, uint32_t freq, uint32_t Time_ms)
{
    if(!IS_PIN(Pin))
        return;

    if(freq == 0 || freq > 500000)
    {
        noTone(Pin);
        return;
    }
    tone(Pin, freq);
    tone_StopTimePoint = millis() + Time_ms;
    IsToneEnable = false;
}


void tone(uint8_t Pin, uint32_t freq)
{
    if(!IS_PIN(Pin))
        return;

    if(freq == 0 || freq > 500000)
    {
        noTone(Pin);
        return;
    }
    tone_Pin = Pin;
    IsToneEnable = true;

    if(ToneTimer != ToneTimer_Last)
    {
        Timer_Init(ToneTimer, (500000.0 / freq), tone_TimerHandler, 0);
        TIM_Cmd(ToneTimer, ENABLE);
        ToneTimer_Last = ToneTimer;
    }
    else
    {
        TimerSet_InterruptTimeUpdate(ToneTimer, 500000.0 / freq);
        TIM_Cmd(ToneTimer, ENABLE);
    }
}


void noTone(uint8_t Pin)
{
    TIM_Cmd(ToneTimer, DISABLE);
    digitalWrite_LOW(Pin);
    IsToneEnable = Off;
}


void toneBlock(uint8_t Pin, uint32_t freq, uint32_t Time_ms)
{
    uint32_t TimePoint = millis() + Time_ms;
    uint32_t dlyus = 500000 / freq;
    if(freq == 0)return;
    do
    {
        digitalWrite_HIGH(Pin);
        delayMicroseconds(dlyus);
        digitalWrite_LOW(Pin);
        delayMicroseconds(dlyus);
    }
    while(millis() < TimePoint);
    digitalWrite_LOW(Pin);
}


void toneBlock_Volumn(uint8_t Pin, uint32_t freq, uint32_t Time_ms, uint32_t vol)
{
    uint32_t TimePoint = millis() + Time_ms;
    uint32_t dlyus = 500000 / freq;
    uint32_t dlHigh = dlyus * vol / 100;
    uint32_t dlLow = 2 * dlyus - dlHigh;
    if(freq == 0)return;
    do
    {
        digitalWrite_HIGH(Pin);
        delayMicroseconds(dlHigh);
        digitalWrite_LOW(Pin);
        delayMicroseconds(dlLow);
    }
    while(millis() < TimePoint);
    digitalWrite_LOW(Pin);
}


void toneBlock_Volumn_us(uint8_t Pin, uint32_t freq, uint32_t Time_us, uint32_t vol)
{
    uint32_t TimePoint = micros() + Time_us;
    uint32_t dlyus = 500000 / freq;
    uint32_t dlHigh = dlyus * vol / 100;
    uint32_t dlLow = 2 * dlyus - dlHigh;
    if(freq == 0)return;
    do
    {
        digitalWrite_HIGH(Pin);
        delayMicroseconds(dlHigh);
        digitalWrite_LOW(Pin);
        delayMicroseconds(dlLow);
    }
    while(micros() < TimePoint);
    digitalWrite_LOW(Pin);
}
