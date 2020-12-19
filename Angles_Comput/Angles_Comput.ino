#include <Wire.h>                          //Include the Wire.h library so we can communicate with the gyro.
#include <EEPROM.h>                        //Include the EEPROM.h library so we can store information onto the EEPROM

double gyro_pitch, gyro_roll, gyro_yaw,Acc_rawX,Acc_rawY,Acc_rawZ;
double gyro_axis[4], gyro_axis_cal[4],acc_axis_cal[3];
float Acceleration_angle[2];
int cal_int, start, gyro_address;
float rad_to_deg = 180/3.141592654;
void setup() {
  Serial.begin(9600);
  Wire.begin();
  gyro_address = 0x68;
  set_gyro_registers(); 
  // put your setup code here, to run once:
  for (cal_int = 0; cal_int < 2000 ; cal_int ++){              //Take 2000 readings for calibration.
    if(cal_int % 15 == 0)digitalWrite(12, !digitalRead(12));   //Change the led status to indicate calibration.
    gyro_signalen();                                           //Read the gyro output.
    gyro_axis_cal[1] += gyro_axis[1];                          //Ad roll value to gyro_roll_cal.
    gyro_axis_cal[2] += gyro_axis[2];                          //Ad pitch value to gyro_pitch_cal.
    gyro_axis_cal[3] += gyro_axis[3];                          //Ad yaw value to gyro_yaw_cal.
    acc_axis_cal[1] += Acc_rawX;                          //Ad accX value to accX_cal.
    acc_axis_cal[2] += Acc_rawY;
    //We don't want the esc's to be beeping annoyingly. So let's give them a 1000us puls while calibrating the gyro.
    PORTD |= B11110000;                                        //Set digital poort 4, 5, 6 and 7 high.
    delayMicroseconds(1000);                                   //Wait 1000us.
    PORTD &= B00001111;                                        //Set digital poort 4, 5, 6 and 7 low.
    delay(3);                                                  //Wait 3 milliseconds before the next loop.
  }
  //Now that we have 2000 measures, we need to devide by 2000 to get the average gyro offset.
  gyro_axis_cal[1] /= 2000;                                    //Divide the roll total by 2000.
  gyro_axis_cal[2] /= 2000;                                    //Divide the pitch total by 2000.
  gyro_axis_cal[3] /= 2000;                                     //Divide the yaw total by 2000.
  acc_axis_cal[1]/=2000;
  acc_axis_cal[2]/=2000;
}

void loop() {
  // put your main code here, to run repeatedly:
  Acceleration_angle[0] = atan(((float)Acc_rawY/16384.0)/sqrt(pow(((float)Acc_rawX/16384.0),2) + pow(((float)Acc_rawZ/16384.0),2)))*rad_to_deg;
  Acceleration_angle[1] = atan(-1*((float)Acc_rawX/16384.0)/sqrt(pow(((float)Acc_rawY/16384.0),2) + pow(((float)Acc_rawZ/16384.0),2)))*rad_to_deg;
  Serial.print("AangleX:   ");Serial.print(Acceleration_angle[0]);Serial.print("       AangleY:   ");Serial.println(Acceleration_angle[1]);
}


void set_gyro_registers(){
  //Setup the MPU-6050
    Wire.beginTransmission(gyro_address);                        //Start communication with the address found during search.
    Wire.write(0x6B);                                            //We want to write to the PWR_MGMT_1 register (6B hex)
    Wire.write(0x00);                                            //Set the register bits as 00000000 to activate the gyro
    Wire.endTransmission();                                      //End the transmission with the gyro.
    
    Wire.beginTransmission(gyro_address);                        //Start communication with the address found during search.
    Wire.write(0x1B);                                            //We want to write to the GYRO_CONFIG register (1B hex)
    Wire.write(0x08);                                            //Set the register bits as 00001000 (500dps full scale)
    Wire.endTransmission();                                      //End the transmission with the gyro
    
    //Let's perform a random register check to see if the values are written correct
    Wire.beginTransmission(gyro_address);                        //Start communication with the address found during search
    Wire.write(0x1B);                                            //Start reading @ register 0x1B
    Wire.endTransmission();                                      //End the transmission
    Wire.requestFrom(gyro_address, 1);                           //Request 1 bytes from the gyro
    while(Wire.available() < 1);                                 //Wait until the 6 bytes are received
    if(Wire.read() != 0x08){                                     //Check if the value is 0x08
      digitalWrite(12,HIGH);                                     //Turn on the warning led
      while(1)delay(10);                                         //Stay in this loop for ever
    }
    
    Wire.beginTransmission(gyro_address);                        //Start communication with the address found during search
    Wire.write(0x1A);                                            //We want to write to the GYRO_CONFIG register (1B hex)
    Wire.write(0x03);                                            //Set the register bits as 00001000 (500dps full scale)
    Wire.endTransmission();                                      //End the transmission with the gyro    
}

void gyro_signalen(){
   //Read the MPU-6050
    Wire.beginTransmission(gyro_address);                        //Start communication with the gyro
    Wire.write(0x43);                                            //Start reading @ register 43h and auto increment with every read
    Wire.endTransmission();                                      //End the transmission
    Wire.requestFrom(gyro_address,6);                            //Request 6 bytes from the gyro
    while(Wire.available() < 6);                                 //Wait until the 6 bytes are received
    gyro_axis[1] = Wire.read()<<8|Wire.read();                   //Read high and low part of the angular data
    gyro_axis[2] = Wire.read()<<8|Wire.read();                   //Read high and low part of the angular data
    gyro_axis[3] = Wire.read()<<8|Wire.read();                   //Read high and low part of the angular data
    Wire.beginTransmission(0x68);
    Wire.write(0x3B); //Ask for the 0x3B register- correspond to AcX
    Wire.endTransmission(false);
    Wire.requestFrom(0x68,6,true); 
  
    Acc_rawX=Wire.read()<<8|Wire.read(); //each value needs two registres
    Acc_rawY=Wire.read()<<8|Wire.read();
    Acc_rawZ=Wire.read()<<8|Wire.read();
    if(cal_int == 2000){
      gyro_axis[1] -= gyro_axis_cal[1];// 375.09*-1;                           //Only compensate after the calibration
      gyro_axis[2] -= gyro_axis_cal[2];// 281.60;                           //Only compensate after the calibration
      gyro_axis[3] -= gyro_axis_cal[3];//19.75;                            //Only compensate after the calibration
      Acc_rawX -= acc_axis_cal[1];//117.47;
      Acc_rawY -= acc_axis_cal[2];//485.83*-1;
  }
  
}
