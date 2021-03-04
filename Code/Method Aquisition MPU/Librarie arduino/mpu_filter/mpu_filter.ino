#include "mpu_lib.h"
#include "kalman_filter.h"
#include <Wire.h>
#include <Arduino.h>

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

float Angle_value, Angle_value_last;
float Speed_value, Speed_value_last;

float Angle_ref = 0;
float Speed_ref = 0;

float Kp_angle = 5, Ki_angle = 3, Kd_angle = 1;
float Kp_speed = 5, Ki_speed = 3, Kd_speed = 1;

int Throttle = 1500;
int input_1;
int input_2;

int timer_channel_1, timer_channel_2, loop_timer, esc_loop_timer;

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
    Angle_value = mpu.getAngleY();
    Speed_value = mpu.getGyroY();
    Speed_ref = pid_compute_angle();
    input_1 = Throttle + (int)pid_compute_speed();
    input_2 = Throttle - (int)pid_compute_speed();
    PWM();

    //Debug information
    Serial.print(input_1);
    Serial.print(" ");
    Serial.println(Speed_ref);
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

float pid_compute_angle()
{
    float error = Angle_value - Angle_ref;
    float error_last = Angle_value_last - Angle_ref;
    Angle_value_last = Angle_value;
    return Kp_angle * error + Ki_angle * (error + error_last) + Kd_angle * (error - error_last);
}
float pid_compute_speed()
{
    float error = Speed_value - Speed_ref;
    float error_last = Speed_value_last - Speed_ref;
    Speed_value_last = Speed_value;
    return Kp_speed * error + Ki_speed * (error + error_last) + Kd_speed * (error - error_last);
}

void PWM()
{
    if (input_1 < 1200)
        input_1 = 1200;
    if (input_2 < 1200)
        input_2 = 1200;

    if (input_1 > 2000)
        input_1 = 2000;
    if (input_2 > 2000)
        input_2 = 2000;

    while (micros() - loop_timer < 4000)
    {
    }
    loop_timer = micros();

    PORTD |= B11110000;
    timer_channel_1 = input_1 + loop_timer;
    timer_channel_2 = input_2 + loop_timer;

    while (PORTD >= 63)
    {
        esc_loop_timer = micros();
        if (timer_channel_1 <= esc_loop_timer)
            PORTD &= B10111111;
        if (timer_channel_2 <= esc_loop_timer)
            PORTD &= B01111111;
    }
}