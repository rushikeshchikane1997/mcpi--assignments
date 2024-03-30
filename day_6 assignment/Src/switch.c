/*
 * switch.c
 *
 *  Created on: Mar 27, 2024
 *      Author: Nilesh
 */

#include "switch.h"

void SwitchInit(uint32_t pin) {
	// enable gpio clock (in AHB1ENR)
	RCC->AHB1ENR |= BV(SWITCH_GPIO_EN);
	// set gpio pin as input (in MODER)
	SWITCH_GPIO->MODER &= ~(BV(pin * 2 + 1) | BV(pin * 2));
	// set gpio pin speed to low (in OSPEEDR)
	SWITCH_GPIO->OSPEEDR &= ~(BV(pin * 2 + 1) | BV(pin * 2));
	// set gpio pin no pull up, no pull down (in PUPDR)
	SWITCH_GPIO->PUPDR &= ~(BV(pin * 2 + 1) | BV(pin * 2));
	// enable falling edge detection (in FTSR)
	EXTI->FTSR |= BV(SWITCH);
	// enable (unmask) exti interrupt (in IMR)
	EXTI->IMR |= BV(SWITCH);
	// select exti interrupt (in SYSCFG->EXTICRx)
	SYSCFG->EXTICR[0] &= ~(BV(3) | BV(2) | BV(1) | BV(0));
	// enable exti in NVIC (ISER or NVIC_EnableIRQ())
	//NVIC->ISER[0] |= BV(EXTI0_IRQn);
	NVIC_EnableIRQ(EXTI0_IRQn);
}

int SwitchGetState(uint32_t pin) {
	// read gpio pin
	uint32_t state = SWITCH_GPIO->IDR;
	// return 1 if pin in high, otherwise return 0
	if(state & BV(pin))
		return 1;
	return 0;
}

// Global flag for interrupt
volatile int exti0_flag = 0;

// Switch EXTT0 IRQ Handler
void EXTI0_IRQHandler(void) {
    // Acknowledge interrupt (in PR)
	EXTI->PR |= BV(SWITCH);
	// Handle interrupt

	exti0_flag = 1;
}

/*
#include "stm32f4xx_hal.h"
#include "lcd.h" // You need to include the LCD library for your specific LCD

uint32_t count = 0; // Global count variable

void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0); // Handle EXTI interrupt
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    if (GPIO_Pin == GPIO_PIN_0) // Check if the interrupt is from the switch
    {
        count++; // Increment the global count variable
        // Display count on LCD
        lcd_clear();
        lcd_printf("Count: %lu", count);
    }
}

int main(void)
{
    HAL_Init();
    // Initialize LCD and GPIO for the switch
    // (configure the switch pin as input with interrupt)

    // Start the LCD
    lcd_init();
    lcd_clear();

    while (1)
    {
        // Main loop, nothing to do here
    }
}


*/








