/*
 * Copyright (c) 2022, CATIE
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef CATIE_SIXTRON_2SMPB02E_H_
#define CATIE_SIXTRON_2SMPB02E_H_

#include "mbed.h"

namespace sixtron {

class O2SMPB02E {
public:
    enum class I2CAddress : char {
        Address1 = 0x56,
        Address2 = 0x70,
    };

    /*!
     * \brief Chip registers
     */
    enum class RegisterAddress : char {
        TEMP_TXD0 = 0xFC,
        TEMP_TXD1 = 0xFB,
        TEMP_TXD2 = 0xFA,
        PRESS_TXD0 = 0xF9,
        PRESS_TXD1 = 0xF8,
        PRESS_TXD2 = 0xF7,
        IO_SETUP = 0xF5,
        CTRL_MEAS = 0xF4,
        DEVICE_STAT = 0xF3,
        I2C_SET = 0xF2,
        IIR_CNT = 0xF1,
        RESET = 0xE0,
        CHIP_ID = 0xD1,
    };

    /*!
     * \brief Power mode
     */
    enum class PowerMode : char {
        MSK_MODE_POWER = 0x03,
        VAL_MODE_SLEEP = 0x00,
        VAL_MODE_FORCED = 0x01,
        VAL_MODE_NORMAL = 0x03,
    };

    enum class PressureControlMeasure : char {
        MSK_MODE_P = 0xE3,
        SFT_MODE_P = 2,
        VAL_MODE_HIGHSPEED_P = 0x04,
        VAL_MODE_LOWPOWER_P = 0x08,
        VAL_MODE_STANDARD_P = 0x10,
        VAL_MODE_HIGHACCURACY_P = 0x14,
        VAL_MODE_ULTRAHIGHACCURACY_P = 0x18,
    };

    enum class TemperatureControlMeasure : char {
        MSK_MODE_T = 0x1F,
        SFT_MODE_T = 5,
        VAL_MODE_HIGHSPEED_T = 0x20,
        VAL_MODE_LOWPOWER_T = 0x20,
        VAL_MODE_STANDARD_T = 0x20,
        VAL_MODE_HIGHACCURACY_T = 0x40,
        VAL_MODE_ULTRAHIGHACCURACY_T = 0x40,
    };

    enum class Status : int {
        OK = 0,
        PENDING = 1,
        NOT_INITIALIZED = -1,
    };

    O2SMPB02E(PinName i2c_sda, PinName i2c_scl, I2CAddress i2c_address = I2CAddress::Address2);

    bool init();

private:
    I2CAddress _i2c_address;
    I2C _i2c;

    int read_chip_id();

    int reset();

    /*!
     *  \brief Read register data
     *
     *  \param register_address Address of the register
     *  \param value Pointer to the value read from the register
     *  \return 0 on success, 1 on failure
     */
    int i2c_read_register(RegisterAddress register_address, char *value);

    /*!
     *  \brief Write to a register
     *
     *  \param register_address Address of the register to write to
     *  \param value Data to store in the register
     *  \return 0 on success, 1 on failure
     */
    int i2c_write_register(RegisterAddress register_address, char value);
};

} // namespace sixtron

#endif // CATIE_SIXTRON_2SMPB02E_H_
