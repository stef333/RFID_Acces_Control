/**
 * @file	led.c
 * @brief	
 * @details
 * @date	
 * @author	Radovan Pljevaljcic
 *
 */
#include <stdlib.h>

#include "led.h"
#include "soft_timer.h"
#include "gpio.h"
#include "main.h"

#define MIN_ON_PERIOD		50
#define MIN_BLINK_PERIOD	100


typedef struct
{
	uint16_t on_time;		/* Store how long ON state of LED lasts. */
	uint16_t blink_period;	/* Store period between two blinks. */
	uint8_t counter;		/* Store number of blinks wanted. If 0xFF, blink forever */
}led_time_t;

led_time_t red;
led_time_t green;

Gpio_t led_red;
Gpio_t led_green;

soft_timer_id_t red_handle;
soft_timer_id_t green_handle;

/**
 * @brief Called when software timer for LED blinkin expires
 */
static void led_red_callback();

/**
 * @brief Called when software timer for LED blinkin expires
 */
static void led_green_callback();


void led_init(void)
{
	soft_timer_get_id(&red_handle);
	soft_timer_get_id(&green_handle);

	gpio_init(&led_red, LED_RED_PIN, PIN_OUTPUT, PIN_PULL_DOWN);
	gpio_init(&led_green, LED_GREEN_PIN, PIN_OUTPUT, PIN_PULL_DOWN);

	/* set param as default */
	red.on_time	= green.on_time			  = MIN_ON_PERIOD;
	red.blink_period = green.blink_period = MIN_BLINK_PERIOD;
	red.counter = green.counter			  = LED_BLINK_FOREVER;

	/* create timer for leds and set callback function */
	soft_timer_create(red_handle,   SOFT_TIMER_MODE_REPEATED, led_red_callback);
	soft_timer_create(green_handle, SOFT_TIMER_MODE_REPEATED, led_green_callback);
}

void led_on(led_t led)
{
	if (led == LED_RED)
	{
		soft_timer_stop(red_handle);
		gpio_write(&led_red, GPIO_PIN_SET);
	}
	else if (led == LED_GREEN)
	{
		soft_timer_stop(green_handle);
		gpio_write(&led_green, GPIO_PIN_SET);
	}
}

void led_off(led_t led)
{
	if (led == LED_RED)
	{
		soft_timer_stop(red_handle);
		gpio_write(&led_red, GPIO_PIN_RESET);
	}
	else if (led == LED_GREEN)
	{
		soft_timer_stop(green_handle);
		gpio_write(&led_green, GPIO_PIN_RESET);
	}
}

uint8_t led_set_blink(led_t led, uint16_t on_ms, uint16_t blink_ms)
{
	/* ON period must be MIN_ON_PERIOD ms or longer */
	if (on_ms < MIN_ON_PERIOD)
	{
		return FAIL;
	}
	
	/* blink period must be at least MIN_BLINK_PERIOD ms longer than 'on' period  */
	if (on_ms > (blink_ms - MIN_BLINK_PERIOD))
	{
		return FAIL;
	}
	
	if (led == LED_RED)
	{
		red.on_time = on_ms;
		red.blink_period = blink_ms;
	}
	else if (led == LED_GREEN)
	{
		green.on_time = on_ms;
		green.blink_period = blink_ms;
	}
	
	return SUCCESS;
}

void led_start_blink(led_t led, uint8_t count)
{
	if (led == LED_RED)
	{
		red.counter = count;
		soft_timer_start(red_handle,  SOFT_TIMER_MIN_TIMEOUT_TICKS, NULL);
	}
	else if (led == LED_GREEN)
	{
		green.counter = count;
		soft_timer_start(green_handle,  SOFT_TIMER_MIN_TIMEOUT_TICKS, NULL);
	}
}

void led_stop_blink(led_t led)
{
	if (led == LED_RED)
	{
		soft_timer_stop(red_handle);
		gpio_write(&led_red, GPIO_PIN_RESET);
	}
	else if (led == LED_GREEN)
	{
		soft_timer_stop(green_handle);
		gpio_write(&led_green, GPIO_PIN_RESET);
	}
}

static void led_red_callback()
{
	/* Toggle pin of the red LED */
	gpio_write(&led_red, GPIO_PIN_TOGGLE);
	
	if (gpio_read(&led_red) != GPIO_PIN_RESET)
	{
		/* LED is ON */
		soft_timer_change_period(red_handle, red.on_time);
	}
	else
	{
		/* LED is OFF */
		if ((red.counter != LED_BLINK_FOREVER) && (red.counter != 0))
		{
			red.counter--;
		}
		
		if (red.counter != 0)
		{
			soft_timer_change_period(red_handle, red.blink_period - red.on_time);
		}
		else
		{
			soft_timer_stop(red_handle);
		}
	}
}

static void led_green_callback()
{
	/* Toggle pin of the green LED */
	gpio_write(&led_green, GPIO_PIN_TOGGLE);
	
	if (gpio_read(&led_green) != GPIO_PIN_RESET)
	{
		/* LED is ON */
		soft_timer_change_period(green_handle, green.on_time);
	}
	else
	{
		/* LED is OFF */
		if ((green.counter != LED_BLINK_FOREVER) && (green.counter != 0))
		{
			green.counter--;
		}
		
		if (green.counter != 0)
		{
			soft_timer_change_period(green_handle, green.blink_period - green.on_time);
		}
		else
		{
			soft_timer_stop(green_handle);
		}
	}
}
