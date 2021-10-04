/**
 * @file	keypad.h
 * @brief	
 * @details
 * @date	
 * @author	Radovan Pljevaljcic
 *
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#define KEY_PORT 	PORTB
#define KEY_DDR		DDRB
#define KEY_PIN		PINB

#define KEYS_RELEASED 0

#define COL0	0
#define COL1	1
#define COL2	2
#define COL3	3

#define ROW0	4
#define ROW1	5
#define ROW2	6
#define ROW3	7


#define ALL_LINES	(((KEY_PIN & (1U<<COL0)) >> COL0) & \
					((KEY_PIN & (1U<<COL1)) >> COL1) &	\
					((KEY_PIN & (1U<<COL2)) >> COL2) &	\
					((KEY_PIN & (1U<<COL3)) >> COL3))


/**
 * @brief Port initialization for keypad
 */
void keypad_init(void);

/**
 * @brief Port initialization for keypad
 *
 * @retval 0 If key isn't pressed
 * @retval   Otherwise returns ascii to the key pressed
 */
uint8_t keypad_scan(void);

#endif /* KEYPAD_H_ */
