#include "ti_msp_dl_config.h"
#include "pid.h"

//PID参数
float kp = 0.2;
float ki = 0.04;
float kd = 0;
float erro_right0 = 0;//当前偏差
float erro_right1 = 0;//上次偏差
float erro_right2 = 0;//上上次偏差
float p_right = 0;//线性项
float i_right = 0;//积分项
float d_right = 0;//微分项


//实际速度与设置速度的值
float Speed_real;
float Speed_set_left = 0;

//PID算法
//输入：设定速度值，实际速度值
//输出：占空比改变量
float Pid_Angle(float speed_set, float speed_real)
{
	float u;
	erro_right0 = speed_set - speed_real;
	p_right = erro_right0 - erro_right1;
	i_right = erro_right0;
	d_right = erro_right0 - 2*erro_right1 + erro_right2;
	u = kp*p_right + ki*i_right + kd*d_right;
	erro_right2 = erro_right1;
	erro_right1 = erro_right0;
	return u;
}
