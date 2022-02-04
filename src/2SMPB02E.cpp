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

O2SMPB02E::O2SMPB02E(PinName i2c_sda, PinName i2c_scl)
{
}

bool O2SMPB02E::init()
{
    if (reset() != SUCCESS) {
        return false;
    }
    if (read_chip_id() != SUCCESS) {
        return false;
    }
}

int O2SMPB02E::read_chip_id()
{
    char chip_id = 0;
    if (i2c_read_register(RegisterAddress::CHIP_ID, &chip_id) != SUCCESS) {
        return FAILURE;
    }
    return (chip_id != HW_CHIP_ID) ? FAILURE : SUCCESS;
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
    return SUCCESS;
}

int O2SMPB02E::i2c_write_register(RegisterAddress register_address, char value)
{
    return SUCCESS;
}

} // namespace sixtron
