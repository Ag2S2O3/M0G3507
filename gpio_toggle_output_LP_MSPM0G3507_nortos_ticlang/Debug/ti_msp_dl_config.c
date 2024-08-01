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

/*
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gTIMER_300msBackup;
DL_UART_Main_backupConfig gUART_SendBackup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_TIMER_300ms_init();
    SYSCFG_DL_UART_0_init();
    SYSCFG_DL_UART_Send_init();
    /* Ensure backup structures have no valid state */
	gTIMER_300msBackup.backupRdy 	= false;
	gUART_SendBackup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(TIMER_300ms_INST, &gTIMER_300msBackup);
	retStatus &= DL_UART_Main_saveConfiguration(UART_Send_INST, &gUART_SendBackup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(TIMER_300ms_INST, &gTIMER_300msBackup, false);
	retStatus &= DL_UART_Main_restoreConfiguration(UART_Send_INST, &gUART_SendBackup);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(TIMER_300ms_INST);
    DL_UART_Main_reset(UART_0_INST);
    DL_UART_Main_reset(UART_Send_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(TIMER_300ms_INST);
    DL_UART_Main_enablePower(UART_0_INST);
    DL_UART_Main_enablePower(UART_Send_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_0_IOMUX_TX, GPIO_UART_0_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_0_IOMUX_RX, GPIO_UART_0_IOMUX_RX_FUNC);
    DL_GPIO_initPeripheralOutputFunction(
        GPIO_UART_Send_IOMUX_TX, GPIO_UART_Send_IOMUX_TX_FUNC);
    DL_GPIO_initPeripheralInputFunction(
        GPIO_UART_Send_IOMUX_RX, GPIO_UART_Send_IOMUX_RX_FUNC);

    DL_GPIO_initDigitalInput(GPIO_RESET_BUTTON_IOMUX);

    DL_GPIO_initDigitalOutputFeatures(GPIO_LED_PIN_0_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_DRIVE_STRENGTH_LOW, DL_GPIO_HIZ_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_SPI_OLED_CLK_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SPI_OLED_SDA_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SPI_OLED_CS_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_SPI_OLED_DC_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_GRAY_PIN_1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_GRAY_PIN_2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_GRAY_PIN_3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_GRAY_PIN_4_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_GRAY_PIN_5_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInput(GPIO_GRAY_PIN_6_IOMUX);

    DL_GPIO_initDigitalInput(GPIO_GRAY_PIN_7_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GPIO_STATE_P0_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_STATE_P1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_TASK_BUTTON_1_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_TASK_BUTTON_2_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_TASK_BUTTON_3_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GPIO_TASK_BUTTON_4_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_DOWN,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_clearPins(GPIOA, GPIO_SPI_OLED_CLK_PIN |
		GPIO_SPI_OLED_SDA_PIN |
		GPIO_SPI_OLED_CS_PIN |
		GPIO_SPI_OLED_DC_PIN);
    DL_GPIO_enableOutput(GPIOA, GPIO_SPI_OLED_CLK_PIN |
		GPIO_SPI_OLED_SDA_PIN |
		GPIO_SPI_OLED_CS_PIN |
		GPIO_SPI_OLED_DC_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOA, DL_GPIO_PIN_1_EDGE_FALL |
		DL_GPIO_PIN_2_EDGE_RISE_FALL |
		DL_GPIO_PIN_3_EDGE_RISE_FALL |
		DL_GPIO_PIN_4_EDGE_RISE_FALL |
		DL_GPIO_PIN_5_EDGE_RISE_FALL |
		DL_GPIO_PIN_6_EDGE_RISE_FALL |
		DL_GPIO_PIN_7_EDGE_RISE_FALL |
		DL_GPIO_PIN_8_EDGE_RISE_FALL |
		DL_GPIO_PIN_12_EDGE_RISE |
		DL_GPIO_PIN_13_EDGE_RISE);
    DL_GPIO_setUpperPinsPolarity(GPIOA, DL_GPIO_PIN_23_EDGE_RISE |
		DL_GPIO_PIN_24_EDGE_RISE);
    DL_GPIO_clearInterruptStatus(GPIOA, GPIO_RESET_BUTTON_PIN |
		GPIO_GRAY_PIN_1_PIN |
		GPIO_GRAY_PIN_2_PIN |
		GPIO_GRAY_PIN_3_PIN |
		GPIO_GRAY_PIN_4_PIN |
		GPIO_GRAY_PIN_5_PIN |
		GPIO_GRAY_PIN_6_PIN |
		GPIO_GRAY_PIN_7_PIN |
		GPIO_TASK_BUTTON_1_PIN |
		GPIO_TASK_BUTTON_2_PIN |
		GPIO_TASK_BUTTON_3_PIN |
		GPIO_TASK_BUTTON_4_PIN);
    DL_GPIO_enableInterrupt(GPIOA, GPIO_RESET_BUTTON_PIN |
		GPIO_GRAY_PIN_1_PIN |
		GPIO_GRAY_PIN_2_PIN |
		GPIO_GRAY_PIN_3_PIN |
		GPIO_GRAY_PIN_4_PIN |
		GPIO_GRAY_PIN_5_PIN |
		GPIO_GRAY_PIN_6_PIN |
		GPIO_GRAY_PIN_7_PIN |
		GPIO_TASK_BUTTON_1_PIN |
		GPIO_TASK_BUTTON_2_PIN |
		GPIO_TASK_BUTTON_3_PIN |
		GPIO_TASK_BUTTON_4_PIN);
    DL_GPIO_clearPins(GPIO_LED_PORT, GPIO_LED_PIN_0_PIN);
    DL_GPIO_enableOutput(GPIO_LED_PORT, GPIO_LED_PIN_0_PIN);

}


SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    /* Set default configuration */
    DL_SYSCTL_disableHFXT();
    DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_1);
    DL_SYSCTL_setMCLKDivider(DL_SYSCTL_MCLK_DIVIDER_DISABLE);

}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   20000 Hz = 4000000 Hz / (8 * (199 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_300msClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 199U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_300ms_INST_LOAD_VALUE = (300 ms * 20000 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_300msTimerConfig = {
    .period     = TIMER_300ms_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_ONE_SHOT,
    .startTimer = DL_TIMER_STOP,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_300ms_init(void) {

    DL_TimerA_setClockConfig(TIMER_300ms_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_300msClockConfig);

    DL_TimerA_initTimerMode(TIMER_300ms_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_300msTimerConfig);
    DL_TimerA_enableInterrupt(TIMER_300ms_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_300ms_INST);





}



static const DL_UART_Main_ClockConfig gUART_0ClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_0Config = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_0_init(void)
{
    DL_UART_Main_setClockConfig(UART_0_INST, (DL_UART_Main_ClockConfig *) &gUART_0ClockConfig);

    DL_UART_Main_init(UART_0_INST, (DL_UART_Main_Config *) &gUART_0Config);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_0_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_0_INST, UART_0_IBRD_32_MHZ_115200_BAUD, UART_0_FBRD_32_MHZ_115200_BAUD);


    /* Configure Interrupts */
    DL_UART_Main_enableInterrupt(UART_0_INST,
                                 DL_UART_MAIN_INTERRUPT_RX);


    DL_UART_Main_enable(UART_0_INST);
}

static const DL_UART_Main_ClockConfig gUART_SendClockConfig = {
    .clockSel    = DL_UART_MAIN_CLOCK_BUSCLK,
    .divideRatio = DL_UART_MAIN_CLOCK_DIVIDE_RATIO_1
};

static const DL_UART_Main_Config gUART_SendConfig = {
    .mode        = DL_UART_MAIN_MODE_NORMAL,
    .direction   = DL_UART_MAIN_DIRECTION_TX_RX,
    .flowControl = DL_UART_MAIN_FLOW_CONTROL_NONE,
    .parity      = DL_UART_MAIN_PARITY_NONE,
    .wordLength  = DL_UART_MAIN_WORD_LENGTH_8_BITS,
    .stopBits    = DL_UART_MAIN_STOP_BITS_ONE
};

SYSCONFIG_WEAK void SYSCFG_DL_UART_Send_init(void)
{
    DL_UART_Main_setClockConfig(UART_Send_INST, (DL_UART_Main_ClockConfig *) &gUART_SendClockConfig);

    DL_UART_Main_init(UART_Send_INST, (DL_UART_Main_Config *) &gUART_SendConfig);
    /*
     * Configure baud rate by setting oversampling and baud rate divisors.
     *  Target baud rate: 115200
     *  Actual baud rate: 115211.52
     */
    DL_UART_Main_setOversampling(UART_Send_INST, DL_UART_OVERSAMPLING_RATE_16X);
    DL_UART_Main_setBaudRateDivisor(UART_Send_INST, UART_Send_IBRD_32_MHZ_115200_BAUD, UART_Send_FBRD_32_MHZ_115200_BAUD);



    DL_UART_Main_enable(UART_Send_INST);
}

