/*
 * board.c
 *
 * Created: 1/26/2021 9:58:44 AM
 *  Author: Radovan
 */ 
#include <avr/interrupt.h>
#include <util/delay.h>

#include "board.h"
#include "main.h"
#include "gpio.h"

#include "lcd.h"
#include "board.h"
#include "keypad.h"
#include "usart.h"
#include "rfid.h"
#include "timer.h"
#include "soft_timer.h"
#include "led.h"
#include "relay.h"
#include "buzzer.h"


Gpio_t ext_int0;
Gpio_t ext_int1;

static void board_init_mcu(void);


static void board_init_mcu(void)
{
	/* All input */
	DDRA  = 0x00;
	DDRB  = 0x00;
	DDRC  = 0x00;
	DDRD  = 0x00;

	/* Internal pull-ups to avoid floating pins */
	PORTA = 0xFF;
	PORTB = 0xFF;
	PORTC = 0xFF;
	PORTD = 0xFF;	

	gpio_init(&ext_int0, EXT_INT0_PIN, PIN_INPUT, PIN_PULL_UP); /* will be moved */
	gpio_init(&ext_int1, EXT_INT1_PIN, PIN_INPUT, PIN_PULL_UP);
}

/**
 * @brief Initialization of system after boot
 */
void init_interface(void)
{
	board_init_mcu();
	timer0_init();
	soft_timers_init();
	usart_init();

	buzzer_init();
	lcd_init();
	keypad_init();
	led_init();
	relay_init();
	
	lcd_clear();
	led_on(LED_RED);
	led_on(LED_GREEN);
	lcd_send_string("RFID Started");
	_delay_ms(1000.0);
	lcd_clear();

	led_set_blink(LED_GREEN, 100, 1000);
	led_start_blink(LED_GREEN, LED_BLINK_FOREVER);
	led_set_blink(LED_RED, 100, 3000);
	led_start_blink(LED_RED, LED_BLINK_FOREVER);
	buzzer_set_buzzing(50, 200);
	buzzer_start_buzzing(0x02, false);

	/* enable gloabl interrupt */
	sei();	
}
