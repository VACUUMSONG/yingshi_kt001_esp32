//
// Created by wt on 0017.
//

#include "Wheel.h"

Wheel::Wheel(Motor motor, Encoder encoder, bool isleft) : motor(motor), encoder(encoder), pid(100, 0, 100) {
    this->is_left_wheel = isleft;
}

Wheel::~Wheel() {

}

void Wheel::updateTargetVel(float targetSpeed) {
    //新的速度
    if (this->targetSpeed != targetSpeed) {
        //更新目标速度
        this->targetSpeed = targetSpeed;
        //重置pid
        pid.reset();
    }
}

void Wheel::init() {
    //马达初始化
    this->motor.init();
    //编码器初始化
    this->encoder.init();
    //时间初始化
    startTime = millis();
    //Serial.print("wheel init.\n");
}

void Wheel::spin() {
    //当前速度 m/s  0-1000ms  数据->圈->速度  0-10ms 数据*100->圈->速度
    if (millis() - startTime < ((unsigned long) 1000) / MOVE_CTRL_RATE) {
        return;
    }
    //时间重置
    startTime = millis();
    //读取信号数据  2 2 13 30
    short i = encoder.read();
    //速度
    curSpeed = ((float) i) / WHEEL_TPR * WHEEL_DIAMETER * M_PI * MOVE_CTRL_RATE;
    // mylog("curSpeed:%d", (int) (curSpeed * 100));
    //目标速度
    //调节速度 PID 通过PID工具 根据当前速度和目标速度  获取马达转动的pwm
    float pwm = pid.compute(this->targetSpeed, curSpeed);
    if (this->is_left_wheel){
        mylog("left:  ExpSpeed:%d, CurSpeed:%d, pwm:%d", (int)(this->targetSpeed * 100), (int)(curSpeed*100), (int)(pwm));
    }else{
        mylog("right: ExpSpeed:%d, CurSpeed:%d, pwm:%d", (int)(this->targetSpeed * 100), (int)(curSpeed*100), (int)(pwm));
    }

    this->motor.spin((int) pwm);
    //this->motor.spin(pwm);
}

float Wheel::getVel() {
    return this->curSpeed;
}
