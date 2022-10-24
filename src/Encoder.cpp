//
// Created by wt on 0017.
//

#include "Encoder.h"
#include "mylog.h"

#define PCNT_LEFT_UNIT  PCNT_UNIT_0
#define PCNT_RIGHT_UNIT PCNT_UNIT_1

volatile int16_t motor_left_counter;
volatile int16_t motor_right_counter;


void Read_Left_Moto(){
    motor_left_counter++;
    mylog("right, Cur_pusle:%d", (int)(motor_left_counter));
}
void Read_Right_Moto(){
    motor_right_counter++;
    mylog("right, Cur_pusle:%d", (int)(motor_right_counter));
}

Encoder::Encoder(uint8_t MotorCountPin1, uint8_t MotorCountPin2, int direction, MotorPosition left_or_right) {
    this->direction = direction;
    this->motorCountPin1  = MotorCountPin1;
    this->motorCountPin2 = MotorCountPin2; 
    this->motor_position = left_or_right;
    pinMode(this->motorCountPin1, INPUT); //编码器A引脚
    pinMode(this->motorCountPin2, INPUT); //编码器B引脚
    this->timer = timerBegin(0, 8, true);
    
    // // 配置PCNT脉冲计数器
    // if (this->motor_position == LeftMotor){
    //     this->pcnt_config.channel = PCNT_CHANNEL_0; //计数器频道
    //     this->pcnt_config.unit = PCNT_LEFT_UNIT;
    // }else{
    //     this->pcnt_config.channel = PCNT_CHANNEL_1; //计数器频道
    //     this->pcnt_config.unit = PCNT_RIGHT_UNIT;
    // }
    // this->pcnt_config.pulse_gpio_num = this->motorCountPin1;// 脉冲脚
    // this->pcnt_config.ctrl_gpio_num = -1; // 方向脚
    // this->pcnt_config.counter_h_lim = 32767;  //最大计数值
    // this->pcnt_config.counter_l_lim = -32767; //最小计数值
    // this->pcnt_config.pos_mode = PCNT_COUNT_INC;
    // this->pcnt_config.neg_mode = PCNT_COUNT_DIS;
    // this->pcnt_config.lctrl_mode = PCNT_MODE_REVERSE;
    // this->pcnt_config.hctrl_mode = PCNT_MODE_KEEP;
    // pcnt_unit_config(&pcnt_config);
}

Encoder::~Encoder() {
    detachInterrupt(digitalPinToInterrupt(this->motorCountPin1));
}

void Encoder::init() {
    //编码器开启定时器
    if (this->motor_position == LeftMotor){
        attachInterrupt(digitalPinToInterrupt(this->motorCountPin1), Read_Left_Moto, RISING); //左轮脉冲开中断计数
        timerAttachInterrupt(this->timer, &Read_Left_Moto, true); // 绑定中断函数
        //重置计数
        motor_left_counter =  0;
        //Serial.print("Left Encoder init.\n");
        
        // pcnt_counter_pause(PCNT_LEFT_UNIT);     // 暂停
        // pcnt_counter_clear(PCNT_LEFT_UNIT);     // 清除
        // pcnt_counter_resume(PCNT_LEFT_UNIT);    // 开始
    }else if(this->motor_position == RightMotor){
        attachInterrupt(digitalPinToInterrupt(this->motorCountPin1), Read_Right_Moto, RISING); //左轮脉冲开中断计数
        timerAttachInterrupt(this->timer, &Read_Right_Moto, true); // 绑定中断函数
        //重置计数
        motor_right_counter = 0;
        //Serial.print("Left Encoder init.\n");
           
        // pcnt_counter_pause(PCNT_RIGHT_UNIT);     // 暂停
        // pcnt_counter_clear(PCNT_RIGHT_UNIT);     // 清除
        // pcnt_counter_resume(PCNT_RIGHT_UNIT);    // 开始
    }

}

short Encoder::read() {
    //关中断计数
    // detachInterrupt(digitalPinToInterrupt(this->motorCountPin1)); 
    //获取的编码器数据
    short count = 0;
    if (this->motor_position == LeftMotor){
        count = (short)motor_left_counter;
        // attachInterrupt(digitalPinToInterrupt(this->motorCountPin1), Read_Left_Moto, RISING); //左轮脉冲开中断计数
        //重置计数
        motor_left_counter =  0;

        // pcnt_get_counter_value(PCNT_LEFT_UNIT, &count); // 获取计数
        // pcnt_counter_pause(PCNT_LEFT_UNIT);     // 暂停
        // pcnt_counter_clear(PCNT_LEFT_UNIT);     // 清除
        // pcnt_counter_resume(PCNT_LEFT_UNIT);    // 开始
    }else if(this->motor_position == RightMotor){
        count = (short)motor_right_counter;
        // attachInterrupt(digitalPinToInterrupt(this->motorCountPin1), Read_Right_Moto, RISING); //左轮脉冲开中断计数
        //重置计数
        motor_right_counter = 0;

        // pcnt_get_counter_value(PCNT_RIGHT_UNIT, &count); // 获取计数
        // pcnt_counter_pause(PCNT_RIGHT_UNIT);     // 暂停
        // pcnt_counter_clear(PCNT_RIGHT_UNIT);     // 清除
        // pcnt_counter_resume(PCNT_RIGHT_UNIT);    // 开始
    }
    // mylog("right:%d, CurSpeed:%d", (int) (this->motor_position), (int)(i));

    return count*this->direction;
}
