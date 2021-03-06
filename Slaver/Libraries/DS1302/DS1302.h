/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/
#ifndef DS1302_h
#define DS1302_h

extern "C"
{
#include "FileGroup.h"
}
/**
 * Convenience register constants
 */
#define SEC_REG  0
#define MIN_REG  1
#define HR_REG   2
#define DATE_REG 3
#define MON_REG  4
#define DAY_REG  5
#define YR_REG   6
#define WP_REG   7

/**
 * Type for a register number
 */
typedef uint8_t reg_t;


/**
 * Class representing a particular time and date.
 */
class Time
{
public:
  uint8_t sec;
  uint8_t min;
  uint8_t hr;
  uint8_t date;
  uint8_t mon;
  uint8_t day;
  uint16_t yr;

  /**
   * Default constructor.
   *
   * Creates a time object dated to Saturday Jan 1, 2000 at 00:00:00.
   * The date and time can be changed by editing the instance variables.
   */
  Time();

  /**
   * Create a Time object with a given time.
   *
   * Args:
   *   yr: year. Range: {2000, ..., 2099}.
   *   mon: month. Range: {1, ..., 12}.
   *   date: date (of the month). Range: {1, ..., 31}.
   *   hr: hour. Range: {0, ..., 23}.
   *   min: minutes. Range: {0, ..., 59}.
   *   sec: seconds. Range: {0, ..., 59}.
   *   day: day of the week. Sunday is 1. Range: {1, ..., 7}.
   */
  Time(uint16_t yr, uint8_t mon, uint8_t date,
       uint8_t hr, uint8_t min, uint8_t sec,
       uint8_t day);
};


/**
 * Talk to a Dallas Semiconductor DS1302 Real Time Clock (RTC) chip.
 */
class DS1302
{
public:
  /**
   * Constructor.
   *
   * Args:
   *   ce_pin: CE pin number
   *   io_pin: IO pin number
   *   sclk_pin: SCLK pin number
   */
  DS1302(int ce_pin, int io_pin, int sclk_pin);

  /**
   * Read register byte value.
   *
   * Args:
   *   reg: register number
   *
   * Returns:
   *   register value
   */
  uint8_t read_register(reg_t reg);

  /**
   * Write byte into register.
   *
   * Args:
   *   reg: register number
   *   value: byte to write
   */
  void write_register(reg_t reg, uint8_t value);

  /**
   * Enable or disable write protection on chip.
   *
   * Args:
   *   enable: true to enable, false to disable.
   */
  void write_protect(bool enable);

  /**
   * Set or clear clock halt flag.
   *
   * Args:
   *   value: true to set halt flag, false to clear.
   */
  void halt(bool value);

  /**
   * Get individual pieces of the time and date.
   */
  uint8_t seconds();
  uint8_t minutes();
  uint8_t hour();
  uint8_t date();
  uint8_t month();
  uint8_t day();
  uint16_t year();

  /**
   * Get the current time and date in a Time object.
   *
   * Returns:
   *   Time object.
   */
  Time time();

  /**
   * Individually set pieces of the date and time.
   *
   * The arguments here follow the rules specified above in Time::Time(...).
   */
  void seconds(uint8_t sec);
  void minutes(uint8_t min);
  void hour(uint8_t hr);
  void date(uint8_t date);
  void month(uint8_t mon);
  void day(uint8_t day);
  void year(uint16_t yr);

  /**
   * Set the time and date to the instant specified in a given Time object.
   *
   * Args:
   *   t: Time object to use
   */
  void time(Time t);

private:
  int _ce_pin;
  int _io_pin;
  int _sclk_pin;

  /**
   * Shift out a value to the IO pin.
   *
   * Side effects: sets _io_pin as OUTPUT.
   *
   * Args:
   *   value: byte to shift out
   */
  void _write_out(uint8_t value);

  /**
   * Read in a byte from the IO pin.
   *
   * Side effects: sets _io_pin to INPUT.
   *
   * Returns:
   *   byte read in
   */
  uint8_t _read_in();

  /**
   * Get a binary-coded decimal register and return it in decimal.
   *
   * Args:
   *   reg: register number
   *   high_bit: number of the bit containing the last BCD value ({0, ..., 7})
   *
   * Returns:
   *   decimal value
   */
  uint8_t _register_bcd_to_dec(reg_t reg, uint8_t high_bit);
  uint8_t _register_bcd_to_dec(reg_t reg);

  /**
   * Set a register with binary-coded decimal converted from a given value.
   *
   * Args:
   *   reg: register number
   *   value: decimal value to convert to BCD
   *   high_bit: highest bit in the register allowed to contain BCD value
   */
  void _register_dec_to_bcd(reg_t reg, uint8_t value, uint8_t high_bit);
  void _register_dec_to_bcd(reg_t reg, uint8_t value);
};

#endif
