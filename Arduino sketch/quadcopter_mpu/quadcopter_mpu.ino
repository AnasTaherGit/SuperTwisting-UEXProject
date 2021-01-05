#include "mpu_lib.h"

MPU6050 mpu(Wire);
unsigned long timer = 0;

void setup()
{
    Wire.begin();
    Serial.begin(9600);

    // Initialize the MPU6050
    byte status = mpu.begin();
    Serial.print("MPU6050 status: ");
    Serial.println(status);
    while (status != 0)
    {
    }
    Serial.println(F("Calculating offsets, do not move MPU6050"));
    delay(1000);
    mpu.calcOffsets();
    Serial.println("Done!\n");
}

void loop()
{
    mpu.update();

    if ((millis() - timer) > 10)
    {
        Serial.print("X : ");
        Serial.print(mpu.getAngleX());
        Serial.print("\tY : ");
        Serial.print(mpu.getAngleY());
        Serial.print("\tZ : ");
        Serial.println(mpu.getAngleZ());
        timer = millis();
    }
}