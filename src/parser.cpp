#include "parser.h"

/**
 * parse vel command received
 **/
void parse_rvelcommnad(uint8_t* rcommand, float& vel, float& angular)
{
    uint_union vel_, angular_;
    vel_.ivalue[0] = rcommand[5];
    vel_.ivalue[1] = rcommand[4];
    
    angular_.ivalue[0] = rcommand[9];
    angular_.ivalue[1] = rcommand[8];
    vel = (float)(vel_.i16value) / 1000;
    angular = (float)(angular_.i16value) / 1000;
}

void parse_pid(uint8_t* rcommand, float& kp, float& ki, float& kd){
    uint_union kp_, ki_, kd_;
    kp_.ivalue[0] = rcommand[5];
    kp_.ivalue[1] = rcommand[4];
    ki_.ivalue[0] = rcommand[7];
    ki_.ivalue[1] = rcommand[6];
    kd_.ivalue[0] = rcommand[9];
    kd_.ivalue[1] = rcommand[8];
    kp = (float)(kp_.i16value) / 1000;
    ki = (float)(ki_.i16value) / 1000;
    kd = (float)(kd_.i16value) / 1000;
}

/**
 * set publish msg
 **/
void set_publishmsg(uint8_t* USARTzTxBuffer, send_data& com_x_send_data)
{
    // com_x_send_data.x_pos.fv = 2.68;//x坐标
	// com_x_send_data.y_pos.fv = 3.96;//y坐标
	// com_x_send_data.x_v.fv	= 0.6;//x方向速度
	// com_x_send_data.y_v.fv = 0.0;//y 方向速度
	// com_x_send_data.angular_v.fv = 2.0;//角速度 绕z轴
	// com_x_send_data.pose_angular.fv = 1.0;//yaw偏航角 
	
	USARTzTxBuffer[0] = head1;
	USARTzTxBuffer[1] = head2;
	
	USARTzTxBuffer[2] = com_x_send_data.x_pos.cv[0];
	USARTzTxBuffer[3] = com_x_send_data.x_pos.cv[1];
	USARTzTxBuffer[4] = com_x_send_data.x_pos.cv[2];
	USARTzTxBuffer[5] = com_x_send_data.x_pos.cv[3];
	
	USARTzTxBuffer[6] = com_x_send_data.y_pos.cv[0];
	USARTzTxBuffer[7] = com_x_send_data.y_pos.cv[1];
	USARTzTxBuffer[8] = com_x_send_data.y_pos.cv[2];
	USARTzTxBuffer[9] = com_x_send_data.y_pos.cv[3];
	
	USARTzTxBuffer[10] = com_x_send_data.x_v.cv[0];
	USARTzTxBuffer[11] = com_x_send_data.x_v.cv[1];
	USARTzTxBuffer[12] = com_x_send_data.x_v.cv[2];
	USARTzTxBuffer[13] = com_x_send_data.x_v.cv[3];
	
	USARTzTxBuffer[14] = com_x_send_data.y_v.cv[0];
	USARTzTxBuffer[15] = com_x_send_data.y_v.cv[1];
	USARTzTxBuffer[16] = com_x_send_data.y_v.cv[2];
	USARTzTxBuffer[17] = com_x_send_data.y_v.cv[3];
	
	USARTzTxBuffer[18] = com_x_send_data.angular_v.cv[0];
	USARTzTxBuffer[19] = com_x_send_data.angular_v.cv[1];
	USARTzTxBuffer[20] = com_x_send_data.angular_v.cv[2];
	USARTzTxBuffer[21] = com_x_send_data.angular_v.cv[3];
	
	USARTzTxBuffer[22] = com_x_send_data.pose_angular.cv[0];
	USARTzTxBuffer[23] = com_x_send_data.pose_angular.cv[1];
	USARTzTxBuffer[24] = com_x_send_data.pose_angular.cv[2];
	USARTzTxBuffer[25] = com_x_send_data.pose_angular.cv[3];
	
	USARTzTxBuffer[26] = USARTzTxBuffer[2]^USARTzTxBuffer[3]^USARTzTxBuffer[4]^USARTzTxBuffer[5]^USARTzTxBuffer[6]^
                        USARTzTxBuffer[7]^USARTzTxBuffer[8]^USARTzTxBuffer[9]^USARTzTxBuffer[10]^USARTzTxBuffer[11]^
                        USARTzTxBuffer[12]^USARTzTxBuffer[13]^USARTzTxBuffer[14]^USARTzTxBuffer[15]^USARTzTxBuffer[16]^
                        USARTzTxBuffer[17]^USARTzTxBuffer[18]^USARTzTxBuffer[19]^USARTzTxBuffer[20]^USARTzTxBuffer[21]^
                        USARTzTxBuffer[22]^USARTzTxBuffer[23]^USARTzTxBuffer[24]^USARTzTxBuffer[25];
    // smsg[0] = head1;
    // smsg[1] = head2;
    // smsg[2] = 40; // data size, to be done
    // smsg[3] = 0; // IMU_gyro
        
    // // pose_position.x 
    // smsg[22] = 
    // smsg[23] =
    // // pose_position.y
    // smsg[24] =
    // smsg[25] =
    // // pose_position.raw
    // smsg[26] =
    // smsg[27] = 
    // // linear.x
    // smsg[28] = (int16_t)((int16_t)(car_vel) >> 8) & 0xff;
    // smsg[29] = (int16_t)(car_vel) & 0xff;
    // // linear.y
    // smsg[30] = 0;
    // smsg[31] = 0;
    // // angular.z
    // smsg[32] = (int16_t)((int16_t)(car_angular) >> 8) & 0xff;
    // smsg[33] = (int16_t)(car_angular) & 0xff;
    
    // // lmotor_vel
    // smsg[34] = ();
    // smsg[35] =
    // // rmotor_vel
    // smsg[36] =
    // smsg[37] =
    // // lmotor_set
    // smsg[38] = 
    // smsg[39] =
    // // rmotor_set
    // smsg[40] =
    // smsg[41] =
};