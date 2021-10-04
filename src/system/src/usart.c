/*
 * uart.c
 *
 * Created: 1/31/2021 6:13:25 PM
 *  Author: Radovan
 */ 
#include <avr/interrupt.h>
#include "stdbool.h"

#include "rfid.h"
#include "usart.h"
#include "main.h"

#define UART_BAUD				9600
#define UART_BAUDRATE			((F_CPU)/(UART_BAUD*16UL)-1)

uint8_t Rx_Buffer[UART_BUFFER_SIZE] = {0};
uint8_t Rx_Buffer_Size = 0;
uint8_t Rx_Buffer_First = 0;
uint8_t Rx_Buffer_Last = 0;

bool uart_notify = false;

/**
 * @brief 
 */
ISR(USART_RXC_vect)
{
	uint8_t rx_data;

	if (!( UCSRA & ((1<<FE)|(1<<DOR))))	// Check for error
	{
		rx_data = UDR;
		Rx_Buffer[Rx_Buffer_Last++] = rx_data;
		Rx_Buffer_Last &= UART_BUFFER_SIZE - 1;
		if (Rx_Buffer_Size < UART_BUFFER_SIZE)
		{
			Rx_Buffer_Size++;					
		}
		
		if (rx_data == RFID_STOP_BYTE) //TODO izbaciti RFID iz usart system file
		{
			if(Rx_Buffer_Size > RFID_TOTAL_NUM_OF_BYTES-1)
			{
				/* notify when arrived a complete number of card */
				uart_notify = true;
			}
		}
	}
}

void usart_init( void )
{
	/* Set baud rate */
	UBRRH = (UART_BAUDRATE >> 8);
	UBRRL = UART_BAUDRATE;
	/* Enable receiver and transmitter */
	UCSRB = (1<<RXEN)|(1<<RXCIE)|(1<<TXEN);
	/* Set frame format: 8data, 2stop bit */
	UCSRC = (1<<URSEL) | (3<<UCSZ0); // Set frame format: 8data 
	
	
}

void usart_disable(void)
{
	CLR_BIT(UCSRB, RXEN);
	CLR_BIT(UCSRB, RXCIE);
	CLR_BIT(UCSRB, TXEN);
}

void usart_enable(void)
{
	SET_BIT(UCSRB, RXEN);
	SET_BIT(UCSRB, RXCIE);
	SET_BIT(UCSRB, TXEN);
}

void usart_write_udr(uint8_t data )
{
	while (!( UCSRA & (1<<UDRE)));
	UDR = data;
}

uint8_t usart_read_udr(void)
{
	while (!( UCSRA & (1<<RXC)));
	return UDR;
}

uint8_t usart_get_char(void)
{
	uint8_t c = 0;
	
	c = Rx_Buffer[Rx_Buffer_First++];
	Rx_Buffer_First &= UART_BUFFER_SIZE - 1;
	Rx_Buffer_Size--;
	
	return c;
}

uint8_t usart_get_string(uint8_t *s)
{
	uint8_t len = 0;

	while (Rx_Buffer_Size > 0)
	{
		s[len++] = usart_get_char();
	}

	s[len] = '\0';
	
	return len;
}

void usart_put_string( uint8_t *str)
{
	while(*str != '\0')
	{
		usart_write_udr(*str++);
	}
}

unsigned char usart_get_buff_size( void )
{
	return Rx_Buffer_Size;
}

void usart_flush_buff( void )
{
	Rx_Buffer_Size = 0;
	Rx_Buffer_First = 0;
	Rx_Buffer_Last = 0;
	uart_notify = false;
}




