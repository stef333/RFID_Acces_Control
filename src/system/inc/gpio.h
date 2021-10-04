/*
 * gpio.h
 *
 * Created: 1/26/2021 10:43:45 AM
 *  Author: Radovan
 */ 


#ifndef SYSTEM_GPIO_H_
#define SYSTEM_GPIO_H_

#include <stdint.h>

#include "gpio.h"


#define PIN_LOW		0x00
#define PIN_HIGH	0x01

#define MCU_PINS \
	PA_0 = 0, PA_1, PA_2, PA_3, PA_4, PA_5, PA_6, PA_7,	\
	PB_0, PB_1, PB_2, PB_3, PB_4, PB_5, PB_6, PB_7,		\
	PC_0, PC_1, PC_2, PC_3, PC_4, PC_5, PC_6, PC_7,		\
	PD_0, PD_1, PD_2, PD_3, PD_4, PD_5, PD_6, PD_7

/* PORTA */
#define LCD_RS_PIN			PA_1
#define LCD_RW_PIN			PA_2
#define LCD_E_PIN			PA_3

/* PORTB */

/* PORTC */
#define LED_RED_PIN			PC_3
#define LED_GREEN_PIN		PC_4
#define BUZZER_PIN			PC_5
#define LCD_EN_PIN			PC_7

/* PORTD */
#define EXT_INT0_PIN		PD_2
#define EXT_INT1_PIN		PD_3

#define RELAY_PIN			PD_6


typedef enum
{
	PIN_INPUT = 0,
	PIN_OUTPUT
}PinDir;

typedef enum
{
	PIN_PULL_DOWN = 0,
	PIN_PULL_UP
}PinState;

typedef enum
{
	MCU_PINS
}PinName;

typedef enum
{
	GPIO_PIN_RESET = 0,
	GPIO_PIN_SET,
	GPIO_PIN_TOGGLE
}Gpio_PinState;

typedef struct
{
	PinName pinName;
	PinDir pinDir;
	PinState pinState;
	volatile uint8_t *port;
	uint8_t pinIndex;
}Gpio_t;

/**/
void gpio_init( Gpio_t *obj, PinName pin, PinDir dir, PinState state );

void gpio_write( Gpio_t *obj, uint8_t value );

uint8_t gpio_read( Gpio_t *obj );

#endif /* SYSTEM_GPIO_H_ */
