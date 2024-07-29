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



/* Defines for PWM_0 */
#define PWM_0_INST                                                         TIMG8
#define PWM_0_INST_IRQHandler                                   TIMG8_IRQHandler
#define PWM_0_INST_INT_IRQN                                     (TIMG8_INT_IRQn)
#define PWM_0_INST_CLK_FREQ                                              1000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_0_C0_PORT                                                 GPIOA
#define GPIO_PWM_0_C0_PIN                                          DL_GPIO_PIN_1
#define GPIO_PWM_0_C0_IOMUX                                       (IOMUX_PINCM2)
#define GPIO_PWM_0_C0_IOMUX_FUNC                      IOMUX_PINCM2_PF_TIMG8_CCP0
#define GPIO_PWM_0_C0_IDX                                    DL_TIMER_CC_0_INDEX
/* GPIO defines for channel 1 */
#define GPIO_PWM_0_C1_PORT                                                 GPIOA
#define GPIO_PWM_0_C1_PIN                                          DL_GPIO_PIN_2
#define GPIO_PWM_0_C1_IOMUX                                       (IOMUX_PINCM7)
#define GPIO_PWM_0_C1_IOMUX_FUNC                      IOMUX_PINCM7_PF_TIMG8_CCP1
#define GPIO_PWM_0_C1_IDX                                    DL_TIMER_CC_1_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMG0)
#define TIMER_0_INST_IRQHandler                                 TIMG0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMG0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                           (999U)



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




/* Defines for SPI1 */
#define SPI1_INST                                                          SPI1
#define SPI1_INST_IRQHandler                                    SPI1_IRQHandler
#define SPI1_INST_INT_IRQN                                        SPI1_INT_IRQn
#define GPIO_SPI1_PICO_PORT                                               GPIOB
#define GPIO_SPI1_PICO_PIN                                        DL_GPIO_PIN_8
#define GPIO_SPI1_IOMUX_PICO                                    (IOMUX_PINCM25)
#define GPIO_SPI1_IOMUX_PICO_FUNC                    IOMUX_PINCM25_PF_SPI1_PICO
/* GPIO configuration for SPI1 */
#define GPIO_SPI1_SCLK_PORT                                               GPIOB
#define GPIO_SPI1_SCLK_PIN                                        DL_GPIO_PIN_9
#define GPIO_SPI1_IOMUX_SCLK                                    (IOMUX_PINCM26)
#define GPIO_SPI1_IOMUX_SCLK_FUNC                    IOMUX_PINCM26_PF_SPI1_SCLK



/* Port definition for Pin Group GPIO_LED */
#define GPIO_LED_PORT                                                    (GPIOA)

/* Defines for LED: GPIOA.3 with pinCMx 8 on package pin 43 */
#define GPIO_LED_LED_PIN                                         (DL_GPIO_PIN_3)
#define GPIO_LED_LED_IOMUX                                        (IOMUX_PINCM8)
/* Port definition for Pin Group GPIO_OLED */
#define GPIO_OLED_PORT                                                   (GPIOA)

/* Defines for PIN_SCL: GPIOA.12 with pinCMx 34 on package pin 5 */
#define GPIO_OLED_PIN_SCL_PIN                                   (DL_GPIO_PIN_12)
#define GPIO_OLED_PIN_SCL_IOMUX                                  (IOMUX_PINCM34)
/* Defines for PIN_SDA: GPIOA.13 with pinCMx 35 on package pin 6 */
#define GPIO_OLED_PIN_SDA_PIN                                   (DL_GPIO_PIN_13)
#define GPIO_OLED_PIN_SDA_IOMUX                                  (IOMUX_PINCM35)
/* Port definition for Pin Group GPIO_LCD */
#define GPIO_LCD_PORT                                                    (GPIOA)

/* Defines for ST7789_RST: GPIOA.27 with pinCMx 60 on package pin 31 */
#define GPIO_LCD_ST7789_RST_PIN                                 (DL_GPIO_PIN_27)
#define GPIO_LCD_ST7789_RST_IOMUX                                (IOMUX_PINCM60)
/* Defines for ST7789_A0: GPIOA.26 with pinCMx 59 on package pin 30 */
#define GPIO_LCD_ST7789_A0_PIN                                  (DL_GPIO_PIN_26)
#define GPIO_LCD_ST7789_A0_IOMUX                                 (IOMUX_PINCM59)
/* Defines for ST7789_CS: GPIOA.25 with pinCMx 55 on package pin 26 */
#define GPIO_LCD_ST7789_CS_PIN                                  (DL_GPIO_PIN_25)
#define GPIO_LCD_ST7789_CS_IOMUX                                 (IOMUX_PINCM55)
/* Defines for ST7789_BL: GPIOA.24 with pinCMx 54 on package pin 25 */
#define GPIO_LCD_ST7789_BL_PIN                                  (DL_GPIO_PIN_24)
#define GPIO_LCD_ST7789_BL_IOMUX                                 (IOMUX_PINCM54)
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
/* Port definition for Pin Group GPIO_ENCODER */
#define GPIO_ENCODER_PORT                                                (GPIOA)

/* Defines for MONITOR1_PIN_1: GPIOA.4 with pinCMx 9 on package pin 44 */
// pins affected by this interrupt request:["MONITOR1_PIN_1","MONITOR1_PIN_2","MONITOR2_PIN_1","MONITOR2_PIN_2"]
#define GPIO_ENCODER_INT_IRQN                                   (GPIOA_INT_IRQn)
#define GPIO_ENCODER_INT_IIDX                   (DL_INTERRUPT_GROUP1_IIDX_GPIOA)
#define GPIO_ENCODER_MONITOR1_PIN_1_IIDX                     (DL_GPIO_IIDX_DIO4)
#define GPIO_ENCODER_MONITOR1_PIN_1_PIN                          (DL_GPIO_PIN_4)
#define GPIO_ENCODER_MONITOR1_PIN_1_IOMUX                         (IOMUX_PINCM9)
/* Defines for MONITOR1_PIN_2: GPIOA.5 with pinCMx 10 on package pin 45 */
#define GPIO_ENCODER_MONITOR1_PIN_2_IIDX                     (DL_GPIO_IIDX_DIO5)
#define GPIO_ENCODER_MONITOR1_PIN_2_PIN                          (DL_GPIO_PIN_5)
#define GPIO_ENCODER_MONITOR1_PIN_2_IOMUX                        (IOMUX_PINCM10)
/* Defines for MONITOR2_PIN_1: GPIOA.6 with pinCMx 11 on package pin 46 */
#define GPIO_ENCODER_MONITOR2_PIN_1_IIDX                     (DL_GPIO_IIDX_DIO6)
#define GPIO_ENCODER_MONITOR2_PIN_1_PIN                          (DL_GPIO_PIN_6)
#define GPIO_ENCODER_MONITOR2_PIN_1_IOMUX                        (IOMUX_PINCM11)
/* Defines for MONITOR2_PIN_2: GPIOA.7 with pinCMx 14 on package pin 49 */
#define GPIO_ENCODER_MONITOR2_PIN_2_IIDX                     (DL_GPIO_IIDX_DIO7)
#define GPIO_ENCODER_MONITOR2_PIN_2_PIN                          (DL_GPIO_PIN_7)
#define GPIO_ENCODER_MONITOR2_PIN_2_IOMUX                        (IOMUX_PINCM14)

/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_0_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_UART_0_init(void);
void SYSCFG_DL_SPI1_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */