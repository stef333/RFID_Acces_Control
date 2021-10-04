/**
 * @file	lcd.h
 * @brief	
 * @details
 * @date	
 * @author	Radovan Pljevaljcic
 *
 */
#ifndef LCD_H_
#define LCD_H_

#include "gpio.h"

#define LCD_ENABLE()		gpio_write(&lcd_en, GPIO_PIN_SET);
#define LCD_DISABLE()		gpio_write(&lcd_en, GPIO_PIN_RESET);

#define LCD_RS_SET()		gpio_write(&lcd_rs, GPIO_PIN_SET);
#define LCD_RS_RESET()		gpio_write(&lcd_rs, GPIO_PIN_RESET);

#define LCD_RW_SET()		gpio_write(&lcd_rw, GPIO_PIN_SET);
#define LCD_RW_RESET()		gpio_write(&lcd_rw, GPIO_PIN_RESET);

#define LCD_E_SET()			gpio_write(&lcd_e, GPIO_PIN_SET);
#define LCD_E_RESET()		gpio_write(&lcd_e, GPIO_PIN_RESET);

void lcd_print_ch(unsigned char);

void lcd_send_string(char *str);

void lcd_init(void);

void lcd_string_xy (char row, char pos, char *str);

void lcd_clear();


#endif /* LCD_H_ */
