/*
 * rfid.c
 *
 * Created: 2/1/2021 8:37:56 PM
 *  Author: Radovan
 */ 
#include "stdint.h"
#include "rfid.h"
#include "usart.h"
#include "lcd.h"
#include "stdbool.h"

#define RFID_SUCCESS				0x00
#define RFID_FAIL					0x01


int8_t rfid_read_card_number( uint8_t *card_nummber )
{
	uint8_t i = 0;
	uint8_t x = 0;
	uint8_t num_of_byte = 0;
	uint8_t curr_val = 0;
	uint8_t buff[UART_BUFFER_SIZE] = {0};
	
	/* read data from uart buffer */
	num_of_byte = usart_get_string(buff);
	
	uart_notify = false;
	
	if (num_of_byte < RFID_TOTAL_NUM_OF_BYTES)
	{
		/* not enought caracter */
		return RFID_FAIL;
	}
	
	do
	{
		curr_val = buff[i++];

		if (curr_val == RFID_START_BYTE)
		{
			while (i < num_of_byte)
			{
				curr_val = buff[i++];

				if (x == 12)
				{
					if (curr_val == RFID_STOP_BYTE)
					{
						/* successfully read card number */
						return RFID_SUCCESS;
					}
					else
					{
						/* no stop byte was detected at the expexted position */
						x=0; /* reset start position */
						break;
					}
				}

				/* check that the number is within the expected range */
				if ( ((curr_val > 47) && (curr_val < 58)) || ((curr_val > 64) && (curr_val < 71)) )
				{
					card_nummber[x++] = curr_val;
				}
				else
				{
					break; /* invalid value of card number */
				}
			}
		}
	}while(i < num_of_byte);

	return RFID_FAIL;
}

int8_t rfid_get_card_number(uint8_t *card_buff)
{
	uint8_t i = 0;
	uint8_t x = 0;
	uint8_t ascii_data = 0;
	int8_t status = 0; // signed
	uint8_t buff[UART_BUFFER_SIZE] = {0};
		
	status = rfid_read_card_number(buff);
	
	if (status != RFID_SUCCESS)
	{
		return RFID_FAIL;
	}
	
	while ( i < 12 )
	{
		ascii_data = buff[i];

		if ((ascii_data > 47) && (ascii_data < 58))
		{
			ascii_data -= 48;
		}
		else if ((ascii_data > 64) && (ascii_data < 71))
		{
			ascii_data -= 55;
		}

		if (i % 2 == 0)
		{
			ascii_data <<= 4;
			card_buff[x] = ascii_data;
		}
		else
		{
			card_buff[x++] |= ascii_data;
		}
		i++;
	}
	
	status = rfid_calc_checksum(card_buff);
	
	if (status == RFID_SUCCESS)
	{
		return RFID_SUCCESS;
	}
	else
	{
		return RFID_FAIL;
	}
	
}

int8_t rfid_calc_checksum(uint8_t *buff)
{
	uint8_t i = 0;
	uint8_t rfid_checksum = 0;
	uint8_t calc_checksum = 0;
	
	/* */
	for ( i = 0; i < 5; i++ )
	{
		calc_checksum ^= buff[i];
	}	
	
	rfid_checksum = buff[i];
	
	if (rfid_checksum == calc_checksum)
	{
		return RFID_SUCCESS;
	}
	else
	{
		return RFID_FAIL;
	}
}
