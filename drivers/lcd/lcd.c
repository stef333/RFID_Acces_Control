/**
 * @file	lcd.c
 * @brief	
 * @details
 * @date	
 * @author	Radovan Pljevaljcic
 *
 */
#include <util/delay.h>
#include "avr/io.h"

#include "lcd.h"


Gpio_t lcd_en;
Gpio_t lcd_rs;
Gpio_t lcd_rw;
Gpio_t lcd_e;

void lcd_cmd(unsigned char);

void lcd_init()
{
	gpio_init(&lcd_en, LCD_EN_PIN, PIN_OUTPUT, PIN_PULL_UP);
	gpio_init(&lcd_rs, LCD_RS_PIN, PIN_OUTPUT, PIN_PULL_DOWN);
	gpio_init(&lcd_rw, LCD_RW_PIN, PIN_OUTPUT, PIN_PULL_DOWN);
	gpio_init(&lcd_e, LCD_E_PIN, PIN_OUTPUT, PIN_PULL_DOWN);

	LCD_ENABLE();
	_delay_ms(2.0);
	lcd_cmd(0x33);
	lcd_cmd(0x32);	/* Send for 4 bit initialization of LCD  */
	lcd_cmd(0x28);	/* 2 line, 5*7 matrix in 4-bit mode */
	lcd_cmd(0x0c);	/* Display on cursor off */
	lcd_cmd(0x06);	/* Increment cursor (shift cursor to right) */
	lcd_cmd(0x01);	/* Clear display screen */
	lcd_cmd(0x80);
}

void lcd_cmd(unsigned char cmd)
{
	PORTA = (PORTA & 0x0F) | (cmd & 0xF0);	/* Sending upper nibble */
	LCD_RS_RESET();		/* RS=0, command reg. */
	LCD_E_SET();			/* Enable pulse */
	_delay_us(1.0);
	LCD_E_RESET();
	_delay_us(200.0);
	PORTA = (PORTA & 0x0F) | (cmd << 4);/* Sending lower nibble */
	LCD_E_SET();
	_delay_us(1.0);
	LCD_E_RESET();
	_delay_ms(2.0);
}

void lcd_print_ch(unsigned char ch)
{
	PORTA = (PORTA & 0x0F) | (ch & 0xF0);/* Sending upper nibble */
	LCD_RS_SET();  /* RS=1, data reg. */
	LCD_E_SET();
	_delay_us(1.0);
	LCD_E_RESET();
	_delay_us(200.0);
	
	PORTA = (PORTA & 0x0F) | (ch << 4);  /* Sending lower nibble */
	LCD_E_SET();
	_delay_us(1.0);
	LCD_E_RESET();
	_delay_ms(2.0);
}

void lcd_send_string(char *str)
{
	while(*str > 0)
	{
		lcd_print_ch(*str++);
	}
}

void lcd_string_xy (char row, char pos, char *str)	/* Send string to LCD with xy position */
{
	if (row == 0 && pos<16)
	{
		lcd_cmd((pos & 0x0F)|0x80);	/* Command of first row and required position<16 */
	}
	else if (row == 1 && pos<16)
	{
		lcd_cmd((pos & 0x0F)|0xC0);	/* Command of first row and required position<16 */
	}
	lcd_send_string(str);		/* Call LCD string function */
}

void lcd_clear()
{
	lcd_cmd (0x01);		/* Clear display */
	_delay_ms(2.0);
	lcd_cmd (0x80);		/* Cursor at home position */
}
