#include "Car.h"

Car::Car(Wheel backLWheel, Wheel backRWheel) : backLWheel(backLWheel), backRWheel(backRWheel) {
    this->pose_x = 0;
    this->pose_y = 0;
    this->pose_angular = 0;
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
    float left_wheel_delta = this->backLWheel.spin();   // 左轮移动的增量
    float right_wheel_delta  = this->backRWheel.spin(); // 右轮移动的增量
    
    // 计算位姿
    // 底盘坐标系的X轴和Y轴变化
    float car_xy_delta = (left_wheel_delta + right_wheel_delta) / 2;
    float car_angular_delta = (right_wheel_delta - left_wheel_delta) / WHEEL_DISTANCE;
    float delta_x = (cos(car_angular_delta) * car_xy_delta);
    float delta_y = -sin(car_angular_delta) * car_xy_delta;

    // 计算里程计坐标系的变化
    this->pose_x += (cos(this->pose_angular)* delta_x - sin(this->pose_angular)*delta_y);
    this->pose_y += (sin(this->pose_angular)* delta_x + cos(this->pose_angular)*delta_y);
    this->pose_angular += car_angular_delta;

    if (this->pose_angular < -(2*M_PI)){
        this->pose_angular += (2 * M_PI); 
    }else if(this->pose_angular > 2*M_PI){
        this->pose_angular -= 2 * M_PI;
    }
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

// 获取线速度
float Car::getVel() {
    float lSpeed = backLWheel.getVel();
    float rSpeed = backRWheel.getVel();
    return (lSpeed+rSpeed)/2;
}

// 获取绕z轴角速度
float Car::getAnguler() {
    float lSpeed = backLWheel.getVel();
    float rSpeed = backRWheel.getVel();
    return (rSpeed-lSpeed)/WHEEL_DISTANCE;
}

// 获取位姿x的坐标
float Car::getPose_x(){
    return this->pose_x;
}

// 获取位姿y的坐标
float Car::getPose_y(){
    return this->pose_y;
}

// 获取位姿 转向角
float Car::getPose_angular(){
    return this->pose_angular;
}


