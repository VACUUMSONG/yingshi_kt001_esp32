#include "Bat.h"
#include "Motor.h"

float_t batDigValue;
float_t batVoltage;

Bat::Bat(uint8_t batPin_Adc,uint8_t batPin_Buzzer){

    this->batMonitorPin_Adc    = batPin_Adc;
    this->batMonitorPin_Buzzer = batPin_Buzzer;
    
    //定义引脚
    pinMode(this->batMonitorPin_Adc, INPUT);  //驱动芯片控制引脚
    pinMode(this->batMonitorPin_Buzzer, OUTPUT);   //驱动芯片控制引脚，PWM调速
}

Bat::~Bat(){

}

void Bat::init() {
    // 电池检测相关引脚初始化
    // Serial.print(" BatMonitor Init....\n");
    //驱动芯片控制引脚全部拉高
    // ESP32板子（P8管脚 与下载有关 内部弱上拉）
    // 需要低电平驱动
    digitalWrite(this->batMonitorPin_Buzzer, LOW);
}

void Bat::spin() {
}

void Bat::setBatAlarmBuzzer(){
    // ESP32板子（P8管脚 与下载有关 内部弱上拉）
    // 盖板有修改  需要低电平驱动
    digitalWrite(this->batMonitorPin_Buzzer,LOW);
    delay(1000);
    digitalWrite(this->batMonitorPin_Buzzer,HIGH);
    delay(1000);
}

u_int8_t Bat::getBatVoltage() {
    

    batDigValue = analogRead(this->batMonitorPin_Adc)/4;
    batVoltage = batDigValue*(5/1024.0);

    // Serial.print("Bat Voltage:");
    // Serial.print(batVoltage);
    // Serial.print("\n");
    return batVoltage;
}

void Bat::setMotorStop(){

    // MotorLeft Stop
    pinMode(MOTORL_PIN1,OUTPUT);
    digitalWrite(MOTORL_PIN1, LOW);
    pinMode(MOTORL_PIN2,OUTPUT);
    digitalWrite(MOTORL_PIN2, LOW);

    // MotorLeft Stop
    pinMode(MOTORR_PIN1,OUTPUT);
    digitalWrite(MOTORR_PIN1, LOW);
    pinMode(MOTORR_PIN2,OUTPUT);
    digitalWrite(MOTORR_PIN2, LOW);
}
 
 // 低电压预警
void Bat::setBatVoltageAlarm(){

    batDigValue = getBatVoltage();

    if (batVoltage < BAT_LOWFLAG && batVoltage > BAT_NONEFLAG){
        setMotorStop();
        setBatAlarmBuzzer();
    }

    // 正常电压
    if (batVoltage > BAT_LOWFLAG ){
        digitalWrite(this->batMonitorPin_Buzzer,HIGH);
    }
    // 无电池
    if (batVoltage < BAT_NONEFLAG){
        setMotorStop();
        digitalWrite(this->batMonitorPin_Buzzer,HIGH);
    }
}
