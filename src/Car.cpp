//
// Created by wt on 0017.
//

#include "Car.h"

Car::Car(Wheel backLWheel, Wheel backRWheel) : backLWheel(backLWheel), backRWheel(backRWheel) {

}

Car::~Car() {

}

void Car::init() {
    //每一个轮子初始化
    this->backLWheel.init();
    this->backRWheel.init();
    Serial.print(" Car init.\n");
}

void Car::spin() {
    //轮子不断执行
    this->backLWheel.spin();
    this->backRWheel.spin();
}

void Car::updateSpeed(float vel, float anguler) {
    //差速运算  计算每一个轮子的速度
    //左边轮子速度
    float speedL = vel - anguler * 0.5 * WHEEL_DISTANCE;
    //右边轮子速度
    float speedR = vel + anguler * 0.5 * WHEEL_DISTANCE;
    //让两个轮子转动
    backLWheel.updateTargetVel(speedL);
    backRWheel.updateTargetVel(speedR);
}

void Car::updatePid(float kp, float ki, float kd){
    backLWheel.updatePid(kp, ki, kd);
    backRWheel.updatePid(kp, ki, kd);
}


// 获取左轮速度
float Car::getLVel(){
    return backLWheel.getVel();
}
// 获取右轮速度
float Car::getRVel(){
    return backRWheel.getVel();
}

float Car::getVel() {
    //获取左右轮子的速度
    float lSpeed = backLWheel.getVel();
    float rSpeed = backRWheel.getVel();
    return (lSpeed+rSpeed)/2;
}

float Car::getAnguler() {
    float lSpeed = backLWheel.getVel();
    float rSpeed = backRWheel.getVel();
    return (rSpeed-lSpeed)/WHEEL_DISTANCE;
}

