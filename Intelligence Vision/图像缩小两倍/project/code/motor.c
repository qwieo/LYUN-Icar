#include "zf_common_headfile.h"
#define LEFTREAR_d		PWM1_MODULE3_CHA_D0//
#define LEFTREAR_b		PWM2_MODULE3_CHA_D2//
#define RIGHTREAR_d		PWM2_MODULE3_CHB_D3//
#define RIGHTREAR_b		PWM1_MODULE3_CHB_D1//PWM2_MODULE1_CHA_C8
#define LEFTFRONT_d		PWM2_MODULE0_CHB_C7//PWM2_MODULE3_CHA_D2
#define LEFTFRONT_b		PWM2_MODULE1_CHA_C8//PWM1_MODULE3_CHA_D0
#define RIGHTFRONT_d 	PWM2_MODULE0_CHA_C6//PWM1_MODULE3_CHB_D1
#define RIGHTFRONT_b	PWM2_MODULE1_CHB_C9//PWM2_MODULE3_CHB_D3
#define Q 10000
void Motor_Init(void)
{			
		pwm_init(RIGHTFRONT_d, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
		pwm_init(RIGHTFRONT_b, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
		pwm_init(LEFTFRONT_d, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
		pwm_init(LEFTFRONT_b, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
		
		pwm_init(RIGHTREAR_d, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
		pwm_init(RIGHTREAR_b, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
		pwm_init(LEFTREAR_d, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%
		pwm_init(LEFTREAR_b, 17000, 0);                                                // 初始化 PWM 通道 频率 17KHz 初始占空比 0%	
}

void motor_speed(pwm_channel_enum g,int speed)
{
	pwm_set_duty(g,speed);	
}
void front(float delta)
{
	if (delta>=0)
	{	
		motor_speed(LEFTFRONT_d,(int)(delta*Q));
		motor_speed(RIGHTFRONT_b,(int)(delta*Q));
		motor_speed(LEFTFRONT_b,0);
		motor_speed(RIGHTFRONT_d,0);
	}
	else
	{
		motor_speed(LEFTFRONT_b,-(int)(delta*Q));
		motor_speed(RIGHTFRONT_d,-(int)(delta*Q));
		motor_speed(LEFTFRONT_d,0);
		motor_speed(RIGHTFRONT_b,0);
	}
}
void gear(void)
{
	motor_speed(RIGHTREAR_d,2500);
	motor_speed(LEFTREAR_d,2500);
}

void forwheel(float speed)
{
	int i=(int) speed;
	if (speed>=0)
	{
		motor_speed(LEFTREAR_d,i);
		motor_speed(LEFTREAR_b,0);
	}
	else
	{
		motor_speed(LEFTREAR_b,i);
		motor_speed(LEFTREAR_d,0);
	}
}
	
