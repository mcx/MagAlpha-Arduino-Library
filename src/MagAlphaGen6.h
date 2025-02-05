/***************************************************
  Arduino library for the MPS MagAlpha magnetic angle sensor
  Supports MagAlpha 6th generation Sensors. 
  Support Part Number includes: MA600
  MagAlpha sensor detects the
  absolute angular position of a permanent magnet, typically a diametrically
  magnetized cylinder on the rotating shaft.
  ----> http://www.monolithicpower.com/Products/Position-Sensors/Products-Overview
  Written by Mathieu Kaelin for Monolithic Power Systems.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#ifndef MAGALPHAGEN6_H
#define MAGALPHAGEN6_H

#if (ARDUINO >= 100)
     #include "Arduino.h"
#else
     #include "WProgram.h"
#endif
#include "MagAlphaBase.h"

class MagAlphaGen6: public MagAlphaSPI {
public:
    MagAlphaGen6();
    uint16_t readAngleRaw(bool *error) override;
    uint16_t readAngleRaw16() override;
    uint8_t readAngleRaw8() override;
    uint8_t readRegister(uint8_t address) override;
    uint8_t writeRegister(uint8_t address, uint8_t value) override;
    void readRegisterBurst(uint8_t address, uint8_t valueArray[], uint16_t numberOfRegister) override;
    void writeRegisterBurst(uint8_t address, uint8_t valueArray[], uint16_t numberOfRegister) override;

    //Detect the sensor generation
    //uint16_t detectSensorGeneration() override;

    //Set Key Parameters
    uint16_t getZero() override;
    void setZero(uint16_t zero) override;
    uint16_t setCurrentAngleAsZero() override;
    uint16_t getBct() override;
    void setBct(uint16_t bct) override;

    //Memory management
    void restoreAllRegisters() override; 
    void storeAllRegisters() override;
    /**
     * @brief Store register block
     * @param block Register block to store. if block=0, it stores register 0 to 31 
     *        (registers containing the configuration).
     *        if block=1 it stores register 31 to 63
     *        (registers containing the correction table).
     */
    void storeRegisterBlock(uint8_t block) override;

    //Advanced features
    void clearErrorFlags() override;
    double readSpeed() override;
    int16_t readTurn() override;
    /**
     * @brief set a multiturn offset by configuring the MTOFFSET field
     *        in the configuration register.
     *         MTOFFSET is set to 0 at the system power up. 
     * @attention MTOFFSET setting can’t be stored into NVM, 
     *            so user needs to set MTOFFSET after every power up if offset is needed.
     * 
     * 
     */
    void writeTurn(int16_t turn) override;
    void readAngleAndMultiturnOrSpeedRaw(uint16_t *angle, uint16_t *multiturnOrSpeed);

    //Part Information
    uint16_t getNumberOfRegisters() override;
    void getLockedRegisters(uint8_t unlockedRegisters[]) override;
    void getPartNumber(char *partNumber) override;
    uint8_t getSiliconId() override;
    uint8_t getSiliconRevision() override;
    uint8_t getRegisterMapRevision() override;

};

class MagAlphaSSIGen6: public MagAlphaSSI {};

#endif //MAGALPHAGEN6_H
