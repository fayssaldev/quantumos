/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#include "Tone.h"

static TIM_TypeDef *ToneTimer_Last = 0, *ToneTimer = ToneTimer_Default;
static uint8_t tone_State = Off;
static uint8_t tone_Pin;
static uint32_t tone_StopTimePoint;


static void tone_TimerHandler()
{
    togglePin(tone_Pin);
    if(millis() > tone_StopTimePoint && !tone_State)
    {
        noTone(tone_Pin);
    }
}


void toneSetTimer(TIM_TypeDef* TIMx)
{
    if(IS_TIM_ALL_PERIPH(TIMx))
        ToneTimer = TIMx;
}


void tone(uint8_t Pin, uint32_t freq, uint32_t Time_ms)
{
    if(freq == 0 || Time_ms == 0 || freq > 500000)
    {
        noTone(Pin);
        return;
    }
    tone(Pin, freq);
    tone_StopTimePoint = millis() + Time_ms;
    tone_State = Off;
}


void tone(uint8_t Pin, uint32_t freq)
{
    if(freq == 0 || freq > 500000)
    {
        noTone(Pin);
        return;
    }
    tone_Pin = Pin;
    tone_State = On;

    if(ToneTimer != ToneTimer_Last)
    {
        Timer_SetInterruptBase(
            ToneTimer, 
            0xFF, 0xFF,
            tone_TimerHandler, 
            0, 0
        );
        Timer_SetInterruptTimeUpdate(ToneTimer, (500000.0f / freq));
        TIM_Cmd(ToneTimer, ENABLE);
        ToneTimer_Last = ToneTimer;
    }
    else
    {
        Timer_SetInterruptTimeUpdate(ToneTimer, (500000.0f / freq));
        TIM_Cmd(ToneTimer, ENABLE);
    }
}


void noTone(uint8_t Pin)
{
    TIM_Cmd(ToneTimer, DISABLE);
    digitalWrite(Pin, LOW);
    tone_State = Off;
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
