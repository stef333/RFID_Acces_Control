/**
 * @file	led.h
 * @brief	
 * @details
 * @date	
 * @author	Radovan Pljevaljcic
 *
 */
#ifndef LED_H_
#define LED_H_

#include "stdint.h"

#define LED_BLINK_FOREVER		(0xFF)

typedef enum
{
	LED_RED,
	LED_GREEN	
}led_t;

void led_init(void);

void led_on(led_t led);

void led_off(led_t led);

uint8_t led_set_blink(led_t led, uint16_t on_ms, uint16_t blink_ms);

void led_start_blink(led_t led, uint8_t count);

void led_stop_blink(led_t led);


#endif /* LED_H_ */
