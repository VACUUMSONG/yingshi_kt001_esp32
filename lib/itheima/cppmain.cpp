//
// Created by wt on 0017.
//

#include "cppmain.h"


#include "Motor.h"
#include "Encoder.h"
#include "Wheel.h"
#include "Car.h"
#include "mylog.h"
#include <stdio.h>

//右后轮
/*********************** 创建马达 ***********************/
Motor motor(&htim8,TIM_CHANNEL_2,GPIOA,GPIO_PIN_4,GPIOA,GPIO_PIN_5,-1);
/*********************** 编码器 ***********************/
Encoder encoder(&htim3,TIM_CHANNEL_1|TIM_CHANNEL_2,1);
/*********************** Wheel轮子 ***********************/
Wheel wheel(motor,encoder);

//左后轮
/*********************** 创建马达 ***********************/
Motor motor1(&htim8,TIM_CHANNEL_1,GPIOA,GPIO_PIN_2,GPIOA,GPIO_PIN_3,1);
/*********************** 编码器 ***********************/
Encoder encoder1(&htim2,TIM_CHANNEL_1|TIM_CHANNEL_2,-1);
/*********************** Wheel轮子 ***********************/
Wheel wheel1(motor1,encoder1);

/*********************** 小车 ***********************/
Car car(wheel1,wheel);

void HeimaCarInit() {
//    log("hello init");
    /*********************** Motor初始化 ***********************/
//    motor.init();
//    motor.spin(3000);
//    motor1.init();
//    motor1.spin(3000);
    /*********************** Encode初始化 ***********************/
//    encoder.init();
//    encoder1.init();
    /*********************** 轮子初始化 ***********************/
//    wheel.init();
//    //更新速度
//    wheel.updateTargetVel(0.1);
    /*********************** 初始化小车 ***********************/
    car.init();
    //小车运行
    car.updateSpeed(0.1,0.2);
}

void HeimaCarTick() {
    /*********************** 不断更新速度 ***********************/
//    wheel.spin();
    /*********************** 转动 ***********************/
//    motor.spin(3000);
    /*********************** 获取计数数据 ***********************/
//    HAL_Delay(1000);
//    short i = encoder.read();
//    log("encode:%hd",i);
//    HAL_Delay(1000);
//    short i = encoder1.read();
//    mylog("encode:%hd",i);
    /*********************** 小车不断执行 ***********************/
    car.spin();
    mylog("vel:%d  anguler:%d",(int)(car.getVel()*100),(int)(car.getAnguler()*100));
}
