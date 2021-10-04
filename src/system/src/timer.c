/*
 * timer.c
 *
 * Created: 2/10/2021 8:33:57 PM
 *  Author: Radovan
 */ 
#include <stdint.h>
#include <avr/interrupt.h>

#include "timer.h"



static uint32_t tick_ms = 0;

/**
 * @brief This interrupt function performs increment a global variable "tick_ms"
 *        used as application time base.
 *		  This variable is incremented each 1ms in Timer 0 ISR.
 */
ISR (TIMER0_COMP_vect)	
{
	tick_ms &= MAX_32BIT_VALUE;
	tick_ms++;
}

/* TMR2 Interrupt every 1ms */
ISR (TIMER2_COMP_vect)	
{
	/* Not used for now. */
}


void timer0_init(void)
{
	TCCR0 |= (1<<WGM01); 				/* set CTC mode */
	TIMSK |= (1<<OCIE0);				/* output compare match interrupt enable */
	TCCR0 |= ((1<<CS01) | (1<<CS00));	/* set 64-bit prescaler (16Mhz / 64 = 250kHz) */
	OCR0 = 0xFA; 						/* 250 x (1/250kHz) = 1ms */
}

void timer2_init(void)
{
	TCCR2 |= (1<<WGM21); 	/* set CTC mode */
	TIMSK |= (1<<OCIE2);	/* output compare match interrupt enable */
	TCCR2 |= ((1<<CS22));	/* set 64-bit prescaler (16Mhz / 64 = 250kHz) */
	OCR2 = 0xFA; 			/* 250 x (1/250kHz) = 1ms */
}

uint32_t get_tick_ms(void)
{
	return tick_ms;
}
