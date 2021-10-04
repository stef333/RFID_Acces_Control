/*
 * gpio.c
 *
 * Created: 1/26/2021 10:43:36 AM
 *  Author: Radovan
 */ 

#include <avr/io.h>
#include "main.h"
#include "gpio.h"

void gpio_init( Gpio_t *obj, PinName pin, PinDir dir, PinState state )
{
	/* find index of pin (0-7) */	
	obj->pinIndex = (pin & 0x07);
		
	/* check which port it is */
	if ((pin & 0xF8) == 0x00)  
	{
		/* set direction of pin (i/o) */
		if (dir == PIN_INPUT)
		{
			CLR_BIT(DDRA, obj->pinIndex);
		}
		else
		{
			SET_BIT(DDRA, obj->pinIndex);
		}
		
		obj->port = &PORTA;
	}
	else if ((pin & 0xF8) == 0x08)
	{	
		/* set direction of pin (i/o) */
		if (dir == PIN_INPUT)
		{
			CLR_BIT(DDRB, obj->pinIndex);
		}
		else
		{
			SET_BIT(DDRB, obj->pinIndex);
		}
		
		obj->port = &PORTB;
	}
	else if ((pin & 0xF8) == 0x10)
	{
		/* set direction of pin (i/o) */
		if (dir == PIN_INPUT)
		{
			CLR_BIT(DDRC, obj->pinIndex);
		}
		else
		{
			SET_BIT(DDRC, obj->pinIndex);
		}
		
		obj->port = &PORTC;
	}
	else if ((pin & 0xF8) == 0x18)
	{
		/* set direction of pin (i/o) */
		if (dir == PIN_INPUT)
		{
			CLR_BIT(DDRD, obj->pinIndex);
		}
		else
		{
			SET_BIT(DDRD, obj->pinIndex);
		}
		
		obj->port = &PORTD;
	}
	
	/* set state of pin (high/low) */
	if (state == PIN_PULL_DOWN)
	{
		CLR_BIT((*obj->port), obj->pinIndex);
	}
	else
	{
		SET_BIT((*obj->port), obj->pinIndex);
	}
}


void gpio_write( Gpio_t *obj, uint8_t value )
{
	if (value == GPIO_PIN_SET)
	{
		SET_BIT((*obj->port), obj->pinIndex);
	}
	else if (value == GPIO_PIN_RESET)
	{
		CLR_BIT((*obj->port), obj->pinIndex);
	}
	else if (value == GPIO_PIN_TOGGLE)
	{
		TOGG_BIT((*obj->port), obj->pinIndex);
	}
}

uint8_t gpio_read( Gpio_t *obj )
{
	return READ_PIN((*obj->port), obj->pinIndex);
}
