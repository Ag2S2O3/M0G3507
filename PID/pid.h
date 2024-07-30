#ifndef __PID_H
#define __PID_H

#include "ti_msp_dl_config.h"

float PID_right(float speed_set,float speed_real);
float PID_left(float speed_set,float speed_real);

#endif