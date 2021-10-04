/*
 * relay.c
 *
 * Created: 2/11/2021 12:59:16 AM
 *  Author: Radovan
 */ 
#include "relay.h"

Gpio_t relay;


void relay_init(void)
{
	gpio_init(&relay, RELAY_PIN, PIN_OUTPUT, PIN_PULL_DOWN);
}
