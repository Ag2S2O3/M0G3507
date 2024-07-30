#include "ti_msp_dl_config.h"
#include "pid.h"

//PID参数
float kp_left = 0.2;
float ki_left = 0.04;
float kd_left = 0;
float kp_right = 0.2;
float ki_right = 0.04;
float kd_right = 0;
float erro_right0 = 0;//当前偏差
float erro_right1 = 0;//上次偏差
float erro_right2 = 0;//上上次偏差
float p_right = 0;//线性项
float i_right = 0;//积分项
float d_right = 0;//微分项
float erro_left0 = 0;//当前偏差
float erro_left1 = 0;//上次偏差
float erro_left2 = 0;//上上次偏差
float p_left = 0;//线性项
float i_left = 0;//积分项
float d_left = 0;//微分项

//实际速度与设置速度的值
float Speed_real_left;
float Speed_real_right;
float Speed_set_left = 0;
float Speed_set_right = 0;

//PID算法，控制右电机转速
//输入：设定速度值，实际速度值
//输出：占空比改变量
float PID_right(float speed_set, float speed_real)
{
	float u;
	erro_right0 = speed_set - speed_real;
	p_right = erro_right0 - erro_right1;
	i_right = erro_right0;
	d_right = erro_right0 - 2*erro_right1 + erro_right2;
	u = kp_right*p_right + ki_right*i_right + kd_right*d_right;
	erro_right2 = erro_right1;
	erro_right1 = erro_right0;
	return u;
}

//PID算法，控制左电机转速
//输入：设定速度值，实际速度值
//输出：占空比改变量
float PID_left(float speed_set,float speed_real)
{
	float u;
	erro_left0 = speed_set - speed_real;
	p_left = erro_left0 - erro_left1;
	i_left = erro_left0;
	d_left = erro_left0 - 2*erro_left1 + erro_left2;
	u = kp_left*p_left + ki_left*i_left + kd_left*d_left;
	erro_left2 = erro_left1;
	erro_left1 = erro_left0;
	return u;
}