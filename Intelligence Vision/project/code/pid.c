#include  "zf_common_headfile.h"
#include "pid.h"

#define  Max 6500
#define Data_Max  6500

/*
InitializePID Structure PID 
*/
/*************************************************************************
 *  �������ƣ�float constrain_float(float amt, float low, float high)
 *  ����˵����pid����ʽ���������
 *  ����˵����
  * @param    pid     pid����
  * @param    error   pid�������
 *  �������أ�PID������   ע���������Ѿ��������ϴν��
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע��
 *************************************************************************/
float PidIncCtrl(pid_param_t * pid, float Encoder,float Target)
{

		pid->error=(float)(Target - Encoder);//��ǰ���
    pid->out_p = pid->kp * (pid->error - pid->last_error);

		//printf("%f",pid->out_p);
    pid->out_i = pid->ki * pid->error;
    pid->out_d = pid->kd * ((pid->error - 2*(pid->last_error)) + pid->last_derivative);

    pid->last_derivative = pid->error - pid->last_error;
    pid->last_error = pid->error;

    pid->out += pid->out_p + pid->out_i + pid->out_d;
//    b =pid->out;//test
		//printf("%f",pid->out);
    return pid->out=func_limit_ab(pid->out, -Max, Max);
}


/*************************************************************************
 *  �������ƣ�float constrain_float(float amt, float low, float high)
 *  ����˵����pidλ��ʽ���������
 *  ����˵����
  * @param    pid     pid����
  * @param    error   pid�������
 *  �������أ�PID������
 *  �޸�ʱ�䣺2020��4��1��
 *  ��    ע��
 *************************************************************************/
float PidLocCtrl(pid_param_t * pid, float Encoder,float Target)
{
	
	pid->error=(float)(Target - Encoder);//��ǰ���
    /* �ۻ���� */
    pid->integrator += pid->error;

    /* ����޷� */
   // constrain_float(pid->integrator, -pid->imax, pid->imax);


    pid->out_p = pid->kp * pid->error;
    pid->out_i = pid->ki * pid->integrator;
    pid->out_d = pid->kd * (pid->error - pid->last_error);

    pid->last_error = pid->error;

    pid->out = pid->out_p + pid->out_i + pid->out_d;

    return pid->out=func_limit_ab(pid->out, -Max, Max);
}


