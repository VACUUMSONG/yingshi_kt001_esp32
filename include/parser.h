#ifndef _COMMANDPARSER
#define _COMMANDPARSER

#include <Arduino.h>

#define head1 0xAA
#define head2 0x55
#define receiveType_velocity 0x11
#define receiveType_pid      0x12
#define receiveType_params   0x13

#define rBUFFER_SIZE 11   // receive buffer 's length
#define sBUFFER_SIZE 27   // send buffer 's length

// uint与HEX快速获取
typedef union{
    uint8_t ivalue[2];
    int16_t i16value;
} uint_union;

//浮点数与HEX快速获取
typedef	union{
	float fv;
	uint8_t cv[4];
}float_union;

//发送数据结构
typedef	struct{
		float_union	x_pos;//x方向坐标
		float_union	y_pos;//y方向坐标
		float_union	x_v;//x方向速度
		float_union	y_v;//y方向速度
		float_union	angular_v;//角速度
		float_union	pose_angular;//角度
}send_data;

/*
 * parser command from master computer
 */
void parse_rvelcommnad(uint8_t* rcommand, float& vel, float& angular);
/*
 * parser pid from master computer
 */
void parse_pid(uint8_t* rcommand, float& kp, float& ki, float& kd);

void set_publishmsg(uint8_t* smsg, send_data& send_data);

#endif // _COMMANDPARSER