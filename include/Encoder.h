//
// Created by wt on 0017.
//

#ifndef SMARTCAR_ENCODER_H
#define SMARTCAR_ENCODER_H
#include <Arduino.h>
// #include "driver/pcnt.h"

typedef enum{
    LeftMotor,RightMotor
    } MotorPosition;

//编码器
//属性: 定时器  channel
//行为: 初始化  获取当前编码数据
class Encoder {
private:
    //编码器
    // 编码器信号引脚
    uint8_t motorCountPin1;
    uint8_t motorCountPin2;

    // 脉冲计数器 配置
    // pcnt_config_t pcnt_config;

    //方向调节系数
    int direction=1;

    // 左轮右轮
    MotorPosition motor_position;

public:
    Encoder(uint8_t MotorCountPin1, uint8_t MotorCountPin2, int direction, MotorPosition left_or_right);

    ~Encoder();

    //初始化
    void init();
    //读取编码器数据 /13/30/4
    short read();
};


#endif //SMARTCAR_ENCODER_H
