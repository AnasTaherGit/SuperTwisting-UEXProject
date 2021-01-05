/*
 *
 * Mapping of the different gyro and accelero configurations:
 *
 * GYRO_CONFIG_[0,1,2,3] range = +- [250, 500,1000,2000] °/s
 *                       sensi =    [131,65.5,32.8,16.4] bit/(°/s)
 *
 * ACC_CONFIG_[0,1,2,3] range = +- [    2,   4,   8,  16] times the gravity (9.81m/s²)
 *                      sensi =    [16384,8192,4096,2048] bit/gravity
*/

#ifndef MPU_LIB_H
#define MPU_LIB_H

#include "Arduino.h"
#include "Wire.h"

#define MPU6050_ADDR 0x68
#define MPU6050_SMPLRT_DIV_REGISTER 0x19
#define MPU6050_CONFIG_REGISTER 0x1a
#define MPU6050_GYRO_CONFIG_REGISTER 0x1b
#define MPU6050_ACCEL_CONFIG_REGISTER 0x1c
#define MPU6050_PWR_MGMT_1_REGISTER 0x6b

#define MPU6050_GYRO_OUT_REGISTER 0x43
#define MPU6050_ACCEL_OUT_REGISTER 0x3B

#define RAD_2_DEG 57.29578 // [°/rad]
#define CALIB_OFFSET_NB_MES 1000

#define DEFAULT_GYRO_COEFF 0.9

class MPU6050
{
public:
    // INIT and BASIC FUNCTIONS
    MPU6050(TwoWire &w);
    byte begin(int gyro_config_num = 0, int acc_config_num = 0);

    byte writeData(byte reg, byte data);
    byte readData(byte reg);

    void calcOffsets(bool is_calc_gyro = true, bool is_calc_acc = true);

    // MPU CONFIG SETTER
    byte setGyroConfig(int config_num);
    byte setAccConfig(int config_num);

    void setGyroOffsets(float x, float y, float z);
    void setAccOffsets(float x, float y, float z);

    void setFilterGyroCoef(float gyro_coeff);
    void setFilterAccCoef(float acc_coeff);

    // MPU CONFIG GETTER
    float getGyroXoffset() { return gyroXoffset; };
    float getGyroYoffset() { return gyroYoffset; };
    float getGyroZoffset() { return gyroZoffset; };

    float getAccXoffset() { return accXoffset; };
    float getAccYoffset() { return accYoffset; };
    float getAccZoffset() { return accZoffset; };

    float getFilterGyroCoef() { return filterGyroCoef; };
    float getFilterAccCoef() { return 1.0 - filterGyroCoef; };

    // INLOOP GETTER
    float getAccX() { return accX; };
    float getAccY() { return accY; };
    float getAccZ() { return accZ; };

    float getGyroX() { return gyroX; };
    float getGyroY() { return gyroY; };
    float getGyroZ() { return gyroZ; };

    float getAccAngleX() { return angleAccX; };
    float getAccAngleY() { return angleAccY; };

    float getAngleX() { return angleX; };
    float getAngleY() { return angleY; };
    float getAngleZ() { return angleZ; };

    // INLOOP UPDATE
    void fetchData();
    void update();

private:
    TwoWire *wire;
    float acc_lsb_to_g;
    float gyroXoffset, gyroYoffset, gyroZoffset;
    float accXoffset, accYoffset, accZoffset;
    float accX, accY, accZ, gyroX, gyroY, gyroZ;
    float angleAccX, angleAccY;
    float angleX, angleY, angleZ;
    long preInterval;
    float filterGyroCoef; // complementary filter coefficient to balance gyro vs accelero data to get angle
};

#endif