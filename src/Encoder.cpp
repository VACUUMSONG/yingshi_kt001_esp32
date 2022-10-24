//
// Created by wt on 0017.
//

#include "Encoder.h"
#include "mylog.h"

#define PCNT_LEFT_UNIT  PCNT_UNIT_0
#define PCNT_RIGHT_UNIT PCNT_UNIT_1

static volatile int16_t motor_left_counter;
static volatile int16_t motor_right_counter;


void Read_Left_Moto(){
    motor_left_counter++;
}
void Read_Right_Moto(){
    motor_right_counter++;
}

Encoder::Encoder(uint8_t MotorCountPin1, uint8_t MotorCountPin2, int direction, MotorPosition left_or_right) {
    this->direction = direction;
    this->motorCountPin1  = MotorCountPin1;
    this->motorCountPin2 = MotorCountPin2; 
    this->motor_position = left_or_right;
    pinMode(this->motorCountPin1, INPUT); //编码器A引脚
    pinMode(this->motorCountPin2, INPUT); //编码器B引脚
    //this->timer = timerBegin(0, 8, true);
}

Encoder::~Encoder() {
    detachInterrupt(digitalPinToInterrupt(this->motorCountPin1));
}

void Encoder::init() {
    //编码器开启定时器
    if (this->motor_position == LeftMotor){
        attachInterrupt(digitalPinToInterrupt(this->motorCountPin1), Read_Left_Moto, RISING); //左轮脉冲开中断计数
        //timerAttachInterrupt(this->timer, &Read_Left_Moto, true); // 绑定中断函数
        //重置计数
        motor_left_counter =  0;
        //Serial.print("Left Encoder init.\n");
    }else if(this->motor_position == RightMotor){
        attachInterrupt(digitalPinToInterrupt(this->motorCountPin1), Read_Right_Moto, RISING); //左轮脉冲开中断计数
        //timerAttachInterrupt(this->timer, &Read_Right_Moto, true); // 绑定中断函数
        //重置计数
        motor_right_counter = 0;
        //Serial.print("Left Encoder init.\n");
    }

}

short Encoder::read() {
    //获取的编码器数据
    short count = 0;
    if (this->motor_position == LeftMotor){
        count = (short)motor_left_counter;
        //重置计数
        motor_left_counter =  0;

    }else if(this->motor_position == RightMotor){
        count = (short)motor_right_counter;
        //重置计数
        motor_right_counter = 0;
    }
    // mylog("right:%d, CurSpeed:%d", (int) (this->motor_position), (int)(i));

    return count*this->direction;
}
