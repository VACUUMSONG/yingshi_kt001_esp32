#include <Arduino.h>

#include "Bat.h"
#include "Car.h"
#include "parser.h"

float vel = 0, angular = 0;

/*==================== 电池 ==========================*/
// Battary voltage  Monitor
Bat bat(BATPIN_ADC,BATPIN_BUZZER);
/*==================== 小车 ==========================*/
// 左电机
Motor lmotor(MOTORL_PIN1, MOTORL_PIN2, MOTORL_PWM, 1);
// 左编码器
Encoder lencoder(-1, LeftMotor);
// 左轮
Wheel lwheel(lmotor, lencoder, true);

// 右电机
Motor rmotor(MOTORR_PIN1, MOTORR_PIN2, MOTORR_PWM, -1);
// 右编码器
Encoder rencoder(1, RightMotor);
// 右轮
Wheel rwheel(rmotor,rencoder, false);

Car Kt001(lwheel,rwheel);
/**====================================================**/
TaskHandle_t readCommandTask;
TaskHandle_t readBatVoltageTask;

// 和校验
uint8_t checksum(uint8_t* buf, size_t len)
{
  uint8_t sum = 0x00;
  for(int i=0;i<len;i++)
  {
    sum += *(buf + i);
  }
  return sum;
}

void readBatVoltage(void* param)
{
  bat.setBatVoltageAlarm();
}

void readCommand(void* param)
{
  // Serial.print(" start to receive command.\n");
  enum frameState
  {
    State_Head1, State_Head2, State_Size, State_Type, 
    State_Velocity, State_Pid, State_Params,
    State_CheckSum, State_Handle
  };
  uint8_t frame_type; // velocity; pid; correction; 
  frameState state = State_Head1; // init with state==Head1
  uint8_t command[rBUFFER_SIZE]; // 指令

  //State machine
  // [head1 head2 size type data checksum ]
  // [0xAA  0x55  0x2D 0x01 ....  0xXX    ]
  for(;;){
    if (Serial.available()==0){
      continue;
    }
    switch (state)
    {
      case State_Head1:             //waiting for frame header 1
          command[0] = Serial.read();
          state = (command[0] == head1 ? State_Head2 : State_Head1);
          if(state == State_Head1)
          {
              //ROS_INFO_STREAM ("recv head1 error : ->"<<(int)data[0]);
          }
          break;
      
      case State_Head2:             //waiting for frame header 2
          command[1] = Serial.read();
          state = (command[1] == head2 ? State_Size : State_Head1);
          if(state == State_Head1)
          {
              //ROS_INFO_STREAM ("recv head2 error : ->"<<(int)data[1]);
          }
          break;
          
      case State_Size:              //waiting for frame Size
          command[2] = Serial.read();
          state = State_Type;
          break;
          
      case State_Type:              //waiting for data_type
          command[3] = Serial.read();
          frame_type = command[3];
          if (frame_type == receiveType_velocity){
            state = State_Velocity;
          }else if (frame_type == receiveType_pid){
            state = State_Pid;
          }else if (frame_type == receiveType_params){
            state = State_Params;
          }else{
            state = State_Head1;
          }
          break;
      case State_Velocity:
          Serial.readBytes(command+4, 6);
          state = State_CheckSum;
          break;
      case State_Pid: //TODO
          Serial.readBytes(command+4, 6);
          state = State_CheckSum;
          break;
      case State_Params: // TODO
          Serial.readBytes(command+4, 6);
          state = State_Head1;
          break;
      
      case State_CheckSum:         //waiting for frame CheckSum
          command[10] = Serial.read();
          state = command[10] == checksum(command,10) ? State_Handle : State_Head1;
          if(state == State_Head1)
          {
              //ROS_INFO_STREAM ("check sum error! recv is  : ->"<<(int)data[frame_size -1]<<"  calc is "<<frame_sum);
          }
          break;
          
      case State_Handle:
          if (frame_type == receiveType_velocity){
            // parser to vel
            //float vel = 0, angular = 0;
            parse_rvelcommnad(command, vel, angular);
            //  update speed
            Kt001.updateSpeed(vel, angular);
          }else if (frame_type == receiveType_pid){
            float kp,ki,kd; 
            parse_pid(command, kp, ki, kd);
            Kt001.updatePid(kp, ki, kd);
            // TODO
          }else if (frame_type == receiveType_params){
            // TODO
            
          }else{
            // not should go here.
          }
          state = State_Head1;
          break;
      
      default:
          state = State_Head1;
          break;
    }
  }
}

enum frameState
{
  State_Head1, State_Head2, State_Size, State_Type, 
  State_Velocity, State_Pid, State_Params,
  State_CheckSum, State_Handle
};
uint8_t frame_type; // velocity; pid; correction; 
frameState state = State_Head1; // init with state==Head1

uint8_t command[rBUFFER_SIZE];    // 接收的指令
uint8_t publishMsg[sBUFFER_SIZE]; // 发送的指令


//Init
void setup() {
  Serial.begin(115200);
  Kt001.init();
  //create a task that will be executed in the Task1code() function, with priority 1 and executed on core 0
  xTaskCreatePinnedToCore(
                    readCommand,       /* Task function. */
                    "readCommandTask", /* name of task. */
                    10000,             /* Stack size of task */
                    NULL,              /* parameter of the task */
                    1,                 /* priority of the task */
                    &readCommandTask,  /* Task handle to keep track of created task */
                    1);                /* task on core 2*/
}


void loop() {

  bat.setBatVoltageAlarm();

  Kt001.spin(); //转动
  
  // publish msg to master
  send_data msg;
  float linear_vel = Kt001.getVel();
  float angular_vel = Kt001.getAnguler();
  float pose_x = Kt001.getPose_x();
  float pose_y = Kt001.getPose_y();
  float pose_angular = Kt001.getPose_angular();

  msg.x_v.fv = linear_vel;
  msg.y_v.fv = 0;
  msg.angular_v.fv = angular_vel;
  msg.x_pos.fv = pose_x;
  msg.y_pos.fv = pose_y;
  msg.pose_angular.fv = pose_angular;

  set_publishmsg(publishMsg, msg);
  Serial.write(publishMsg, sBUFFER_SIZE);
}