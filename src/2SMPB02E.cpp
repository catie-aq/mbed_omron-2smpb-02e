/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#include "2SMPB02E/2SMPB02E.h"

namespace sixtron {

namespace {
#define SUCCESS 0
#define FAILURE -1

#define SOFTRESET_CMD 0xE6
#define HW_CHIP_ID 0x5C
}

O2SMPB02E::O2SMPB02E(PinName i2c_sda, PinName i2c_scl, I2CAddress i2c_address):
        _i2c(i2c_sda, i2c_scl), _i2c_address(i2c_address)
{
}

bool O2SMPB02E::init()
{
    reset();
    ThisThread::sleep_for(10ms);
    if (read_chip_id() != SUCCESS) {
        return false;
    }

    return true;
}

int O2SMPB02E::read_chip_id()
{
    char chip_id = 0;
    if (i2c_read_register(RegisterAddress::CHIP_ID, &chip_id) != SUCCESS) {
        return FAILURE;
    }
    return (chip_id == HW_CHIP_ID) ? SUCCESS : FAILURE;
}

int O2SMPB02E::reset()
{
    if (i2c_write_register(RegisterAddress::RESET, SOFTRESET_CMD) != SUCCESS) {
        return FAILURE;
    }
    return SUCCESS;
}

int O2SMPB02E::i2c_read_register(RegisterAddress register_address, char *value)
{
    static char data;
    data = static_cast<char>(register_address);
    if (_i2c.write(static_cast<int>(_i2c_address) << 1, &data, 1) != SUCCESS) {
        return FAILURE;
    }
    char *char_value = reinterpret_cast<char *>(value);
    if (_i2c.read(static_cast<int>(_i2c_address) << 1, char_value, 1) != SUCCESS) {
        return FAILURE;
    }

    return SUCCESS;
}

int O2SMPB02E::i2c_write_register(RegisterAddress register_address, char value)
{
    char data[2];
    data[0] = static_cast<char>(register_address);
    data[1] = value;
    if(_i2c.write(static_cast<int>(_i2c_address) << 1, data, 2)) {
        return FAILURE;
    }
    return SUCCESS;
}

} // namespace sixtron
