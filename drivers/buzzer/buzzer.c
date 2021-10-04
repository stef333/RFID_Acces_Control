/**
 * @file	buzzer.c
 * @brief	Buzzer driver source file
 * @details
 * @date	
 * @author	Radovan Pljevaljcic
 *
 */
#include <stdlib.h>
#include <util/delay.h>

#include "buzzer.h"
#include "soft_timer.h"
#include "gpio.h"
#include "main.h"

#define MIN_ON_PERIOD		50
#define MIN_BUZZ_PERIOD		200


/* Store how long on state of buzz lasts. */
static uint16_t buzz_on_time = MIN_ON_PERIOD;

/* Store period between two buzz. */
static uint16_t buzz_period = MIN_BUZZ_PERIOD;

/* Store number of buzzs wanted. If 0xFF, buzz forever. */
static uint8_t buzz_counter = 0;

Gpio_t buzzer;

soft_timer_id_t buzzer_handle;


/**
 * @brief Called when software timer for buzzer expires
 */
void buzzer_callback(void *context);

void buzzer_init(void)
{
	soft_timer_get_id(&buzzer_handle);

	gpio_init(&buzzer, BUZZER_PIN, PIN_OUTPUT, PIN_PULL_DOWN);

	soft_timer_create(buzzer_handle, SOFT_TIMER_MODE_REPEATED, &buzzer_callback);
}

void buzzer_on(void)
{
	soft_timer_stop(buzzer_handle);
	gpio_write(&buzzer, GPIO_PIN_SET);
}

void buzzer_off(void)
{
	soft_timer_stop(buzzer_handle);
	gpio_write(&buzzer, GPIO_PIN_RESET);
}

uint8_t buzzer_set_buzzing(uint16_t on_ms, uint16_t buzz_ms)
{
	/* on period must be MIN_ON_PERIOD or longer */
	if (on_ms < MIN_ON_PERIOD)
	{
		return FAIL;
	}
	
	/* buzzing period must be at least MIN_BLINK_PERIOD longer than 'on' period  */
	if (on_ms >= (buzz_ms - MIN_BUZZ_PERIOD))
	{
		return FAIL;
	}
	
	buzz_on_time = on_ms;
	buzz_period = buzz_ms;
	
	return SUCCESS;
}

void buzzer_start_buzzing(uint8_t count, bool blocking)
{
	buzz_counter = count;
	
	gpio_write(&buzzer, GPIO_PIN_SET);
	soft_timer_start(buzzer_handle,  buzz_on_time, NULL);
	
	if(count != 0xFF && blocking == true)
	{
		while(buzz_counter > 0)
		{
			_delay_ms(1.0);
			soft_timer_timeouts_check();
		}
	}
}

void buzzer_stop_buzzing(void)
{
	soft_timer_stop(buzzer_handle);
	gpio_write(&buzzer, GPIO_PIN_RESET);
}

void buzzer_callback(void *context)
{
	gpio_write(&buzzer, GPIO_PIN_TOGGLE);
	
	if (gpio_read(&buzzer) != GPIO_PIN_RESET)
	{
		/* buzzer is ON */
		soft_timer_change_period(buzzer_handle, buzz_on_time);
	}
	else
	{
		/**
		  * Buzzer is OFF, so check if we are buzzing forever, and if not,
		  * decrement counter for buzzes. 
		  */
		if ((buzz_counter != LED_BUZZING_FOREVER) && (buzz_counter != 0))
		{
			buzz_counter--;
		}
		
		if (buzz_counter != 0)
		{
			soft_timer_change_period(buzzer_handle, buzz_period - buzz_on_time);
		}
		else
		{
			soft_timer_stop(buzzer_handle);
		}
	}
}
