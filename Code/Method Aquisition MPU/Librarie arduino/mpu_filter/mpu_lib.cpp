#include "mpu_lib.h"
#include "Arduino.h"

MPU6050::MPU6050(TwoWire &w)
{
    wire = &w;
    accCoef = 0.1f;
    gyroCoef = 0.9f;
}

void MPU6050::begin()
{
    writeMPU6050(MPU6050_SMPLRT_DIV, 0x00);
    writeMPU6050(MPU6050_CONFIG, 0x00);
    writeMPU6050(MPU6050_GYRO_CONFIG, 0x08);
    writeMPU6050(MPU6050_ACCEL_CONFIG, 0x00);
    writeMPU6050(MPU6050_PWR_MGMT_1, 0x01);
    writeMPU6050(MPU6050_GYRO_CONFIG_REGISTER, 0x08);
    writeMPU6050(MPU6050_ACCEL_CONFIG_REGISTER, 0x00);
    this->update();
    this->process();
    angleGyroX = 0;
    angleGyroY = 0;
    angleX = this->getAccAngleX();
    angleY = this->getAccAngleY();
    preInterval = millis();
}

void MPU6050::writeMPU6050(byte reg, byte data)
{
    wire->beginTransmission(MPU6050_ADDR);
    wire->write(reg);
    wire->write(data);
    wire->endTransmission();
}

byte MPU6050::readMPU6050(byte reg)
{
    wire->beginTransmission(MPU6050_ADDR);
    wire->write(reg);
    wire->endTransmission(true);
    wire->requestFrom(MPU6050_ADDR, 1);
    byte data = wire->read();
    return data;
}

void MPU6050::setGyroOffsets(float x, float y, float z)
{
    gyroXoffset = x;
    gyroYoffset = y;
    gyroZoffset = z;
}

void MPU6050::calcGyroOffsets(bool console, uint16_t delayBefore, uint16_t delayAfter)
{
    float x = 0, y = 0, z = 0;
    int16_t rx, ry, rz, rx_max = -30000, ry_max = -30000, rz_max = -30000, rx_min = 30000, ry_min = 30000, rz_min = 30000;

    delay(delayBefore);
    if (console)
    {
        Serial.println();
        Serial.println("========================================");
        Serial.println("Calculating gyro offsets");
        Serial.print("DO NOT MOVE MPU6050");
    }
    for (int i = 0; i < 3000; i++)
    {
        if (console && i % 1000 == 0)
        {
            Serial.print(".");
        }
        wire->beginTransmission(MPU6050_ADDR);
        wire->write(0x43);
        wire->endTransmission(false);
        wire->requestFrom((int)MPU6050_ADDR, 6);

        rx = wire->read() << 8 | wire->read();
        ry = wire->read() << 8 | wire->read();
        rz = wire->read() << 8 | wire->read();

        if (rx > rx_max)
        {
            rx_max = rx;
        }
        if (ry > ry_max)
        {
            ry_max = ry;
        }
        if (rz > rz_max)
        {
            rz_max = rz;
        }
        if (rx < rx_min)
        {
            rx_min = rx;
        }
        if (ry < ry_min)
        {
            ry_min = ry;
        }
        if (rz < rz_min)
        {
            rz_min = rz;
        }

        x += ((float)rx) / 65.5;
        y += ((float)ry) / 65.5;
        z += ((float)rz) / 65.5;
    }
    gyroXerror = rx_max - rx_min;
    gyroYerror = ry_max - ry_min;
    gyroZerror = rz_max - rz_min;
    gyroXoffset = x / 3000;
    gyroYoffset = y / 3000;
    gyroZoffset = z / 3000;

    if (console)
    {
        Serial.println();
        Serial.println("Done!");
        Serial.print("X : ");
        Serial.println(gyroXoffset);
        Serial.print("Y : ");
        Serial.println(gyroYoffset);
        Serial.print("Z : ");
        Serial.println(gyroZoffset);
        Serial.println("Program will continue after 3 seconds");
        Serial.print("========================================");
        delay(delayAfter);
    }
}

