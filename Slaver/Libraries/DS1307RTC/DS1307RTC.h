/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/

#ifndef DS1307RTC_h
#define DS1307RTC_h

#include "Wire.h"
#include "Time/TimeLib.h"

// library interface description
class DS1307RTC
{
  // user-accessible "public" interface
  public:
    DS1307RTC();
    static time_t get();
    static bool set(time_t t);
    static bool read(tmElements_t &tm);
    static bool write(tmElements_t &tm);
    static bool chipPresent() { return exists; }

  private:
    static bool exists;
    static uint8_t dec2bcd(uint8_t num);
    static uint8_t bcd2dec(uint8_t num);
};

#ifdef RTC
#undef RTC // workaround for Arduino Due, which defines "RTC"...
#endif

extern DS1307RTC RTC;

#endif
 

