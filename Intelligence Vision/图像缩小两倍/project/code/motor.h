#ifndef __MOTOR_H__
#define	__MOTOR_H__
#include "zf_common_headfile.h"
#define LEFTREAR_d		PWM1_MODULE3_CHA_D0//
#define LEFTREAR_b		PWM2_MODULE3_CHA_D2//
#define RIGHTREAR_d		PWM2_MODULE3_CHB_D3//
#define RIGHTREAR_b		PWM1_MODULE3_CHB_D1//PWM2_MODULE1_CHA_C8
#define LEFTFRONT_d		PWM2_MODULE0_CHB_C7//PWM2_MODULE3_CHA_D2
#define LEFTFRONT_b		PWM2_MODULE1_CHA_C8//PWM1_MODULE3_CHA_D0
#define RIGHTFRONT_d 	PWM2_MODULE0_CHA_C6//PWM1_MODULE3_CHB_D1
#define RIGHTFRONT_b	PWM2_MODULE1_CHB_C9//PWM2_MODULE3_CHB_D3

void Motor_Init(void);
void motor_speed(pwm_channel_enum g,int speed);
void front(float delta);
void gear(void);
void forwheel(float speed);
#endif