#include "Wire.h" // This library allows you to communicate with I2C devices.
//MPU6050 parameters
const int MPU_ADDR = 0x68; // I2C address of the MPU-6050. If AD0 pin is set to HIGH, the I2C address will be 0x69.
int Data_len=100;
//Accelerometer
float accelerometer_x, accelerometer_y, accelerometer_z; // variables for accelerometer raw data
float Mean_x, Mean_y, Mean_z; // variables for gyro raw data
float Mean_x_error, Mean_y_error, Mean_z_error;
float previous_x=0;
float previous_z=0;
float LPF=0.3;
//Gyroscope
int gyro_y;
float Mean_gyro;
float Mean_gyro_error;
//System Control parameters
float Angle;
float Speed;

// Control System Setup
float Throttle;
// PID Angle control
float K_angle=5;
float Ki_angle=2;
float Kd_angle=3;
float angle_roll_ref=0;
float angle_roll_last;
float angle_pid_output;
//PID Speed control
float K_speed=5;
float Ki_speed=2;
float Kd_speed=3;
float speed_roll_ref;
float speed_roll_last;
float speed_pid_output=0;

//--------------------------PID DEFINITION ----------------------------------------------------

void pid_angle(){
  float error=Angle-angle_roll_ref;
  float error_last=angle_roll_last-angle_roll_ref;
  angle_pid_output=K_angle*error+Ki_angle*(error+error_last)+Kd_angle*(error-error_last);
}
void pid_speed(){
  float error=Speed-speed_roll_ref;
  float error_last=speed_roll_last-speed_roll_ref;
  angle_pid_output=K_speed*error+Ki_speed*(error+error_last)+Kd_speed*(error-error_last);
}
//----------------------------------------------------------------------------------------------

//--------------------------- Sensor Measurement FUNCTION DEFINITION -----------------------------------------------
//Measure Angle
void angle_sensor(){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 7*2, true); // request a total of 7*2=14 registers
  
 //Serial.println(Mean_z_error);
  accelerometer_x = Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  accelerometer_y = Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
  accelerometer_z = Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)

  //Converting
  accelerometer_x =(float)(accelerometer_x/16384-Mean_x_error)*LPF+previous_x*(1-LPF);
  accelerometer_y =(float)(accelerometer_y/16384-Mean_y_error);
  accelerometer_z =(float)(accelerometer_z/16384-Mean_z_error)*LPF+previous_z*(1-LPF);

  previous_x=accelerometer_x;
  previous_z=accelerometer_z;
  
 // Serial.print(accelerometer_z);Serial.print(' ');Serial.println(accelerometer_x);
 if (accelerometer_x>=0) Angle=(accelerometer_z>0)? (atan(accelerometer_x/accelerometer_z)*180/3.1451):(180+atan(accelerometer_x/accelerometer_z)*180/3.1451);
 else Angle=(accelerometer_z>0)? (360+atan(accelerometer_x/accelerometer_z)*180/3.1451):(270-atan(accelerometer_z/accelerometer_x)*180/3.1451);
}


//Measure Angular speed
void speed_sensor(){
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x45); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
  Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
  Wire.requestFrom(MPU_ADDR, 1*2, true); // request gyroscope value y axis
  
 //Serial.println(Mean_z_error);
  gyro_y = Wire.read()<<8 | Wire.read(); // reading registers

  //Converting
  Speed=(float)(gyro_y/131-Mean_gyro_error);

 // Serial.print(accelerometer_z);Serial.print(' ');Serial.println(accelerometer_x);  
}
//------------------------------------------------------------------------------------------------------

void setup() {
  Serial.begin(9600);
  Wire.begin();
  //MPU6050 Wake-UP
  Wire.beginTransmission(MPU_ADDR); // Begins a transmission to the I2C slave
  Wire.write(0x6B); // PWR_MGMT_1 register
  Wire.write(0); // set to zero (wakes up the MPU-6050)
  Wire.endTransmission(true);
  
  // Accelerometer Calibration
  Mean_x=0;
  Mean_y=0;
  Mean_z=0;
  for (int i=0;i<Data_len;i++){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x3B); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(MPU_ADDR, 3*2, true); // request a total of 7*2=14 registers
    Mean_x += Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
    Mean_y += Wire.read()<<8 | Wire.read(); // reading registers: 0x3D (ACCEL_YOUT_H) and 0x3E (ACCEL_YOUT_L)
    Mean_z += Wire.read()<<8 | Wire.read(); // reading registers: 0x3F (ACCEL_ZOUT_H) and 0x40 (ACCEL_ZOUT_L)
  }
  Mean_x_error=((float)Mean_x/Data_len)/16384;
  Mean_y_error=((float)Mean_y/Data_len)/16384;
  Mean_z_error=((float)(Mean_z/Data_len)/16384)-1;
  
  //Gyroscope Calibration
  for (int i=0;i<Data_len;i++){
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(0x45); // starting with register 0x3B (ACCEL_XOUT_H) [MPU-6000 and MPU-6050 Register Map and Descriptions Revision 4.2, p.40]
    Wire.endTransmission(false); // the parameter indicates that the Arduino will send a restart. As a result, the connection is kept active.
    Wire.requestFrom(MPU_ADDR, 1*2, true); // request a total of 7*2=14 registers
    Mean_gyro += Wire.read()<<8 | Wire.read(); // reading registers: 0x3B (ACCEL_XOUT_H) and 0x3C (ACCEL_XOUT_L)
  }
  Mean_gyro_error=((float)Mean_gyro/Data_len)/131.0;
  

  //Angle Measure
  angle_sensor();
  angle_roll_last=Angle;
  //Speed Measure
  speed_sensor();
  speed_roll_last=Speed;
}
void loop() {
  angle_sensor();
  // delay
  //delay(100);
  pid_angle();
  speed_roll_ref=angle_pid_output;
  speed_sensor();
  pid_speed(); 
  Serial.print("Angle :");Serial.print(Angle);Serial.print(" Speed :");Serial.println(Speed);
}
