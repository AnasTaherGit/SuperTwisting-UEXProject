#include "mpu_lib.h"
#include "kalman_filter.h"
#include <Wire.h>

MPU6050 mpu(Wire);

SimpleKalmanFilter accfil_x(0, 0, 0.1);
SimpleKalmanFilter accfil_y(0, 0, 0.1);
SimpleKalmanFilter accfil_z(0, 0, 0.1);
SimpleKalmanFilter gyrfil_x(0, 0, 0.1);
SimpleKalmanFilter gyrfil_y(0, 0, 0.1);
SimpleKalmanFilter gyrfil_z(0, 0, 0.1);

float rawAccX;
float rawAccY;
float rawAccZ;
float rawGyroX;
float rawGyroY;
float rawGyroZ;

void setup()
{
    Serial.begin(9600);
    Wire.begin();
    initialize_mpu();
    initialize_filters();
}

void loop()
{
    get_imu_readings();
    Serial.print(mpu.getRawGyroX());
    Serial.print(" ");
    Serial.println(rawGyroX);
}

void initialize_filters()
{
    accfil_x.setMeasurementError(mpu.getAccErrorX());
    accfil_x.setEstimateError(mpu.getAccErrorX());

    accfil_y.setMeasurementError(mpu.getAccErrorY());
    accfil_y.setEstimateError(mpu.getAccErrorY());

    accfil_z.setMeasurementError(mpu.getAccErrorZ());
    accfil_z.setEstimateError(mpu.getAccErrorZ());

    gyrfil_x.setMeasurementError(mpu.getGyrErrorX());
    gyrfil_x.setEstimateError(mpu.getGyrErrorX());

    gyrfil_y.setMeasurementError(mpu.getGyrErrorY());
    gyrfil_y.setEstimateError(mpu.getGyrErrorY());

    gyrfil_z.setMeasurementError(mpu.getGyrErrorZ());
    gyrfil_z.setEstimateError(mpu.getGyrErrorZ());
}
void initialize_mpu()
{
    mpu.begin();
    mpu.calcAccelError(false);
    mpu.calcGyroOffsets(false);
}
void get_imu_readings()
{
    mpu.update();
    rawAccX = accfil_x.updateEstimate(mpu.getRawAccX());
    rawAccY = accfil_y.updateEstimate(mpu.getRawAccY());
    rawAccZ = accfil_z.updateEstimate(mpu.getRawAccZ());
    rawGyroX = gyrfil_x.updateEstimate(mpu.getRawGyroX());
    rawGyroY = gyrfil_y.updateEstimate(mpu.getRawGyroY());
    rawGyroZ = gyrfil_z.updateEstimate(mpu.getRawGyroZ());

    mpu.process_filtered(rawAccX, rawAccY, rawAccZ,
                         rawGyroX, rawGyroY, rawGyroZ);
}
