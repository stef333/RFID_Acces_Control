/*
 * relay.h
 *
 * Created: 2/11/2021 12:59:28 AM
 *  Author: Radovan
 */ 


#ifndef RELAY_H_
#define RELAY_H_

#include "gpio.h"

#define RELAY_ON()			gpio_write(&relay, GPIO_PIN_SET);
#define RELAY_OFF()			gpio_write(&relay, GPIO_PIN_RESET);

void relay_init(void);

#endif /* RELAY_H_ */
