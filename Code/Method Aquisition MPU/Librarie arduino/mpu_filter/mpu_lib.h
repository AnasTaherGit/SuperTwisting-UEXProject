#ifndef mpu_lib_h
#define mpu_lib_h

#include "Arduino.h"
#include "Wire.h"

#define MPU6050_ADDR 0x68
#define MPU6050_SMPLRT_DIV 0x19
#define MPU6050_CONFIG 0x1a
#define MPU6050_GYRO_CONFIG 0x1b
#define MPU6050_ACCEL_CONFIG 0x1c
#define MPU6050_WHO_AM_I 0x75
#define MPU6050_PWR_MGMT_1 0x6b
#define MPU6050_GYRO_CONFIG_REGISTER 0x1b
#define MPU6050_ACCEL_CONFIG_REGISTER 0x1c

class MPU6050
{
public:
    MPU6050(TwoWire &w);
    MPU6050(TwoWire &w, float aC, float gC);

    void begin();

    void setGyroOffsets(float x, float y, float z);

    void writeMPU6050(byte reg, byte data);
    byte readMPU6050(byte reg);

    int16_t getRawAccX() { return rawAccX; };
    int16_t getRawAccY() { return rawAccY; };
    int16_t getRawAccZ() { return rawAccZ; };

    int16_t getRawGyroX() { return rawGyroX; };
    int16_t getRawGyroY() { return rawGyroY; };
    int16_t getRawGyroZ() { return rawGyroZ; };

    int16_t getAccErrorX() { return accelXerror; };
    int16_t getAccErrorY() { return accelYerror; };
    int16_t getAccErrorZ() { return accelZerror; };

    int16_t getGyrErrorX() { return gyroXerror; };
    int16_t getGyrErrorY() { return gyroYerror; };
    int16_t getGyrErrorZ() { return gyroZerror; };

    float getAccX() { return accX; };
    float getAccY() { return accY; };
    float getAccZ() { return accZ; };

    float getGyroX() { return gyroX; };
    float getGyroY() { return gyroY; };
    float getGyroZ() { return gyroZ; };

    void calcGyroOffsets(bool console = false, uint16_t delayBefore = 1000, uint16_t delayAfter = 3000);
    void calcAccelError(bool console = false, uint16_t delayBefore = 1000, uint16_t delayAfter = 3000);

    float getGyroXoffset() { return gyroXoffset; };
    float getGyroYoffset() { return gyroYoffset; };
    float getGyroZoffset() { return gyroZoffset; };

    void update();
    void process();
    void process_filtered(float rAccX, float rAccY, float rAccZ, float rGyroX, float rGyroY, float rGyroZ);

    float getAccAngleX()
    {
        return angleAccX;
    };
    float getAccAngleY() { return angleAccY; };

    float getGyroAngleX() { return angleGyroX; };
    float getGyroAngleY() { return angleGyroY; };
    float getGyroAngleZ() { return angleGyroZ; };

    float getAngleX() { return angleX; };
    float getAngleY() { return angleY; };
    float getAngleZ() { return angleZ; };

private:
    TwoWire *wire;

    int16_t rawAccX, rawAccY, rawAccZ,
        rawGyroX, rawGyroY, rawGyroZ,
        accelXerror, accelYerror, accelZerror,
        gyroXerror, gyroYerror, gyroZerror;

    float gyroXoffset, gyroYoffset, gyroZoffset;

    float accX, accY, accZ, gyroX, gyroY, gyroZ;

    float angleGyroX, angleGyroY, angleGyroZ,
        angleAccX, angleAccY, angleAccZ;

    float angleX, angleY, angleZ;

    float interval;
    long preInterval;

    float accCoef, gyroCoef;
};

#endif