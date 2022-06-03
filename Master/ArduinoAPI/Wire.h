/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/


#ifndef _WIRE_H_
#define _WIRE_H_

#include "WireBase.h"

/*
 * On the Maple, let the default pins be in the same location as the Arduino
 * pins
 */
#ifndef SDA_Pin
#define SDA_Pin PA11
#endif

#ifndef SCL_Pin
#define SCL_Pin PA12
#endif

#define SOFT_STANDARD 27
#define SOFT_FAST 0

//#define FULL_SPEED_I2C

#ifdef FULL_SPEED_I2C
#define I2C_DELAY(x) {}
#else
#define I2C_DELAY(x) delayMicroseconds(x)
#endif

#define BUFFER_LENGTH 32

class TwoWire : public WireBase {
public:
    uint8_t       i2c_delay;
    uint8_t       scl_pin;
    uint8_t       sda_pin;

    /*
     * Sets the SCL line to HIGH/LOW and allow for clock stretching by slave
     * devices
     */
    void set_scl(bool);

    /*
     * Sets the SDA line to HIGH/LOW
     */
    void set_sda(bool);

    /*
     * Creates a Start condition on the bus
     */
    void i2c_start();

    /*
     * Creates a Stop condition on the bus
     */
    void  i2c_stop();

    /*
     * Gets an ACK condition from a slave device on the bus
     */
    bool i2c_get_ack();

    /*
     * Creates a ACK condition on the bus
     */
    void i2c_send_ack();

    /*
     * Creates a NACK condition on the bus
     */
    void i2c_send_nack();

    /*
     * Shifts in the data through SDA and clocks SCL for the slave device
     */
    uint8_t i2c_shift_in();

    /*
     * Shifts out the data through SDA and clocks SCL for the slave device
     */
    void i2c_shift_out(uint8_t);
protected:
    /*
     * Processes the incoming I2C message defined by WireBase
     */

    virtual uint8_t process();
public:
    /*
     * Accept pin numbers for SCL and SDA lines. Set the delay needed
     * to create the timing for I2C's Standard Mode and Fast Mode.
     */
    TwoWire(uint8_t scl = SCL_Pin, uint8_t sda = SDA_Pin, uint8_t delay = SOFT_STANDARD);

    /*
     * Sets pins SDA and SCL to OUPTUT_OPEN_DRAIN, joining I2C bus as
     * master. This function overwrites the default behaviour of
     * .begin(uint8_t) in WireBase
     */
    //void begin(uint8_t self_addr);
    virtual void begin(uint8_t = 0x00);
    /*
     * If object is destroyed, set pin numbers to 0.
     */
    ~TwoWire();
};

extern TwoWire Wire;

#endif // _WIRE_H_
