/*
 * led.c
 *
 *  Created on: Nov 21, 2024
 *      Author: jdvil
 */


#include "led.h"



HAL_StatusTypeDef ledTimerInit(TIM_HandleTypeDef *ledTimer)
{
	return HAL_TIM_Base_Start_IT(ledTimer);
}


void ledInit(LED_t *led, GPIO_TypeDef *port, uint16_t pin, uint16_t tOn, uint16_t tOff, LED_Logic_t logic)
{
	led->port = port;
	led->pin = pin;
	led->tOn = tOn;
	led->tOff = tOff;
	led->logic = logic;

	led->pinState = HAL_GPIO_ReadPin(led->port, led->pin);

	if(led->logic == LOGIC_POSITIVE) {
		if(led->pinState == GPIO_PIN_SET) {
			led->state = LED_ON;
		} else {
			led->state = LED_OFF;
		}
	} else {
		if(led->pinState == GPIO_PIN_SET) {
			led->state = LED_OFF;
		} else {
			led->state = LED_ON;
		}
	}

	led->ticks = 0;
}

void ledUpdate(LED_t *led)
{
	led->ticks++;

	if(led->state == LED_ON) {
		if(led->ticks >= led->tOn) {
			// Turn off LED
			HAL_GPIO_WritePin(led->port, led->pin, led->logic == LOGIC_POSITIVE ? GPIO_PIN_RESET : GPIO_PIN_SET);
			led->pinState = HAL_GPIO_ReadPin(led->port, led->pin);
			led->state = LED_OFF;
			led->ticks = 0;
		}
	} else {
		if(led->ticks >= led->tOff) {
			// Turn on LED
			HAL_GPIO_WritePin(led->port, led->pin, led->logic == LOGIC_POSITIVE ? GPIO_PIN_SET : GPIO_PIN_RESET);
			led->pinState = HAL_GPIO_ReadPin(led->port, led->pin);
			led->state = LED_ON;
			led->ticks = 0;
		}
	}
}
