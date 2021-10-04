/**
 * @file	buzzer.h
 * @brief	Buzzer driver source file
 * @details
 * @date	
 * @author	Radovan Pljevaljcic
 *
 */

#ifndef BUZZER_H_
#define BUZZER_H_

#include "stdbool.h"
#include "stdint.h"

#define LED_BUZZING_FOREVER		(0xFF)


/**
 * @brief  Initialize software timer for buzzer control
 */
void buzzer_init(void);

/**
 * @brief Turn ON buzzer
 */
void buzzer_on(void);

/**
 * @brief Turn OFF buzzer
 */
void buzzer_off(void);

/**
 * @brief Configures buzzing.
 * @param on_ms - ON time in buzz cycle, in ms
 * @param period_ms - Buzz cycle period, in ms
 *
 * @retval	0 - setting accepted
 * 			1 - something not in limits, settings not accepted
 */
uint8_t buzzer_set_buzzing(uint16_t on_ms, uint16_t buzz_ms);

/**
 * @brief	Start buzzing
 * @param	count - Number of time to execute buzz cycle (ON - OFF). 
			If BUZZER_BUZZ_FOREVER (0xFF), buzzing will be stopped only by next
 * 			command, or by buzzer_stop_buzz() function.
 * @param	blocking - If BUZZER_WAIT, execution is paused until number of
 * 			buzzs executed. BUZZER_NO_WAIT for no blocking of execution.
 */
void buzzer_start_buzzing(uint8_t count, bool blocking);

/**
 * @brief Stop buzzer
 */
void buzzer_stop_buzzing(void);

#endif /* BUZZER_H_ */
