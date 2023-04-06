#ifndef BAT_H
#define BAT_H

#include <Arduino.h>

//需要拨码开关到A0
#define BAT_FILTER_LIMIT 10

#define BATPIN_ADC 0
#define BATPIN_BUZZER 8

//电压预警标志位
//蓝色电池电压适配
#define BAT_LOWFLAG  (1.36)
//无电池预警标志
#define BAT_NONEFLAG  (0.50)

// Battery Monitor
// 电压 检测
class Bat{
private:
    uint8_t batMonitorPin_Adc; //电压检测 (ADC)
    uint8_t batMonitorPin_Buzzer;

public:
    Bat(uint8_t batMonitorPin_Adc,uint8_t batMonitorPin_Buzzzer);

    ~Bat();

    //初始化
    void init();
    //不断执行
    void spin();

    u_int8_t fliter(u_int8_t analogRead);

    // 获取电池电压
    // 数字量电压范围 0-1023
    u_int8_t getBatVoltage();

    void setBatAlarmBuzzer();
    void setMotorStop();
    void setBatVoltageAlarm();
};
#endif