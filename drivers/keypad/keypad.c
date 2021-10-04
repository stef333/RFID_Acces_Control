/**
 * @file	keypad.c
 * @brief	
 * @details
 * @date	
 * @author	Radovan Pljevaljcic
 *
 */
#include "avr/io.h"
#include <util/delay.h>

#include "keypad.h"
#include "main.h"


void keypad_init(void)
{
	DDRB = 0xF0;	/* Lower 4 bits as input, higher 4 bits as output */
	PORTB = 0xFF;	/* Set PORTB with internal pull-ups */
}

uint8_t keypad_scan(void)
{
	uint8_t key = KEYS_RELEASED;
	uint8_t row = 0;
	uint8_t input = 0;
	
	for (row = 0; row < 4; row++)
	{
		/* set all row high first */
		SET_BIT(KEY_PORT, ROW0);
		SET_BIT(KEY_PORT, ROW1);
		SET_BIT(KEY_PORT, ROW2);
		SET_BIT(KEY_PORT, ROW3);
		
		switch(row)
		{
			case 0:
				CLR_BIT(KEY_PORT, ROW0);
				break;
			case 1:
				CLR_BIT(KEY_PORT, ROW1);
				break;
			case 2:
				CLR_BIT(KEY_PORT, ROW2);
				break;
			case 3:
				CLR_BIT(KEY_PORT, ROW3);
				break;
			default:
				break;
		}
		_delay_ms(1.0);
		
		/* read the input */
		input  = (KEY_PIN & (1<<COL0));
		input |= (KEY_PIN & (1<<COL1));
		input |= (KEY_PIN & (1<<COL2));
		input |= (KEY_PIN & (1<<COL3));
		
		/* if it was input (1111 -> 1) */
		if(ALL_LINES != 1) 
		{
			/* wait till the input is gone */
			while(ALL_LINES != 1);
			break;
		}
	}
	
	if(row == 4)
	{
		/* key isn't pressed */
		return KEYS_RELEASED;
	}

	/* switch the rows */
	switch(row)
	{
		case 0:
			switch(input)
			{
				case 0x07:
					key = 'A';
					break;
				case 0x0B: 
					key = '3';
					break;
				case 0x0D: 
					key = '2';
					break;
				case 0x0E: 
					key = '1';
					break;
				default:
					break;
			}
			break;
		case 1:
			switch(input)
			{
				case 0x07:
					key = 'B';
					break;
				case 0x0B:
					key = '6';
					break;
				case 0x0D:
					key = '5';
					break;
				case 0x0E:
					key = '4';
					break;
				default:
					break;
			}
			break;
		case 2:
			switch(input)
			{
				case 0x07:
					key = 'C';
					break;
				case 0x0B:
					key = '9';
					break;
				case 0x0D:
					key = '8';
					break;
				case 0x0E:
					key = '7';
					break;
				default:
					break;
			}
			break;
		case 3:
			switch(input)
			{
				case 0x07:
					key = 'D';
					break;
				case 0x0B:
					key = '*';
					break;
				case 0x0D:
					key = '0';
					break;
				case 0x0E:
					key = '#';
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
	return key;
}
