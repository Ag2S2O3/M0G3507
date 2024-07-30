#include "ti_msp_dl_config.h"
#include "encoder.h"
#include "pid.h"
#include "pwm.h"

float monitor1, monitor2;   //电极速度（cm/s)
int16_t gEncoderCount;      //GPIO编码返回值
float duty_left, duty_right;    //占空比
uint32_t gpioA; 
float speed_left, speed_right;  //想要设置的速度 (cm/s) 

//初始化函数
void Encoder_Init(void)
{
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    NVIC_EnableIRQ(DECODER_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);
    DL_Timer_startCounter(QEI_0_INST);
    duty_left=0;
    duty_right=0;
    Speed_Change(30, 30);
}

//TIM中断服务函数
void TIMER_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            GetCount();
            Duty_change();
            NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
            break;
        default:
            break;
    }
}

//GPIO中断服务函数
void GROUP1_IRQHandler(void)
{
    //获取中断信号
    gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA,
    DECODER_QEI_1_PIN | DECODER_QEI_2_PIN);
 
    //如果是DECODER_QEI_1_PIN产生的中断
    if((gpioA & DECODER_QEI_1_PIN) == DECODER_QEI_1_PIN)
    {
        //Pin1上升沿，看Pin2的电平，为低电平则判断为反转，高电平判断为正转
        if(!DL_GPIO_readPins(GPIOA,DECODER_QEI_2_PIN))//P2为低电平
        {
            gEncoderCount--;
        }
        else//P2为高电平
        {
            gEncoderCount++;
        }
    }
    
    //类似于Stm32中编码器模式的AB两相都测，可得到2倍的计数
    else if((gpioA & DECODER_QEI_2_PIN) == DECODER_QEI_2_PIN)
    {
        //Pin1上升沿
        if(!DL_GPIO_readPins(GPIOA,DECODER_QEI_1_PIN))//P1为低电平
        {
            gEncoderCount++;
        }
        else//P1为高电平
        {
            gEncoderCount--;
        }
    }
    
    //最后清除中断标志位
    DL_GPIO_clearInterruptStatus(GPIOA, DECODER_QEI_1_PIN|DECODER_QEI_2_PIN);
}

void GetCount(void)
{
    uint16_t test;
    test =  DL_Timer_getTimerCount(QEI_0_INST);
    monitor1 = test * 3.14 * 4.7 / (0.01 * 13 * 20) / 8;
    monitor2 = gEncoderCount * 3.14 * 4.8 / (0.01 * 13 * 20) / 4;
    DL_UART_Main_transmitData(UART_0_INST, test);
    DL_Timer_setTimerCount(QEI_0_INST, 0);
    gEncoderCount = 0;
}


//返回编码器计算速度值
float Encoder_GetM1(void)
{
    return monitor1;
}

float Encoder_GetM2(void)
{
    return monitor2;
}

float Encoder_GetD1(void)
{
    return duty_left;
}

float Encoder_GetD2(void)
{
    return duty_right;
}

//计算并改变占空比
void Duty_change(void)
{
    duty_left += PID_left(speed_left, monitor1);
    duty_right += PID_right(speed_right, monitor2);

    if(duty_left > 0.7)
        duty_left = 0.7;
    else if(duty_left < 0)
        duty_left = 0;
    if(duty_right > 0.7)  
        duty_right = 0.7;
    else if(duty_right < 0)
        duty_right = 0;
    
    PWM_SetDuty(0, duty_right);
    PWM_SetDuty(1, duty_left);
}

//更改电极转速 (左轮，右轮) cm/s
void Speed_Change(float speed_target_left, float speed_target_right)
{
    speed_left = speed_target_left;
    speed_right = speed_target_right;
}