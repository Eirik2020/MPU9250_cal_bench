/*
 * MPU9250.h
 *
 *  Created on: Nov 30, 2024
 *      Author: xoonz
 */

#ifndef SRC_MPU9250_H_
#define SRC_MPU9250_H_

#include "stm32f4xx_hal.h" // Replace with your STM32 series HAL header file

class MPU9250 {
private:
    I2C_HandleTypeDef *i2cHandle;           // Pointer to the I2C handle
    const uint8_t MPU9250_ADDR = 0x68 << 1; // MPU9250 I2C address

    const uint8_t ACCEL_XOUT_H = 0x3B;      // Accelerometer X-axis high byte register
    const uint8_t ACCEL_YOUT_H = 0x3D;      // Accelerometer Y-axis high byte register
    const uint8_t ACCEL_ZOUT_H = 0x3F;      // Accelerometer Z-axis high byte register

    const uint8_t GYRO_XOUT_H = 0x43;       // Gyroscope X-axis high byte register
    const uint8_t GYRO_YOUT_H = 0x45;       // Gyroscope X-axis high byte register
    const uint8_t GYRO_ZOUT_H = 0x47;       // Gyroscope X-axis high byte register

    const uint8_t PWR_MGMT_1 = 0x6B;        // Power management register

    const uint8_t CONFIG = 0x1A;
	const uint8_t SMPLRT_DIV = 0x19;
	const uint8_t GYRO_CONFIG = 0x1B;
	const uint8_t ACCEL_CONFIG = 0x1C;
	const uint8_t ACCEL_CONFIG2 = 0x1D;
	const uint8_t INT_PIN_CFG = 0x37;

    // Helper function to read two bytes from a register
    int16_t readRegisterPair(uint8_t regHigh);

    // Helper function to write to a register
    void writeRegister(uint8_t reg, uint8_t value);

public:
    // Constructor: Takes a pointer to the I2C handle
    MPU9250(I2C_HandleTypeDef *handle);

    // Initialization function
    void initialize();

    // Methods to read accelerometer and gyroscope data
    void readAccelerometer(int16_t &ax, int16_t &ay, int16_t &az);
    void read_raw_accelerometer(
    		uint8_t &ax_H, uint8_t &ax_L,
			uint8_t &ay_H, uint8_t &ay_L,
			uint8_t &az_H, uint8_t &az_L
			);

    void readGyroscope(int16_t &gx, int16_t &gy, int16_t &gz);
    void read_raw_gyroscope(
    		uint8_t &gx_H, uint8_t &gx_L,
			uint8_t &gy_H, uint8_t &gy_L,
			uint8_t &gz_H, uint8_t &gz_L
			);
};

#endif
