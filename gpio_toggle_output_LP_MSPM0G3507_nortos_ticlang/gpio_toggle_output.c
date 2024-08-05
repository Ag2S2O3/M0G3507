/*
 * Copyright (c) 2023, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "ti_msp_dl_config.h"
#include "UART.h"
#include "ssd1106.h"
#include "pid.h"
#include "gary.h"
#include <ti/iqmath/include/IQmathLib.h>


uint8_t M1, M2; //电机数据
float angle_set_2[2] = {0, 175};
float angle_set_3[2] = {-45, 230};
float angle_set_4[8] = {-45, 230, -50, 230, -50, 230, -50, 230};
uint8_t task;


#define speed_xj 20
#define factor 3

//发送清空引脚电平指令
void UART_ClearGPIO(void)
{
    DL_UART_transmitData(UART_Send_INST, 'o');
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, 'w');
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, 'o');
    while (DL_UART_isBusy(UART_Send_INST) == true);
}

//发送停车指令
void UART_Stop(void)
{
    DL_UART_transmitData(UART_Send_INST, '?');
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, '*');
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, '-');
    while (DL_UART_isBusy(UART_Send_INST) == true);
}

//发送清空计数器指令
void UART_Clear(void)
{
    DL_UART_transmitData(UART_Send_INST, '(');
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, '-');
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, ')');
    while (DL_UART_isBusy(UART_Send_INST) == true);
}

//发送两轮速度
void UART_SendM(void)
{
    DL_UART_transmitData(UART_Send_INST, '#');
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, M1);
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, M2);
    while (DL_UART_isBusy(UART_Send_INST) == true);
    DL_UART_transmitData(UART_Send_INST, '!');
    while (DL_UART_isBusy(UART_Send_INST) == true);
}

//角度映射
float AngleMapping(float angle)
{
    if(angle > 0 )
    {
        return angle;
    }
    else 
    {
        return (360+angle);
    }
}

//调用时发出声音
void Shout(void)
{
    DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_PIN_0_PIN);
    DL_Timer_startCounter(TIMER_300ms_INST);
}

//停止发出声音
void TIMER_300ms_INST_IRQHandler(void)
{
    switch (DL_Timer_getPendingInterrupt(TIMER_300ms_INST)) {
        case DL_TIMER_IIDX_ZERO:
            DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_PIN_0_PIN);
            NVIC_ClearPendingIRQ(GPIO_LED_PIN_0_PIN);
            break;
        default:
            break;
    }
}
    
    

int main(void)
{
    SYSCFG_DL_init();

    //UART
    UART_Init();

    //SSD1106
    SSD1106_Init();
    SSD1106_ShowString(1, 0, (u8*) "ML= ", 16);
    SSD1106_ShowString(1, 2, (u8*) "MR= ", 16);
    SSD1106_ShowString(1, 4, (u8*) "Y= ", 16);
    SSD1106_ShowString(1, 6, (u8*) "Task= ", 16);

    //GARY
    GARY_Init();

    //LED
    DL_GPIO_setPins(GPIO_LED_PORT, GPIO_LED_PIN_0_PIN);

    NVIC_EnableIRQ(TIMER_300ms_INST_INT_IRQN);

    float Y = 0;    //当前角度
    float angle = 0;    //当前根据角度需要调整的速度
    uint8_t status = 0; //灰度返回的状态
    float target_angle;  //目标角度
    uint8_t stage = 0;  //寻迹阶段
    uint8_t flag = 0;   //接近目标角度指示
    uint8_t stop_enable = 0;
    uint8_t correct_flag = 0;   //进入修正模式
    uint8_t mode = 0;
    uint8_t mode2 = 0;
    uint8_t shout = 0;
    M1 = 0;
    M2 = 0;

    while (!Get_Task()) ;
    task = Get_Task();
    SSD1106_ShowNum(41, 6, task, 1, 16);
///////////////////////////////////////////////////////////////TASK 1//////////////////////////////////////////////////////////////////
    if (task == 1)
    {
        while(1)
        {
            status = GARY_ReturnS();
            if(UART_GetFlag()==1)
            {
                //计算角度偏差
                if (stage == 1) {
                    Y = AngleMapping(UART_ReturnYaw());
                }
                else
                {
                    Y = UART_ReturnYaw();
                }
                angle = Pid_Angle(0, Y) * 10;
                if(angle > 10)
                    angle = 10;
                if(angle < -10)
                    angle = -10;
                M1 = 30 - angle; M2 = 30 + angle;
            }
            if(status != 0x00)
            {
                UART_Stop();
                if (mode == 0) {
                    Shout();
                    mode = 1;
                }
            }
            SSD1106_ShowFNum(17, 4, Y, 8, 4);    
            UART_SendM();
        }
        
    }

    
///////////////////////////////////////////////////////////////TASK 2//////////////////////////////////////////////////////////////////
    if(task == 2)
    {
        target_angle = angle_set_2[0];
        while (1) {
            status = GARY_ReturnS();
            //接收角度数据
            if(UART_GetFlag()==1)
            {
                //计算角度偏差
                if (stage == 1) {
                    Y = AngleMapping(UART_ReturnYaw());
                }
                else
                {
                    Y = UART_ReturnYaw();
                }
                angle = Pid_Angle(target_angle, Y) * 10;
                if(angle > 10)
                    angle = 10;
                if(angle < -10)
                    angle = -10;

                //接近目标角度指示
                if(correct_flag == 0)
                {
                    if(Y - target_angle  < 10 && Y - target_angle  > -10)
                    {
                        flag = 1;
                    }
                }
            }
            SSD1106_ShowFNum(17, 4, Y, 8, 4);

            switch (status) {
                case 0x40: M1 = speed_xj ; M2 = speed_xj - (factor*6); break;
                case 0x60: M1 = speed_xj ; M2 = speed_xj - (factor*5); break;
                case 0x20: M1 = speed_xj ; M2 = speed_xj - (factor*4); break;
                case 0x30: M1 = speed_xj ; M2 = speed_xj - (factor*3); break;
                case 0x10: M1 = speed_xj ; M2 = speed_xj - (factor*2); break;
                case 0x18: M1 = speed_xj ; M2 = speed_xj - factor; break;
                case 0x08: M1 = speed_xj ; M2 = speed_xj ; break;
                case 0x0C: M1 = speed_xj - (factor*1); M2 = speed_xj ; break;
                case 0x04: M1 = speed_xj - (factor*2); M2 = speed_xj ; break;
                case 0x06: M1 = speed_xj - (factor*3); M2 = speed_xj ; break;
                case 0x02: M1 = speed_xj - (factor*4); M2 = speed_xj ; break;
                case 0x03: M1 = speed_xj - (factor*5); M2 = speed_xj ; break;
                case 0x01: M1 = speed_xj - (factor*6); M2 = speed_xj ; break;
                case 0x00:
                {
                    if(flag == 1)   //进入角度寻迹模式
                    {
                        if(shout == 0)
                        {
                            Shout();
                            shout = 1;
                        }
                        M1 = 30 - angle; M2 = 30 + angle; 
                        if(stop_enable == 1)
                        {
                            UART_Stop();
                        }
                    }
                    break; 
                }
                default: break;
            }
            if (status != 0x00 && flag == 1)    //在角度寻迹的时候发现了线
            {
                flag = 0;   //退出角度寻迹
                shout = 0;
                Shout();
                if (stage == 0)    //进入下一个寻迹阶段
                {
                    stage = 1;  
                    target_angle = angle_set_2[1];
                    correct_flag = 0;
                }
                else if (stage == 1)
                {
                    stage = 2;
                    stop_enable = 1;
                    target_angle = 0;
                    correct_flag = 0;
                }
            }


            UART_SendM();

            SSD1106_ShowFNum(1, 0, stage, 5, 2);
            SSD1106_ShowNum(1, 2, flag,3, 16);
            SSD1106_ShowNum(80, 0, M1 , 2, 16);
            SSD1106_ShowNum(80, 2, M2 , 2, 16);
        }
    }
///////////////////////////////////////////////////////////////TASK 3//////////////////////////////////////////////////////////////////
        if(task == 3)
        {
            target_angle = angle_set_3[0];
            while(1) {
            status = GARY_ReturnS();
            SSD1106_ShowNum(56, 2, stage, 1, 16);
            //接收角度数据
            if(UART_GetFlag()==1)
            {
                //计算角度偏差
                if (stage == 1) {
                    Y = AngleMapping(UART_ReturnYaw());
                }
                else
                {
                    Y = UART_ReturnYaw();
                }
                angle = Pid_Angle(target_angle, Y) * 10;
                if(angle > 10)
                    angle = 10;
                if(angle < -10)
                    angle = -10;

                //接近目标角度指示
                if(correct_flag == 0)
                {
                    if (stage == 0 || stage == 2) {
                        if(Y  < 10 && Y > -10)
                        {
                            flag = 1;
                        }
                    }
                    else if (stage == 1) {
                        if(Y  - 180 < 15 && Y - 180  > -15)
                        {
                            flag = 1;
                        }
                    }
                }
            }
            SSD1106_ShowFNum(17, 4, Y, 8, 4);

            if(correct_flag == 0)
            {
                switch (status) {
                    case 0x40: M1 = speed_xj ; M2 = speed_xj - (factor*6); break;
                    case 0x60: M1 = speed_xj ; M2 = speed_xj - (factor*5); break;
                    case 0x20: M1 = speed_xj ; M2 = speed_xj - (factor*4); break;
                    case 0x30: M1 = speed_xj ; M2 = speed_xj - (factor*3); break;
                    case 0x10: M1 = speed_xj ; M2 = speed_xj - (factor*2); break;
                    case 0x18: M1 = speed_xj ; M2 = speed_xj - factor; break;
                    case 0x08: M1 = speed_xj ; M2 = speed_xj ; break;
                    case 0x0C: M1 = speed_xj - (factor*1); M2 = speed_xj ; break;
                    case 0x04: M1 = speed_xj - (factor*2); M2 = speed_xj ; break;
                    case 0x06: M1 = speed_xj - (factor*3); M2 = speed_xj ; break;
                    case 0x02: M1 = speed_xj - (factor*4); M2 = speed_xj ; break;
                    case 0x03: M1 = speed_xj - (factor*5); M2 = speed_xj ; break;
                    case 0x01: M1 = speed_xj - (factor*6); M2 = speed_xj ; break;
                    case 0x00:
                    {
                        if(flag == 1)   //进入角度寻迹模式
                        {
                            if(shout == 0)
                            {
                                Shout();
                                shout = 1;
                            }
                            M1 = 30 - angle; M2 = 30 + angle; 
                            if(stop_enable == 1)
                            {
                                UART_Stop();
                            }
                            if( stage == 1 && mode == 1 )
                            {
                                UART_Clear();
                                mode = 2;
                            }

                            if ((DL_GPIO_readPins(GPIO_STATE_PORT, GPIO_STATE_P0_PIN | GPIO_STATE_P1_PIN) >> 21) == 1 && mode == 0)  //满足角度修正条件
                            {
                                flag = 0;   //退出角度寻迹
                                shout = 0;
                                if (stage == 0) 
                                {
                                    target_angle = 5;
                                }
                                correct_flag = 1;   //进入角度修正模式
                                mode = 1;
                                UART_ClearGPIO();   //清标识位
                                Shout();
                            }
                            else if((DL_GPIO_readPins(GPIO_STATE_PORT, GPIO_STATE_P0_PIN | GPIO_STATE_P1_PIN) >> 21) == 2 && mode2 !=1)
                            {
                                flag = 0;   //退出角度寻迹
                                if(stage == 1)
                                {
                                    target_angle = 176;
                                }
                                correct_flag = 1;   //进入角度修正模式
                                mode2 = 1;
                                UART_ClearGPIO();   //清标识位
                                Shout();
                            }
                        }
                        break; 
                    }
                    default: break;
                }
            }
            else if (correct_flag == 1) 
            {
                M1 = 20 - angle; M2 = 20 + angle; 
                if ( Y - target_angle < 5 && Y - target_angle > -5)  //角度合适进入下一个寻迹阶段
                {
                    if (stage == 0)    
                    {
                        stage = 1;  
                        target_angle = angle_set_3[1];
                        correct_flag = 0;
                    }
                    else if (stage == 1)
                    {
                        stage = 2;
                        stop_enable = 1;
                        target_angle = 0;
                        correct_flag = 0;
                    }
                }
            }

            SSD1106_ShowNum(25, 0, M1 , 2, 16);
            SSD1106_ShowNum(25, 2, M2 , 2, 16);

            UART_SendM();
        }

    }

///////////////////////////////////////////////////////////////TASK 4//////////////////////////////////////////////////////////////////
        if(task == 4)
        {
            target_angle = angle_set_4[0];
            while(1) {
            status = GARY_ReturnS();
            SSD1106_ShowNum(56, 2, stage, 1, 16);
            //接收角度数据
            if(UART_GetFlag()==1)
            {
                //计算角度偏差
                if (stage == 1 || stage == 3 || stage == 5 || stage == 7) {
                    Y = AngleMapping(UART_ReturnYaw());
                }
                else
                {
                    Y = UART_ReturnYaw();
                }
                angle = Pid_Angle(target_angle, Y) * 10;
                if(angle > 10)
                    angle = 10;
                if(angle < -10)
                    angle = -10;

                //接近目标角度指示
                if(correct_flag == 0)
                {
                    if (stage == 0 || stage == 2 || stage == 4 || stage == 6) {
                        if(Y  < 10 && Y > -10)
                        {
                            flag = 1;
                        }
                    }
                    else if (stage == 1 || stage == 3 || stage == 5 || stage == 7) {
                        if(Y  - 180 < 15 && Y - 180  > -15)
                        {
                            flag = 1;
                        }
                    }
                }
            }
            SSD1106_ShowFNum(17, 4, Y, 8, 4);

            if(correct_flag == 0)
            {
                switch (status) {
                    case 0x40: M1 = speed_xj ; M2 = speed_xj - (factor*6); break;
                    case 0x60: M1 = speed_xj ; M2 = speed_xj - (factor*5); break;
                    case 0x20: M1 = speed_xj ; M2 = speed_xj - (factor*4); break;
                    case 0x30: M1 = speed_xj ; M2 = speed_xj - (factor*3); break;
                    case 0x10: M1 = speed_xj ; M2 = speed_xj - (factor*2); break;
                    case 0x18: M1 = speed_xj ; M2 = speed_xj - factor; break;
                    case 0x08: M1 = speed_xj ; M2 = speed_xj ; break;
                    case 0x0C: M1 = speed_xj - (factor*1); M2 = speed_xj ; break;
                    case 0x04: M1 = speed_xj - (factor*2); M2 = speed_xj ; break;
                    case 0x06: M1 = speed_xj - (factor*3); M2 = speed_xj ; break;
                    case 0x02: M1 = speed_xj - (factor*4); M2 = speed_xj ; break;
                    case 0x03: M1 = speed_xj - (factor*5); M2 = speed_xj ; break;
                    case 0x01: M1 = speed_xj - (factor*6); M2 = speed_xj ; break;
                    case 0x00:
                    {
                        if(flag == 1)   //进入角度寻迹模式
                        {
                            if(shout == 0)
                            {
                                Shout();
                                shout = 1;
                            }
                            M1 = 30 - angle; M2 = 30 + angle; 
                            if(stop_enable == 1)
                            {
                                UART_Stop();
                            }
                            if( stage == 1 && mode == 1 )
                            {
                                UART_Clear();
                                mode = 2;
                            }
                            if( stage > 1 && mode2 == 1 )
                            {
                                UART_Clear();
                                mode2 = 0;
                            }

                            if ((DL_GPIO_readPins(GPIO_STATE_PORT, GPIO_STATE_P0_PIN | GPIO_STATE_P1_PIN) >> 21) == 1 && mode == 0)  //满足角度修正条件
                            {
                                flag = 0;   //退出角度寻迹
                                if (stage == 0) 
                                {
                                    target_angle = 5;
                                }
                                correct_flag = 1;   //进入角度修正模式
                                mode = 1;
                                UART_ClearGPIO();   //清标识位
                                Shout();
                            }
                            else if((DL_GPIO_readPins(GPIO_STATE_PORT, GPIO_STATE_P0_PIN | GPIO_STATE_P1_PIN) >> 21) == 2 && mode2 !=1)
                            {
                                flag = 0;   //退出角度寻迹
                                if(stage == 1 || stage == 3 || stage == 5 || stage == 7)
                                {
                                    target_angle = 180;
                                }
                                else if(stage == 2 || stage == 4 || stage == 6 )
                                {
                                    target_angle = 5;
                                }
                                correct_flag = 1;   //进入角度修正模式
                                mode2 = 1;
                                UART_ClearGPIO();   //清标识位
                                Shout();
                            }
                        }
                        break; 
                    }
                    default: break;
                }
            }
            else if (correct_flag == 1) 
            {
                M1 = 20 - angle; M2 = 20 + angle; 
                if ( Y - target_angle < 5 && Y - target_angle > -5)  //角度合适进入下一个寻迹阶段
                {
                    if (stage < 6)    
                    {
                        stage ++;  
                        target_angle = angle_set_4[stage];
                        correct_flag = 0;
                    }
                    else if (stage == 6)
                    {
                        stage = 7;
                        stop_enable = 1;
                        target_angle = 0;
                        correct_flag = 0;
                    }
                }
            }

            SSD1106_ShowNum(25, 0, M1 , 2, 16);
            SSD1106_ShowNum(25, 2, M2 , 2, 16);

            UART_SendM();
        }

    }

        
}

