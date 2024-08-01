#include "UART.h"
#include "ti/driverlib/m0p/dl_core.h"
#include "ti_msp_dl_config.h"
#include "pwm.h"
#include "encoder.h"

uint8_t gEchoData;
uint8_t flag;
uint8_t stage;
uint8_t M1;
uint8_t M2;
uint8_t stop_flag;
uint8_t clear_flag;
uint8_t gpio_flag;


//初始化函数
void UART_Init(void)
{
    NVIC_ClearPendingIRQ(UART_0_INST_INT_IRQN);
    NVIC_EnableIRQ(UART_0_INST_INT_IRQN);
    stage=0;
    M1=0;
    M2=0;
    stop_flag=0;
}


//中断服务函数
void UART_0_INST_IRQHandler(void)
{
    switch (DL_UART_Main_getPendingInterrupt(UART_0_INST)) {
        case DL_UART_MAIN_IIDX_RX:
            flag=1;
            gEchoData = DL_UART_Main_receiveData(UART_0_INST);
            Data_Decoder(gEchoData);
            break;
        default:
            break;
    }
}

//返回接收的数据
uint8_t UART_Recive(void)
{
    return gEchoData;
}


//返回中断标志位
uint8_t UART_GetFlag(void)
{
    if(flag==1)
    {
        return 1;
        flag=0;
    }
    else {
        return 0;
    }
        
}

void Data_Decoder(uint8_t data)
{
    if(stage == 0)  //等待接收数据头（#）
    {
        if(data == '#')
            stage = 1;
    }
    else if(stage > 0 && stage < 3)
    {
        switch (stage) {
            case 1: M1 = data; break;
            case 2: M2 = data; break;
        }
        stage++;
    }
    else if(stage == 3) //等待接收数据尾（!）
    {
        if (data == '!') {
            stage = 0;
        }
    }
    
    //接收停车指令
    if(stop_flag == 0)
    {
        if(data == '?')    
        {
            stop_flag = 1;
        } 
    }
    else if (stop_flag == 1) 
    {
        if(data == '*')
        {
            stop_flag = 2;
        }
        else 
        {
            stop_flag = 0;
        }
    }
    else if(stop_flag == 2)
    {
        if (data == '-') 
        {
            stop_flag = 4;
        }
        else
        {
            stop_flag = 0;
        }
    }

    //接收清空指令
    if(clear_flag == 0)
    {
        if(data == '(')    
        {
            clear_flag = 1;
        } 
    }
    else if (clear_flag == 1) 
    {
        if(data == '-')
        {
            clear_flag = 2;
        }
        else 
        {
            clear_flag = 0;
        }
    }
    else if(clear_flag == 2)
    {
        if (data == ')') 
        {
            clear_flag = 0;
            Encoder_Clear();
        }
    }

    //接收清空引脚电平指令
    if(gpio_flag == 0)
    {
        if(data == 'o')    
        {
            gpio_flag = 1;
        } 
    }
    else if (gpio_flag == 1) 
    {
        if(data == 'w')
        {
            gpio_flag = 2;
        }
        else 
        {
            gpio_flag = 0;
        }
    }
    else if(gpio_flag == 2)
    {
        if (data == 'o') 
        {
            gpio_flag = 0;
            DL_GPIO_clearPins(GPIO_STATE_PORT, GPIO_STATE_PIN_0_PIN);
            DL_GPIO_clearPins(GPIO_STATE_PORT, GPIO_STATE_PIN_1_PIN);
        }
    }
}

float UART_ReturnM1(void)
{
    return M1;
}

float UART_ReturnM2(void)
{
    return M2;
}

uint8_t UART_Stop(void)
{
    return stop_flag;
}