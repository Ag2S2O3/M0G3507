/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
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

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for TIMER_300ms */
#define TIMER_300ms_INST                                                 (TIMA0)
#define TIMER_300ms_INST_IRQHandler                             TIMA0_IRQHandler
#define TIMER_300ms_INST_INT_IRQN                               (TIMA0_INT_IRQn)
#define TIMER_300ms_INST_LOAD_VALUE                                      (5999U)



/* Defines for UART_0 */
#define UART_0_INST                                                        UART0
#define UART_0_INST_IRQHandler                                  UART0_IRQHandler
#define UART_0_INST_INT_IRQN                                      UART0_INT_IRQn
#define GPIO_UART_0_RX_PORT                                                GPIOA
#define GPIO_UART_0_TX_PORT                                                GPIOA
#define GPIO_UART_0_RX_PIN                                        DL_GPIO_PIN_11
#define GPIO_UART_0_TX_PIN                                        DL_GPIO_PIN_10
#define GPIO_UART_0_IOMUX_RX                                     (IOMUX_PINCM22)
#define GPIO_UART_0_IOMUX_TX                                     (IOMUX_PINCM21)
#define GPIO_UART_0_IOMUX_RX_FUNC                      IOMUX_PINCM22_PF_UART0_RX
#define GPIO_UART_0_IOMUX_TX_FUNC                      IOMUX_PINCM21_PF_UART0_TX
#define UART_0_BAUD_RATE                                                (115200)
#define UART_0_IBRD_32_MHZ_115200_BAUD                                      (17)
#define UART_0_FBRD_32_MHZ_115200_BAUD                                      (23)
/* Defines for UART_Send */
#define UART_Send_INST                                                     UART3
#define UART_Send_INST_IRQHandler                               UART3_IRQHandler
#define UART_Send_INST_INT_IRQN                                   UART3_INT_IRQn
#define GPIO_UART_Send_RX_PORT                                             GPIOA
#define GPIO_UART_Send_TX_PORT                                             GPIOA
#define GPIO_UART_Send_RX_PIN                                     DL_GPIO_PIN_25
#define GPIO_UART_Send_TX_PIN                                     DL_GPIO_PIN_26
#define GPIO_UART_Send_IOMUX_RX                                  (IOMUX_PINCM55)
#define GPIO_UART_Send_IOMUX_TX                                  (IOMUX_PINCM59)
#define GPIO_UART_Send_IOMUX_RX_FUNC                   IOMUX_PINCM55_PF_UART3_RX
#define GPIO_UART_Send_IOMUX_TX_FUNC                   IOMUX_PINCM59_PF_UART3_TX
#define UART_Send_BAUD_RATE                                             (115200)
#define UART_Send_IBRD_32_MHZ_115200_BAUD                                   (17)
#define UART_Send_FBRD_32_MHZ_115200_BAUD                                   (23)





/* Port definition for Pin Group GPIO_RESET */
#define GPIO_RESET_PORT                                                  (GPIOA)

/* Defines for BUTTON: GPIOA.1 with pinCMx 2 on package pin 34 */
// groups represented: ["GPIO_GRAY","GPIO_TASK","GPIO_RESET"]
// pins affected: ["PIN_1","PIN_2","PIN_3","PIN_4","PIN_5","PIN_6","PIN_7","BUTTON_1","BUTTON_2","BUTTON_3","BUTTON_4","BUTTON"]
#define GPIO_MULTIPLE_GPIOA_INT_IRQN                            (GPIOA_INT_IRQn)
#define GPIO_MULTIPLE_GPIOA_INT_IIDX            (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_RESET_BUTTON_IIDX                               (DL_GPIO_IIDX_DIO1)
#define GPIO_RESET_BUTTON_PIN                                    (DL_GPIO_PIN_1)
#define GPIO_RESET_BUTTON_IOMUX                                   (IOMUX_PINCM2)
/* Port definition for Pin Group GPIO_LED */
#define GPIO_LED_PORT                                                    (GPIOB)

/* Defines for PIN_0: GPIOB.9 with pinCMx 26 on package pin 61 */
#define GPIO_LED_PIN_0_PIN                                       (DL_GPIO_PIN_9)
#define GPIO_LED_PIN_0_IOMUX                                     (IOMUX_PINCM26)
/* Port definition for Pin Group GPIO_SPI_OLED */
#define GPIO_SPI_OLED_PORT                                               (GPIOA)

/* Defines for CLK: GPIOA.14 with pinCMx 36 on package pin 7 */
#define GPIO_SPI_OLED_CLK_PIN                                   (DL_GPIO_PIN_14)
#define GPIO_SPI_OLED_CLK_IOMUX                                  (IOMUX_PINCM36)
/* Defines for SDA: GPIOA.15 with pinCMx 37 on package pin 8 */
#define GPIO_SPI_OLED_SDA_PIN                                   (DL_GPIO_PIN_15)
#define GPIO_SPI_OLED_SDA_IOMUX                                  (IOMUX_PINCM37)
/* Defines for CS: GPIOA.16 with pinCMx 38 on package pin 9 */
#define GPIO_SPI_OLED_CS_PIN                                    (DL_GPIO_PIN_16)
#define GPIO_SPI_OLED_CS_IOMUX                                   (IOMUX_PINCM38)
/* Defines for DC: GPIOA.17 with pinCMx 39 on package pin 10 */
#define GPIO_SPI_OLED_DC_PIN                                    (DL_GPIO_PIN_17)
#define GPIO_SPI_OLED_DC_IOMUX                                   (IOMUX_PINCM39)
/* Port definition for Pin Group GPIO_GRAY */
#define GPIO_GRAY_PORT                                                   (GPIOA)

