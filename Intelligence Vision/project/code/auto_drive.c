#include "zf_common_headfile.h"
#include "main.h"
#include "IPM.h"
#include "Image_process.h"
#include "motor.h"
#include "ppersuit.h"
#include "encoder.h"
#include "pid.h"
#include "vofa.h"
#define SUM 100 //base=38 p=1.2*1.25*1.2
extern pid_param_t lf;
extern pid_param_t rf;
extern pid_param_t lr;
extern pid_param_t rr;
extern int16 leftfront,rightfront,leftrear,rightrear;

void rearspeed(float speed)
	{
		
	if ((int)PidIncCtrl(&lr,leftrear,speed)>=0)
	{
		motor_speed(LEFTREAR_d,(int)PidIncCtrl(&lr,leftrear,speed));
		motor_speed(LEFTREAR_b,0);

	}
	else
	{
		motor_speed(LEFTREAR_b,-(int)PidIncCtrl(&lr,leftrear,speed));
		motor_speed(LEFTREAR_d,0);

	}
	if((int)PidIncCtrl(&rr,rightrear,speed)>=0)
	{
		motor_speed(RIGHTREAR_d,(int)PidIncCtrl(&rr,rightrear,speed));
		motor_speed(RIGHTREAR_b,0);
	}
	else
	{
		motor_speed(RIGHTREAR_b,-(int)PidIncCtrl(&rr,rightrear,speed));
		motor_speed(RIGHTREAR_d,0);
	}
		
		
	}
void frontspeed(float speed)
	{
		
	if ((int)PidIncCtrl(&lf,leftfront,speed)>=0)
	{
		motor_speed(LEFTFRONT_d,(int)PidIncCtrl(&lr,leftfront,speed));
		motor_speed(LEFTFRONT_b,0);

	}
	else
	{
		motor_speed(LEFTFRONT_b,-(int)PidIncCtrl(&lr,leftfront,speed));
		motor_speed(LEFTFRONT_d,0);

	}
	if((int)PidIncCtrl(&rf,rightfront,speed)>=0)
	{
		motor_speed(RIGHTFRONT_d,(int)PidIncCtrl(&rf,rightfront,speed));
		motor_speed(RIGHTFRONT_b,0);
	}
	else
	{
		motor_speed(RIGHTFRONT_b,-(int)PidIncCtrl(&rf,leftfront,speed));
		motor_speed(RIGHTFRONT_d,0);
	}
		
		
	}

void mecanum_basic(float y,float w)
{
	
	float i=PidIncCtrl(&rf,rightfront,y+w*SUM);
	float j=PidIncCtrl(&rr,rightrear,y+w*SUM);
	float k=PidIncCtrl(&lf,leftfront,y-w*SUM);
	float l=PidIncCtrl(&lr,leftrear,y-w*SUM);
	if(i>=0)
	{
		motor_speed(RIGHTFRONT_d,(int)i);
	}
	else
	{
		motor_speed(RIGHTFRONT_b,-(int)i);
	}
	
	
	if(j>=0)
	{
		motor_speed(RIGHTREAR_d,(int)j);
	}
	else
	{
		motor_speed(RIGHTREAR_b,-(int)j);
	}
	
	
	if(k>=0)
	{
		motor_speed(LEFTFRONT_d,(int)k);
	}
	else
	{
		motor_speed(LEFTFRONT_b,-(int)k);
	}
	if(l>=0)
	{
		motor_speed(LEFTREAR_d,(int)l);
	}
	else
	{
		motor_speed(LEFTREAR_b,-(int)l);
	}
}