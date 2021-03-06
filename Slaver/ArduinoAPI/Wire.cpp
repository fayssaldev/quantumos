/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/


#include "Wire.h"

#define I2C_WRITE 0
#define I2C_READ  1

/* low level conventions:
 * - SDA/SCL idle high (expected high)
 * - always start with i2c_delay rather than end
 */

void TwoWire::set_scl(bool state) {
    I2C_DELAY(this->i2c_delay);
    digitalWrite(this->scl_pin, state);
    //Allow for clock stretching - dangerous currently
    if (state == HIGH) {
        while(digitalRead(this->scl_pin) == 0);
    }
}

void TwoWire::set_sda(bool state) {
    I2C_DELAY(this->i2c_delay);
    digitalWrite(this->sda_pin, state);
}

void TwoWire::i2c_start() {
#ifdef FULL_SPEED_I2C
    digitalWrite_LOW(this->sda_pin);
    digitalWrite_LOW(this->scl_pin);
#else
    set_sda(LOW);
    set_scl(LOW);
#endif
}

void TwoWire::i2c_stop() {
#ifdef FULL_SPEED_I2C
    digitalWrite_LOW(this->sda_pin);
    digitalWrite_HIGH(this->scl_pin);
    digitalWrite_HIGH(this->sda_pin);
#else
    set_sda(LOW);
    set_scl(HIGH);
    set_sda(HIGH);
#endif
}

bool TwoWire::i2c_get_ack() {
#ifdef FULL_SPEED_I2C
    digitalWrite_LOW(this->scl_pin);
    digitalWrite_HIGH(this->sda_pin);
    digitalWrite_HIGH(this->scl_pin);
#else
    set_scl(LOW);
    set_sda(HIGH);
    set_scl(HIGH);
#endif

    bool ret = !digitalRead(this->sda_pin);
#ifdef FULL_SPEED_I2C
    digitalWrite_LOW(this->scl_pin);
#else
    set_scl(LOW);
#endif
    return ret;
}

void TwoWire::i2c_send_ack() {
#ifdef FULL_SPEED_I2C
    digitalWrite_LOW(this->sda_pin);
    digitalWrite_HIGH(this->scl_pin);
    digitalWrite_LOW(this->scl_pin);
#else
    set_sda(LOW);
    set_scl(HIGH);
    set_scl(LOW);
#endif
}

void TwoWire::i2c_send_nack() {
#ifdef FULL_SPEED_I2C
    digitalWrite_HIGH(this->sda_pin);
    digitalWrite_HIGH(this->scl_pin);
    digitalWrite_LOW(this->scl_pin);
#else
    set_sda(HIGH);
    set_scl(HIGH);
    set_scl(LOW);
#endif
}

uint8_t TwoWire::i2c_shift_in() {
    uint8_t data = 0;
#ifdef FULL_SPEED_I2C
    digitalWrite_HIGH(this->sda_pin);
#else
    set_sda(HIGH);
#endif
    int i;
    for (i = 0; i < 8; i++)
    {
#ifdef FULL_SPEED_I2C
        digitalWrite_HIGH(this->scl_pin);
        data |= digitalRead(this->sda_pin) << (7 - i);
        digitalWrite_LOW(this->scl_pin);
#else
        set_scl(HIGH);
        data |= digitalRead(this->sda_pin) << (7 - i);
        set_scl(LOW);
#endif
    }

    return data;
}

void TwoWire::i2c_shift_out(uint8_t val) {
    int i;
    for (i = 0; i < 8; i++) {
        set_sda(!!(val & (1 << (7 - i)) ) );
#ifdef FULL_SPEED_I2C
        digitalWrite_HIGH(this->scl_pin);
        digitalWrite_LOW(this->scl_pin);
#else
        set_scl(HIGH);
        set_scl(LOW);
#endif
    }
}

uint8_t TwoWire::process(void) {
    itc_msg.xferred = 0;

    uint8_t sla_addr = (itc_msg.addr << 1);
    if (itc_msg.flags == I2C_MSG_READ) {
        sla_addr |= I2C_READ;
    }
    i2c_start();
    // shift out the address we're transmitting to
    i2c_shift_out(sla_addr);
    if (!i2c_get_ack())
    {
        i2c_stop();// Roger Clark. 20141110 added to set clock high again, as it will be left in a low state otherwise
        return ENACKADDR;
    }
    // Recieving
    if (itc_msg.flags == I2C_MSG_READ) {
        while (itc_msg.xferred < itc_msg.length) {
            itc_msg.data[itc_msg.xferred++] = i2c_shift_in();
            if (itc_msg.xferred < itc_msg.length)
            {
                i2c_send_ack();
            }
            else
            {
                i2c_send_nack();
            }
        }
    }
    // Sending
    else {
        for (uint8_t i = 0; i < itc_msg.length; i++) {
            i2c_shift_out(itc_msg.data[i]);
            if (!i2c_get_ack())
            {
                i2c_stop();// Roger Clark. 20141110 added to set clock high again, as it will be left in a low state otherwise
                return ENACKTRNS;
            }
            itc_msg.xferred++;
        }
    }
    i2c_stop();
    return SUCCESS;
}

// TODO: Add in Error Handling if pins is out of range for other Maples
// TODO: Make delays more capable
TwoWire::TwoWire(uint8_t scl, uint8_t sda, uint8_t delay) : i2c_delay(delay) {
    this->scl_pin = scl;
    this->sda_pin = sda;
}

void TwoWire::begin(uint8_t self_addr) {
    tx_buf_idx = 0;
    tx_buf_overflow = false;
    rx_buf_idx = 0;
    rx_buf_len = 0;
    pinMode(this->scl_pin, OUTPUT_OPEN_DRAIN);
    pinMode(this->sda_pin, OUTPUT_OPEN_DRAIN);
    set_scl(HIGH);
    set_sda(HIGH);
}

TwoWire::~TwoWire() {
    this->scl_pin = 0;
    this->sda_pin = 0;
}

// Declare the instance that the users of the library can use
TwoWire Wire(SCL_Pin, SDA_Pin, SOFT_FAST);
//TwoWire Wire(PB6, PB7, SOFT_STANDARD);
