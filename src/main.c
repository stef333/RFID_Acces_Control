/*
 * TestApp.c
 *
 * Created: 1/24/2021 8:56:40 PM
 * Author : Radovan
 */ 
#include <avr/io.h>
#define F_CPU 16000000UL
#include "main.h"
#include <util/delay.h>

#include "rfid_sm.h"
#include "soft_timer.h"

/**
 * Main state machine handle
 */
static Rfid_sm main_sm_handle;

/**
 * @brief Main function
 */
int main(void)
{		
	rfid_sm_init(&main_sm_handle);
	rfid_sm_enter(&main_sm_handle);

    /* main program */
    while (1) 
	{
    	soft_timer_timeouts_check();
		_delay_ms(1.0);
    }
}
