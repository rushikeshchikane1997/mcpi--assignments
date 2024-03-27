// ASSINGNMENT2

#include <stdint.h>
#include <stdio.h>
#include "stm32f4xx.h"
#include "system_stm32f4xx.h"

#include "led.h"

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
  #warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif



int main(void)
{
	SystemInit();
	DelayMs(1);
	LedInit(LED_BLUE);
	LedInit(LED_RED);
	LedInit(LED_ORANGE);
	LedInit(LED_GREEN);
	while(1) {
		LedBlink(LED_BLUE, 20);
		LedBlink(LED_RED, 20);
		LedBlink(LED_ORANGE, 20);
		LedBlink(LED_GREEN, 20);


		LedBlink(LED_GREEN, 20);
		LedBlink(LED_ORANGE, 20);
		LedBlink(LED_RED, 20);
		LedBlink(LED_BLUE, 20);
	}
	return 0;
}


