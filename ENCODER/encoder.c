#include "ti_msp_dl_config.h"
#include "encoder.h"

uint16_t gEncoderCount1, gEncoderCount2;
uint16_t monitor1, monitor2;
uint32_t gpioA;

//初始化函数
void Encoder_Init(void)
{
    NVIC_ClearPendingIRQ(GPIO_ENCODER_INT_IRQN);
    NVIC_EnableIRQ(GPIO_ENCODER_INT_IRQN);
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);
}

//TIM中断服务函数
void TIMER_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            GetCount();
            break;
        default:
            break;
    }
}

void GetCount(void)
{
    monitor1 = gEncoderCount1;
    monitor2 = gEncoderCount2;
    gEncoderCount1 = 0;
    gEncoderCount2 = 0;
}

//（GPIO模拟）编码器中断
void GROUP1_IRQHandler(void)
{
    //获取中断信号
    gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA,
    GPIO_ENCODER_MONITOR1_PIN_1_PIN | GPIO_ENCODER_MONITOR1_PIN_2_PIN | GPIO_ENCODER_MONITOR2_PIN_1_PIN | GPIO_ENCODER_MONITOR2_PIN_2_PIN);

    //如果是GPIO_ENCODER_MONITOR1_PIN_1_PIN产生的中断
    if((gpioA & GPIO_ENCODER_MONITOR1_PIN_1_PIN) == GPIO_ENCODER_MONITOR1_PIN_1_PIN)
    {
        //Pin0上升沿，看Pin1的电平，为低电平则判断为反转，高电平判断为正转
        if(!DL_GPIO_readPins(GPIOA,GPIO_ENCODER_MONITOR1_PIN_2_PIN))//P1为低电平
        {
            gEncoderCount1--;
        }
        else//P1为高电平
        {
            gEncoderCount1++;
        }
    }
    
    //类似于Stm32中编码器模式的AB两相都测，可得到2倍的计数
    else if((gpioA & GPIO_ENCODER_MONITOR1_PIN_2_PIN) == GPIO_ENCODER_MONITOR1_PIN_2_PIN)
    {
        //Pin1上升沿
        if(!DL_GPIO_readPins(GPIOA,GPIO_ENCODER_MONITOR1_PIN_1_PIN))//P0为低电平
        {
            gEncoderCount2++;
        }
        else//P1为高电平
        {
            gEncoderCount2--;
        }
    }

    else if((gpioA & GPIO_ENCODER_MONITOR2_PIN_1_PIN) == GPIO_ENCODER_MONITOR2_PIN_1_PIN)
    {
        //Pin0上升沿，看Pin1的电平，为低电平则判断为反转，高电平判断为正转
        if(!DL_GPIO_readPins(GPIOA,GPIO_ENCODER_MONITOR2_PIN_2_PIN))//P1为低电平
        {
            gEncoderCount1--;
        }
        else//P1为高电平
        {
            gEncoderCount1++;
        }
    }
    else if((gpioA & GPIO_ENCODER_MONITOR2_PIN_2_PIN) == GPIO_ENCODER_MONITOR2_PIN_2_PIN)
    {
        //Pin0上升沿，看Pin1的电平，为低电平则判断为反转，高电平判断为正转
        if(!DL_GPIO_readPins(GPIOA,GPIO_ENCODER_MONITOR2_PIN_1_PIN))//P1为低电平
        {
            gEncoderCount2--;
        }
        else//P1为高电平
        {
            gEncoderCount2++;
        }
    }
    
    //最后清除中断标志位
    DL_GPIO_clearInterruptStatus(GPIOA, 
    GPIO_ENCODER_MONITOR1_PIN_1_PIN | GPIO_ENCODER_MONITOR1_PIN_2_PIN | GPIO_ENCODER_MONITOR2_PIN_1_PIN | GPIO_ENCODER_MONITOR2_PIN_2_PIN);
}

//返回编码器值1
uint16_t Encoder_GetM1(void)
{
    return monitor1;
}

//返回编码器值2
uint16_t Encoder_GetM2(void)
{
    return monitor2;
}