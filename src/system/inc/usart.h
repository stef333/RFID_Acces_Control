/*
 * uart.h
 *
 * Created: 1/31/2021 6:13:35 PM
 *  Author: Radovan
 */ 


#ifndef UART_H_
#define UART_H_

#include "stdbool.h"

extern bool uart_notify;


/* don't use a buffer size larger than 0xFF */
#define UART_BUFFER_SIZE	127


void usart_init( void );

void usart_disable(void);

void usart_enable(void);

void usart_write_udr( uint8_t data );

uint8_t usart_read_udr(void);

uint8_t usart_get_char(void);

uint8_t usart_get_string(uint8_t *s);

void usart_put_string(uint8_t *str);

uint8_t usart_get_buff_size( void );

void usart_flush_buff(void);

#endif /* UART_H_ */
