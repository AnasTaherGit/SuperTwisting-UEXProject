///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//PID gain and limit settings
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
float pid_p_gain_roll = 1.4;  //Gain setting for the roll P-controller (1.3)
float pid_i_gain_roll = 0.05; //Gain setting for the roll I-controller (0.05)
float pid_d_gain_roll = 15;   //Gain setting for the roll D-controller (15)
int pid_max_roll = 400;       //Maximum output of the PID-controller (+/-)

float pid_p_gain_pitch = pid_p_gain_roll; //Gain setting for the pitch P-controller.
float pid_i_gain_pitch = pid_i_gain_roll; //Gain setting for the pitch I-controller.
float pid_d_gain_pitch = pid_d_gain_roll; //Gain setting for the pitch D-controller.
int pid_max_pitch = pid_max_roll;         //Maximum output of the PID-controller (+/-)

float pid_p_gain_yaw = 4.0;  //Gain setting for the pitch P-controller. //4.0
float pid_i_gain_yaw = 0.02; //Gain setting for the pitch I-controller. //0.02
float pid_d_gain_yaw = 0.0;  //Gain setting for the pitch D-controller.
int pid_max_yaw = 400;       //Maximum output of the PID-controller (+/-)

float pid_p_gain_roll_angle = 0.5;
float pid_i_gain_roll_angle = 0.0;
float pid_d_gain_roll_angle = 15;
int pid_max_roll_angle = 100;

float pid_output_roll_angle, pid_output_pitch_angle;
float pid_error_temp_angle, pid_i_mem_roll_angle, pid_last_roll_angle_d_error, pid_i_mem_pitch_angle, pid_last_pitch_angle_d_error;

float pid_p_gain_pitch_angle = pid_p_gain_roll_angle;
float pid_i_gain_pitch_angle = pid_i_gain_roll_angle;
float pid_d_gain_pitch_angle = pid_d_gain_roll_angle;
int pid_max_pitch_angle = pid_max_roll_angle;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//Declaring global variables
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
byte last_channel_1, last_channel_2, last_channel_3, last_channel_4;
byte eeprom_data[36];
byte highByte, lowByte;
int receiver_input_channel_1, receiver_input_channel_2, receiver_input_channel_3, receiver_input_channel_4;
int counter_channel_1, counter_channel_2, counter_channel_3, counter_channel_4, loop_counter;
int esc_1, esc_2, esc_3, esc_4;
int throttle, battery_voltage;
int cal_int, start, gyro_address;
int receiver_input[5];
unsigned long timer_channel_1, timer_channel_2, timer_channel_3, timer_channel_4, esc_timer, esc_loop_timer;
unsigned long timer_1, timer_2, timer_3, timer_4, current_time;
unsigned long loop_timer;
double gyro_pitch, gyro_roll, gyro_yaw, Acc_rawX, Acc_rawY, Acc_rawZ;
double gyro_axis[4], gyro_axis_cal[4], acc_axis_cal[3];
float pid_error_temp;
float pid_i_mem_roll, pid_roll_setpoint, gyro_roll_input, pid_output_roll, pid_last_roll_d_error;
float pid_i_mem_pitch, pid_pitch_setpoint, gyro_pitch_input, pid_output_pitch, pid_last_pitch_d_error;
float pid_i_mem_yaw, pid_yaw_setpoint, gyro_yaw_input, pid_output_yaw, pid_last_yaw_d_error;
float Acceleration_angle[2];
float Total_angle[2];
float elapsedTime, time1, timePrev;
float desired_angle_X, desired_angle_Y;
float rad_to_deg = 180 / 3.141592654;