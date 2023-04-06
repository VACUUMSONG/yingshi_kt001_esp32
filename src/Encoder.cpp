//
// Created by wt on 0017.
//

#include "Encoder.h"
#include "mylog.h"

static volatile int16_t motor_left_counter;
static volatile int16_t motor_right_counter;

void Read_Left_Moto(){
    if (digitalRead(MOTORL_COUNTPIN1) == digitalRead(MOTORL_COUNTPIN2)) {
        motor_left_counter++;
    }else{
        motor_left_counter--;
    }

}
void Read_Right_Moto(){
    if (digitalRead(MOTORR_COUNTPIN1) == digitalRead(MOTORR_COUNTPIN2)) {
        motor_right_counter++;
    }else{
        motor_right_counter--;
    }
}

Encoder::Encoder(int direction, MotorPosition left_or_right) {
    this->direction = direction;
    this->motor_position = left_or_right;
    if(motor_position == LeftMotor){
        this->motorCountPin1  = MOTORL_COUNTPIN1;
        this->motorCountPin2 = MOTORL_COUNTPIN2; 
    }else{
        this->motorCountPin1  = MOTORR_COUNTPIN1;
        this->motorCountPin2 = MOTORR_COUNTPIN2;
    }
    pinMode(this->motorCountPin1, INPUT); //编码器A引脚
    pinMode(this->motorCountPin2, INPUT); //编码器B引脚
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
    }else if(this->motor_position == RightMotor){
        attachInterrupt(digitalPinToInterrupt(this->motorCountPin1), Read_Right_Moto, RISING); //左轮脉冲开中断计数
        //timerAttachInterrupt(this->timer, &Read_Right_Moto, true); // 绑定中断函数
        //重置计数
        motor_right_counter = 0;
    }

}

short Encoder::read() {
    //获取的编码器数据
    short count = 0;
    if (this->motor_position == LeftMotor){
        count = (short)motor_left_counter;
        // mylog("[left] counter:%d \n", (int) (count));
        //重置计数
        motor_left_counter =  0;

    }else if(this->motor_position == RightMotor){
        count = (short)motor_right_counter;
        // mylog("[right] counter:%d \n", (int) (count));
        //重置计数
        motor_right_counter = 0;
    }
    // mylog("right:%d, CurSpeed:%d", (int) (this->motor_position), (int)(i));

    return count*this->direction;
}
