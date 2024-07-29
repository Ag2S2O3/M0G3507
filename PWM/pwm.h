#ifndef __PWM_H
#define __PWM_H

#include "ti_msp_dl_config.h"

void PWM_init(void);
void PWM_SetDuty(uint8_t channel, float duty);

#endif