/*
 * MPU9250.cpp
 *
 *  Created on: Nov 30, 2024
 *      Author: xoonz
 */

#include "MPU9250.h"

// Constructor
MPU9250::MPU9250(I2C_HandleTypeDef *handle) : i2cHandle(handle) {}

// Write a value to an MPU9250 register
void MPU9250::writeRegister(uint8_t reg, uint8_t value) {
    HAL_I2C_Mem_Write(i2cHandle, MPU9250_ADDR, reg, I2C_MEMADD_SIZE_8BIT, &value, 1, HAL_MAX_DELAY);
}

// Read two bytes from a register and combine them
int16_t MPU9250::readRegisterPair(uint8_t regHigh) {
    uint8_t data[2];
    HAL_I2C_Mem_Read(i2cHandle, MPU9250_ADDR, regHigh, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);
    return (int16_t)((data[0] << 8) | data[1]);
}

// Initialize the MPU9250 (e.g., wake up the sensor)
void MPU9250::initialize() {
	// Reset the device
	    writeRegister(PWR_MGMT_1, 0x80);
	    HAL_Delay(100);

	    // Wake up the device and set clock source
	    writeRegister(PWR_MGMT_1, 0x01);


}

// Read accelerometer data
void MPU9250::readAccelerometer(int16_t &ax, int16_t &ay, int16_t &az) {
    ax = readRegisterPair(ACCEL_XOUT_H);
    ay = readRegisterPair(ACCEL_XOUT_H + 2);
    az = readRegisterPair(ACCEL_XOUT_H + 4);
}

void MPU9250::read_raw_accelerometer(uint8_t &ax_H, uint8_t &ax_L, uint8_t &ay_H, uint8_t &ay_L, uint8_t &az_H, uint8_t &az_L) {
    // Buffer to store all 6 bytes of accelerometer data
    uint8_t data[6];

    // Read all accelerometer registers in one I2C transaction
    if (HAL_I2C_Mem_Read(i2cHandle, MPU9250_ADDR, ACCEL_XOUT_H, I2C_MEMADD_SIZE_8BIT, data, 6, HAL_MAX_DELAY) == HAL_OK) {
        // Assign high and low bytes for each axis
        ax_H = data[0];
        ax_L = data[1];
        ay_H = data[2];
        ay_L = data[3];
        az_H = data[4];
        az_L = data[5];
    } else {
        // Handle I2C read error (e.g., set values to zero or indicate an error state)
        ax_H = ax_L = ay_H = ay_L = az_H = az_L = 0;
        // Optionally log an error or handle it in another way
        // printf("I2C Error: Failed to read accelerometer data.\n");
    }
}

// Read gyroscope data
void MPU9250::readGyroscope(int16_t &gx, int16_t &gy, int16_t &gz) {
    gx = readRegisterPair(GYRO_XOUT_H);
    gy = readRegisterPair(GYRO_YOUT_H);
    gz = readRegisterPair(GYRO_ZOUT_H);
}

void MPU9250::read_raw_gyroscope(uint8_t &gx_H, uint8_t &gx_L, uint8_t &gy_H, uint8_t &gy_L, uint8_t &gz_H, uint8_t &gz_L){
	// Data buffer for high and low bits.
	uint8_t data[2];

	// Read accelerometer.
	HAL_I2C_Mem_Read(i2cHandle, MPU9250_ADDR, GYRO_XOUT_H, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);
	gx_H = data[0];
	gx_L = data[1];

	HAL_I2C_Mem_Read(i2cHandle, MPU9250_ADDR, GYRO_XOUT_H, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);
	gy_H = data[0];
	gy_L = data[1];

	HAL_I2C_Mem_Read(i2cHandle, MPU9250_ADDR, GYRO_XOUT_H, I2C_MEMADD_SIZE_8BIT, data, 2, HAL_MAX_DELAY);
	gz_H = data[0];
	gz_L = data[1];
}



