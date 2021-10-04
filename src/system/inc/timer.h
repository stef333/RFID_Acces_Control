/*
 * timer.h
 *
 * Created: 2/10/2021 8:34:08 PM
 *  Author: Radovan
 */ 


#ifndef SYSTEM_TIMER_H_
#define SYSTEM_TIMER_H_

#define MS_IN_SECOND		1000
#define MS_IN_MINUTE		60 * MS_IN_SECOND
#define MS_IN_HOUR			60 * MS_IN_MINUTE
#define MS_IN_DAY			24 * MS_IN_HOUR

/**
 * Maximum value of the 32-bit unsigned variable 
 */
#define MAX_32BIT_VALUE		0xFFFFFFFF

/** 
 * @brief Initialization of timer 0 
 *		  The 8-bit comparator continuously compares TCNT0 with the Output Compare Register (OCR0)
 *		  A match are used to generate an output compare interrupt
 */
void timer0_init(void);

/** 
 * @brief Initialization of timer 2 
 *		  The 8-bit comparator continuously compares TCNT2 with the Output Compare Register (OCR2)
 *		  A match are used to generate an output compare interrupt
 */
void timer2_init(void);

/** 
 * @brief Provides a tick value in millisecond
 *
 * @retval tick value
 */
uint32_t get_tick_ms(void);

#endif /* SYSTEM_TIMER_H_ */
