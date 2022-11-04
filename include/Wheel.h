//
// Created by wt on 0017.
//

#ifndef SMARTCAR_WHEEL_H
#define SMARTCAR_WHEEL_H

#include "Motor.h"
#include "Encoder.h"
#include "PID.h"
#include <stdio.h>
#include "mylog.h"
//轮子
//属性:马达 编码器
//行为: 设置速度
class Wheel {
private:
    //马达
    Motor motor;
    //编码器
    Encoder encoder;
    //PID调节对象
    PID pid;
    //目标速度
    float targetSpeed = 0;
    //开始计时时间
    unsigned long startTime = 0;
    //当前速度
    float curSpeed;
    // 是否左轮
    bool is_left_wheel;

public:
    Wheel(Motor motor,Encoder encoder, bool isleft);

    ~Wheel();
    //初始化
    void init();

    //不断执行 轮子转动 轮子不断速度逼近目标速度 40, 并返回移动距离
    float spin();

    //设置目标速度 速度单位: m/s
    void updateTargetVel(float speed);

    void updatePid(float kp, float ki, float kd);

    //获取当前速度
    float getVel();
};


#endif //SMARTCAR_WHEEL_H
