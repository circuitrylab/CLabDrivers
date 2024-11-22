/*
 * led.h
 *
 *  Created on: Nov 21, 2024
 *      Author: jdvil
 */

#ifndef LED_H_
#define LED_H_

#include "main.h"

typedef enum {
	LED_OFF = 0,
	LED_ON
}LED_State_t;

typedef enum {
	LOGIC_NEGATIVE = 0,
	LOGIC_POSITIVE
}LED_Logic_t;

typedef struct {
	GPIO_TypeDef	*port;
	uint16_t		pin;
	GPIO_PinState	pinState;
	LED_State_t		state;
	uint32_t		ticks;
	uint16_t		tOn;
	uint16_t		tOff;
	LED_Logic_t		logic;
}LED_t;

HAL_StatusTypeDef ledTimerInit(TIM_HandleTypeDef *ledTimer);
void ledInit(LED_t *led, GPIO_TypeDef *port, uint16_t pin, uint16_t tOn, uint16_t tOff, LED_Logic_t logic);
void ledUpdate(LED_t *led);

#endif /* LED_H_ */
