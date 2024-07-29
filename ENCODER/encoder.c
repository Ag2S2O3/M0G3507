#include "ti_msp_dl_config.h"
#include "encoder.h"

int16_t monitor1, monitor2;
int16_t gEncoderCount;
uint32_t gpioA;

//初始化函数
void Encoder_Init(void)
{
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
    NVIC_EnableIRQ(DECODER_INT_IRQN);
    DL_TimerG_startCounter(TIMER_0_INST);
    DL_Timer_startCounter(QEI_0_INST);
}

//TIM中断服务函数
void TIMER_0_INST_IRQHandler(void)
{
    switch (DL_TimerG_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            GetCount();
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
    monitor1 = DL_Timer_getTimerCount(QEI_0_INST);
    monitor2 = gEncoderCount;
    DL_Timer_setTimerCount(QEI_0_INST, 0);
    gEncoderCount = 0;
}


//返回编码器值
int16_t Encoder_GetM1(void)
{
    return monitor1;
}

int16_t Encoder_GetM2(void)
{
    return monitor2;
}
