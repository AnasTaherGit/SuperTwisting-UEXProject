#include "Wire.h" // This library allows you to communicate with I2C devices.
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
float accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
float Mean_x, Mean_y, Mean_z; // variables for gyro raw data
float Mean_x_error, Mean_y_error, Mean_z_error;
float previous_x=0;
float previous_z=0;
float LPF=0.3;
float Angle;
int Data_len;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave (GY-521 board)
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  Mean_x=0;
  Mean_y=0;
  Mean_z=0;
  Data_len=1000;
  for (int i=0;i<Data_len;i++){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
    Mean_x += Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    Mean_y += Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    Mean_z += Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  }
  Mean_x_error=((float)Mean_x/Data_len)/16384;
  Mean_y_error=((float)Mean_y/Data_len)/16384;
  Mean_z_error=((float)(Mean_z/Data_len)/16384)-1;
}
void loop() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
 //Serial.println(Mean_z_error);
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

  //Converting
  accelerometer_x =(float)accelerometer_x/16384-Mean_x_error*LPF+previous_x*(1-LPF);
  accelerometer_y =(float)accelerometer_y/16384-Mean_y_error;
  accelerometer_z =(float)accelerometer_z/16384-Mean_z_error*LPF+previous_z*(1-LPF);

  previous_x=accelerometer_x;
  previous_z=accelerometer_z;
  
 // Serial.print(accelerometer_z);Serial.print(' ');Serial.println(accelerometer_x);
  Angle=atan(accelerometer_x/accelerometer_z)*180/3.1451;
  Serial.println(Angle);
  // delay
  delay(100);
}
