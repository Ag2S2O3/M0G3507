#include "ti/driverlib/m0p/dl_core.h"
#include "delay.h"

void delay_ms(unsigned long ms) 
{
    while(ms--)
	    delay_cycles(CPUCLK_FREQ/1000);
}

void delay_us(unsigned long ms) 
{
    while(ms--)
	    delay_cycles(CPUCLK_FREQ/1000000);
}