/* Defines for PIN_1: GPIOA.2 with pinCMx 7 on package pin 42 */
#define GPIO_GRAY_PIN_1_IIDX                                 (DL_GPIO_IIDX_DIO2)
#define GPIO_GRAY_PIN_1_PIN                                      (DL_GPIO_PIN_2)
#define GPIO_GRAY_PIN_1_IOMUX                                     (IOMUX_PINCM7)
/* Defines for PIN_2: GPIOA.3 with pinCMx 8 on package pin 43 */
#define GPIO_GRAY_PIN_2_IIDX                                 (DL_GPIO_IIDX_DIO3)
#define GPIO_GRAY_PIN_2_PIN                                      (DL_GPIO_PIN_3)
#define GPIO_GRAY_PIN_2_IOMUX                                     (IOMUX_PINCM8)
/* Defines for PIN_3: GPIOA.4 with pinCMx 9 on package pin 44 */
#define GPIO_GRAY_PIN_3_IIDX                                 (DL_GPIO_IIDX_DIO4)
#define GPIO_GRAY_PIN_3_PIN                                      (DL_GPIO_PIN_4)
#define GPIO_GRAY_PIN_3_IOMUX                                     (IOMUX_PINCM9)
/* Defines for PIN_4: GPIOA.5 with pinCMx 10 on package pin 45 */
#define GPIO_GRAY_PIN_4_IIDX                                 (DL_GPIO_IIDX_DIO5)
#define GPIO_GRAY_PIN_4_PIN                                      (DL_GPIO_PIN_5)
#define GPIO_GRAY_PIN_4_IOMUX                                    (IOMUX_PINCM10)
/* Defines for PIN_5: GPIOA.6 with pinCMx 11 on package pin 46 */
#define GPIO_GRAY_PIN_5_IIDX                                 (DL_GPIO_IIDX_DIO6)
#define GPIO_GRAY_PIN_5_PIN                                      (DL_GPIO_PIN_6)
#define GPIO_GRAY_PIN_5_IOMUX                                    (IOMUX_PINCM11)
/* Defines for PIN_6: GPIOA.7 with pinCMx 14 on package pin 49 */
#define GPIO_GRAY_PIN_6_IIDX                                 (DL_GPIO_IIDX_DIO7)
#define GPIO_GRAY_PIN_6_PIN                                      (DL_GPIO_PIN_7)
#define GPIO_GRAY_PIN_6_IOMUX                                    (IOMUX_PINCM14)
/* Defines for PIN_7: GPIOA.8 with pinCMx 19 on package pin 54 */
#define GPIO_GRAY_PIN_7_IIDX                                 (DL_GPIO_IIDX_DIO8)
#define GPIO_GRAY_PIN_7_PIN                                      (DL_GPIO_PIN_8)
#define GPIO_GRAY_PIN_7_IOMUX                                    (IOMUX_PINCM19)
/* Port definition for Pin Group GPIO_STATE */
#define GPIO_STATE_PORT                                                  (GPIOA)

/* Defines for P0: GPIOA.21 with pinCMx 46 on package pin 17 */
#define GPIO_STATE_P0_PIN                                       (DL_GPIO_PIN_21)
#define GPIO_STATE_P0_IOMUX                                      (IOMUX_PINCM46)
/* Defines for P1: GPIOA.22 with pinCMx 47 on package pin 18 */
#define GPIO_STATE_P1_PIN                                       (DL_GPIO_PIN_22)
#define GPIO_STATE_P1_IOMUX                                      (IOMUX_PINCM47)
/* Port definition for Pin Group GPIO_TASK */
#define GPIO_TASK_PORT                                                   (GPIOA)

/* Defines for BUTTON_1: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_TASK_BUTTON_1_IIDX                             (DL_GPIO_IIDX_DIO12)
#define GPIO_TASK_BUTTON_1_PIN                                  (DL_GPIO_PIN_12)
#define GPIO_TASK_BUTTON_1_IOMUX                                 (IOMUX_PINCM34)
/* Defines for BUTTON_2: GPIOA.13 with pinCMx 35 on package pin 6 */
#define GPIO_TASK_BUTTON_2_IIDX                             (DL_GPIO_IIDX_DIO13)
#define GPIO_TASK_BUTTON_2_PIN                                  (DL_GPIO_PIN_13)
#define GPIO_TASK_BUTTON_2_IOMUX                                 (IOMUX_PINCM35)
/* Defines for BUTTON_3: GPIOA.23 with pinCMx 53 on package pin 24 */
#define GPIO_TASK_BUTTON_3_IIDX                             (DL_GPIO_IIDX_DIO23)
#define GPIO_TASK_BUTTON_3_PIN                                  (DL_GPIO_PIN_23)
#define GPIO_TASK_BUTTON_3_IOMUX                                 (IOMUX_PINCM53)
/* Defines for BUTTON_4: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_TASK_BUTTON_4_IIDX                             (DL_GPIO_IIDX_DIO24)
#define GPIO_TASK_BUTTON_4_PIN                                  (DL_GPIO_PIN_24)
#define GPIO_TASK_BUTTON_4_IOMUX                                 (IOMUX_PINCM54)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_TIMER_300ms_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_UART_Send_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