void MPU6050::calcAccelError(bool console, uint16_t delayBefore, uint16_t delayAfter)
{
    int16_t rx, ry, rz, rx_max = -17000, ry_max = -17000, rz_max = -17000, rx_min = 17000, ry_min = 17000, rz_min = 17000;

    delay(delayBefore);
    if (console)
    {
        Serial.println();
        Serial.println("========================================");
        Serial.println("Calculating Accelerometer Offsets");
        Serial.print("DO NOT MOVE MPU6050");
    }
    for (int i = 0; i < 150; i++)
    {
        if (console && i % 50 == 0)
        {
            Serial.print(".");
        }
        wire->beginTransmission(MPU6050_ADDR);
        wire->write(0x3B);
        wire->endTransmission(false);
        wire->requestFrom((int)MPU6050_ADDR, 6);

        rx = wire->read() << 8 | wire->read();
        ry = wire->read() << 8 | wire->read();
        rz = wire->read() << 8 | wire->read();
        if (rx > rx_max)
        {
            rx_max = rx;
        }
        if (ry > ry_max)
        {
            ry_max = ry;
        }
        if (rz > rz_max)
        {
            rz_max = rz;
        }
        if (rx < rx_min)
        {
            rx_min = rx;
        }
        if (ry < ry_min)
        {
            ry_min = ry;
        }
        if (rz < rz_min)
        {
            rz_min = rz;
        }
    }
    accelXerror = rx_max - rx_min;
    accelYerror = ry_max - ry_min;
    accelZerror = rz_max - rz_min;

    if (console)
    {
        Serial.println();
        Serial.println("Done!");
        Serial.print("X : ");
        Serial.println(accelXerror);
        Serial.print("Y : ");
        Serial.println(accelYerror);
        Serial.print("Z : ");
        Serial.println(accelZerror);
        Serial.println("Program will continue after 3 seconds");
        Serial.print("========================================");
        delay(delayAfter);
    }
}

void MPU6050::update()
{
    wire->beginTransmission(MPU6050_ADDR);
    wire->write(0x3B);
    wire->endTransmission(false);
    wire->requestFrom((int)MPU6050_ADDR, 6);

    rawAccX = wire->read() << 8 | wire->read();
    rawAccY = wire->read() << 8 | wire->read();
    rawAccZ = wire->read() << 8 | wire->read();

    wire->beginTransmission(MPU6050_ADDR);
    wire->write(0x43);
    wire->endTransmission(false);
    wire->requestFrom((int)MPU6050_ADDR, 6);

    rawGyroX = wire->read() << 8 | wire->read();
    rawGyroY = wire->read() << 8 | wire->read();
    rawGyroZ = wire->read() << 8 | wire->read();
}
void MPU6050::process()
{
    accX = ((float)rawAccX) / 16384.0;
    accY = ((float)rawAccY) / 16384.0;
    accZ = ((float)rawAccZ) / 16384.0;

    angleAccX = atan2(accY, sqrt(accZ * accZ + accX * accX)) * 360 / 2.0 / PI;
    angleAccY = atan2(accX, sqrt(accZ * accZ + accY * accY)) * 360 / -2.0 / PI;

    gyroX = ((float)rawGyroX) / 65.5;
    gyroY = ((float)rawGyroY) / 65.5;
    gyroZ = ((float)rawGyroZ) / 65.5;

    gyroX -= gyroXoffset;
    gyroY -= gyroYoffset;
    gyroZ -= gyroZoffset;

    interval = (millis() - preInterval) * 0.001;

    angleGyroX += gyroX * interval;
    angleGyroY += gyroY * interval;
    angleGyroZ += gyroZ * interval;

    angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
    angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
    angleZ = angleGyroZ;

    preInterval = millis();
}

void MPU6050::process_filtered(float rAccX, float rAccY, float rAccZ, float rGyroX, float rGyroY, float rGyroZ)
{
    accX = (rAccX) / 16384.0;
    accY = (rAccY) / 16384.0;
    accZ = (rAccZ) / 16384.0;

    angleAccX = atan2(accY, sqrt(accZ * accZ + accX * accX)) * 180 / PI;
    angleAccY = atan2(accX, sqrt(accZ * accZ + accY * accY)) * 180 / PI;
    angleAccZ = atan2(accX, sqrt(accX * accX + accY * accY)) * 180 / PI;

    gyroX = (rGyroX) / 65.5;
    gyroY = (rGyroY) / 65.5;
    gyroZ = (rGyroZ) / 65.5;
    gyroX -= gyroXoffset;
    gyroY -= gyroYoffset;
    gyroZ -= gyroZoffset;

    interval = (millis() - preInterval) * 0.001;

    angleGyroX += gyroX * interval;
    angleGyroY += gyroY * interval;
    angleGyroZ += gyroZ * interval;

    angleX = (gyroCoef * (angleX + gyroX * interval)) + (accCoef * angleAccX);
    angleY = (gyroCoef * (angleY + gyroY * interval)) + (accCoef * angleAccY);
    angleZ = (gyroCoef * (angleZ + gyroZ * interval)) + (accCoef * angleAccZ);

    preInterval = millis();
}