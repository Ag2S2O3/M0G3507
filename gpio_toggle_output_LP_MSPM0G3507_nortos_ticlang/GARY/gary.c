#include "ti_msp_dl_config.h"
#include "UART.h"

uint8_t status;
uint32_t gpioA;
uint8_t choes_task = 0;

#define GPIO_GARY 

//初始化灰度传感器中断
void GARY_Init(void)
{
    NVIC_EnableIRQ(GPIO_MULTIPLE_GPIOA_INT_IRQN);
    status = 0;
}

uint8_t GARY_ReturnS(void)
{
    return status;
}

//GPIO中断服务函数
void GROUP1_IRQHandler(void)
{
    gpioA = DL_GPIO_getEnabledInterruptStatus(GPIOA, GPIO_GRAY_PIN_1_PIN | 
    GPIO_GRAY_PIN_2_PIN | GPIO_GRAY_PIN_3_PIN | GPIO_GRAY_PIN_4_PIN | GPIO_GRAY_PIN_5_PIN | GPIO_GRAY_PIN_6_PIN | GPIO_GRAY_PIN_7_PIN | 
    GPIO_RESET_BUTTON_PIN | GPIO_TASK_BUTTON_1_PIN | GPIO_TASK_BUTTON_2_PIN | GPIO_TASK_BUTTON_3_PIN | GPIO_TASK_BUTTON_4_PIN);
    
    if ((gpioA & GPIO_RESET_BUTTON_PIN) == GPIO_RESET_BUTTON_PIN) {
        UART_RestAngle();
    }

    if ((gpioA & GPIO_TASK_BUTTON_1_PIN) == GPIO_TASK_BUTTON_1_PIN) {
        choes_task = 1;
    }

    if ((gpioA & GPIO_TASK_BUTTON_2_PIN) == GPIO_TASK_BUTTON_2_PIN) {
        choes_task = 2;
    }

    if ((gpioA & GPIO_TASK_BUTTON_3_PIN) == GPIO_TASK_BUTTON_3_PIN) {
        choes_task = 3;
    }

    if ((gpioA & GPIO_TASK_BUTTON_4_PIN) == GPIO_TASK_BUTTON_4_PIN) {
        choes_task = 4;
    }
    
    status = (DL_GPIO_readPins(GPIO_GRAY_PORT, GPIO_GRAY_PIN_1_PIN | 
    GPIO_GRAY_PIN_2_PIN | GPIO_GRAY_PIN_3_PIN | GPIO_GRAY_PIN_4_PIN | GPIO_GRAY_PIN_5_PIN | GPIO_GRAY_PIN_6_PIN | GPIO_GRAY_PIN_7_PIN)) >> 2;
    
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_GRAY_PIN_1_PIN | 
    GPIO_GRAY_PIN_2_PIN | GPIO_GRAY_PIN_3_PIN | GPIO_GRAY_PIN_4_PIN | GPIO_GRAY_PIN_5_PIN | GPIO_GRAY_PIN_6_PIN | GPIO_GRAY_PIN_7_PIN | 
    GPIO_RESET_BUTTON_PIN | GPIO_TASK_BUTTON_1_PIN | GPIO_TASK_BUTTON_2_PIN | GPIO_TASK_BUTTON_3_PIN | GPIO_TASK_BUTTON_4_PIN);
}

uint8_t Get_Task(void)
{
    return choes_task;
}
