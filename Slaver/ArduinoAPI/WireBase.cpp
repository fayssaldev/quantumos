/*
    By : Fayssal Chokri <fayssalchokri@symantec.com>
    2021-2022 MIT Licence
*/


#include "WireBase.h"

void WireBase::begin(uint8_t self_addr) {
    tx_buf_idx = 0;
    tx_buf_overflow = false;
    rx_buf_idx = 0;
    rx_buf_len = 0;
}

void WireBase::setClock(uint32_t clock)
{

}

void WireBase::beginTransmission(uint8_t slave_address) {
    itc_msg.addr = slave_address;
    itc_msg.data = &tx_buf[tx_buf_idx];
    itc_msg.length = 0;
    itc_msg.flags = 0;
}

void WireBase::beginTransmission(int slave_address) {
    beginTransmission((uint8_t)slave_address);
}

uint8_t WireBase::endTransmission(void) {
    uint8_t retVal;
    if (tx_buf_overflow) {
        return EDATA;
    }
    retVal = process();// Changed so that the return value from process is returned by this function see also the return line below
    tx_buf_idx = 0;
    tx_buf_overflow = false;
    return retVal;//SUCCESS;
}

//TODO: Add the ability to queue messages (adding a boolean to end of function
// call, allows for the Arduino style to stay while also giving the flexibility
// to bulk send
uint8_t WireBase::requestFrom(uint8_t address, int num_bytes) {
    if (num_bytes > WIRE_BUFSIZ) {
        num_bytes = WIRE_BUFSIZ;
    }
    itc_msg.addr = address;
    itc_msg.flags = I2C_MSG_READ;
    itc_msg.length = num_bytes;
    itc_msg.data = &rx_buf[rx_buf_idx];
    process();
    rx_buf_len += itc_msg.xferred;
    itc_msg.flags = 0;
    return rx_buf_len;
}

uint8_t WireBase::requestFrom(int address, int numBytes) {
    return WireBase::requestFrom((uint8_t)address, numBytes);
}

void WireBase::write(uint8_t value) {
    if (tx_buf_idx == WIRE_BUFSIZ) {
        tx_buf_overflow = true;
        return;
    }
    tx_buf[tx_buf_idx++] = value;
    itc_msg.length++;
}

void WireBase::write(uint8_t* buf, int len) {
    for (uint8_t i = 0; i < len; i++) {
        write(buf[i]);
    }
}

void WireBase::write(int value) {
    write((uint8_t)value);
}

void WireBase::write(int* buf, int len) {
    write((uint8_t*)buf, (uint8_t)len);
}

void WireBase::write(char* buf) {
    uint8_t *ptr = (uint8_t*)buf;
    while (*ptr) {
        write(*ptr);
        ptr++;
    }
}

uint8_t WireBase::available() {
    return rx_buf_len - rx_buf_idx;
}

uint8_t WireBase::read() {
    if (rx_buf_idx == rx_buf_len) {
        rx_buf_idx = 0;
        rx_buf_len = 0;
        return 0;
    } else if (rx_buf_idx == (rx_buf_len - 1)) {
        uint8_t temp = rx_buf[rx_buf_idx];
        rx_buf_idx = 0;
        rx_buf_len = 0;
        return temp;
    }
    return rx_buf[rx_buf_idx++];
}
