/*
 * Copyright (c) 2021, Texas Instruments Incorporated
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
#include "delay.h"
#include "ssd1106.h"
#include "pwm.h"
#include "encoder.h"

uint8_t flag1=0;


int main(void)
{
    SYSCFG_DL_init();
    
    //UART
    UART_Init();
    
    //PWM
    PWM_init();

    //ENCODER
    Encoder_Init();

    //STATE
    DL_GPIO_clearPins(GPIO_STATE_PORT, GPIO_STATE_PIN_1_PIN);
    DL_GPIO_clearPins(GPIO_STATE_PORT, GPIO_STATE_PIN_0_PIN);

    //SSD1106
    SSD1106_Init();
    SSD1106_ShowString(1, 0, (u8*) "R1= ", 16);
    SSD1106_ShowString(1, 2, (u8*) "R2= ", 16);
    SSD1106_ShowString(1, 4, (u8*) "S1= ", 16);
    SSD1106_ShowString(1, 6, (u8*) "S2= ", 16);
    uint8_t M1,M2;
    uint8_t flag2=0;
    uint8_t flag3=0;
    uint8_t stage=0;
    while(1) 
    {		
        if(UART_GetFlag()==1)
        {
            M1 = UART_ReturnM1();
            M2 = UART_ReturnM2();
            // SSD1106_ShowFNum(17, 0, UART_ReturnRoll(), 8, 4);
            // SSD1106_ShowFNum(17, 2, UART_ReturnPitch(), 8, 4);
            if(UART_Stop() == 4)
            {
                M1 = 0;
                M2 = 0;
            }
            Speed_Change(M1, M2);
            SSD1106_ShowNum(25, 0, M1, 2, 16);
            SSD1106_ShowNum(25, 2, M2, 2, 16);
            DL_GPIO_togglePins(GPIO_LED_PORT, GPIO_LED_LED_PIN);

            if (Encoder_GetS() < 5000) 
            {
                
                
            }
            else if(Encoder_GetS() > 5000 && flag2 == 0)
            {
                DL_GPIO_setPins(GPIO_STATE_PORT, GPIO_STATE_PIN_0_PIN);
                DL_GPIO_clearPins(GPIO_STATE_PORT, GPIO_STATE_PIN_1_PIN);   //1
                flag2 = 1;
            }
            if (Encoder_GetS() < 4300) {
                flag3 = 0;
            }
            else if(Encoder_GetS() > 4300 && flag3 == 0)
            {
                flag3 = 1;
                if(stage > 0)
                {
                    DL_GPIO_clearPins(GPIO_STATE_PORT, GPIO_STATE_PIN_0_PIN);
                    DL_GPIO_setPins(GPIO_STATE_PORT, GPIO_STATE_PIN_1_PIN); //2 
                }
                stage++;
            }
            
        }
        SSD1106_ShowNum(25, 4, Encoder_GetS1(), 8, 16);
        SSD1106_ShowNum(25, 6, Encoder_GetS2(), 8, 16);
        
    }
}

