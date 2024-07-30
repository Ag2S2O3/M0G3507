#include "ti_msp_dl_config.h"

#define period 1000

void PWM_init(void)
{
    DL_TimerG_startCounter(PWM_0_INST);
}


//修改占空比
//channel:通道值为0,1
//duty：小数0.000~1.000
void PWM_SetDuty(uint8_t channel, float duty)
{
    uint32_t CompareValue;
    CompareValue = period - period*(1-duty); 

    if(channel == 0)
        DL_Timer_setCaptureCompareValue(PWM_0_INST, CompareValue, DL_TIMER_CC_0_INDEX);
    else if(channel == 1)
        DL_Timer_setCaptureCompareValue(PWM_0_INST, CompareValue, DL_TIMER_CC_1_INDEX);
}