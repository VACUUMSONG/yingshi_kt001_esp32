//
// Created by wt on 0013.
//

#ifndef CAR_CONFIG_H
#define CAR_CONFIG_H
//最大和最小PWM
#define MAX_PWM         250
#define MIN_PWM         -250
//编码器获取数据的频率
#define MOVE_CTRL_RATE 100

// 轮子转一圈的信号数 (13 * 30 * 4)
#define WHEEL_TPR           (224)
// 轮子的直径
#define WHEEL_DIAMETER      0.064f
// 左右轮子的距离
#define WHEEL_DISTANCE      0.205f
// 前后轮子的轴距
#define WHEEL_AXIS          0.170f

#endif //CAR_CONFIG_H
