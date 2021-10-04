/*
 * main.h
 *
 * Created: 1/26/2021 9:37:53 AM
 *  Author: Radovan
 */ 


#ifndef MAIN_H_
#define MAIN_H_

#define SUCCESS		0
#define FAIL		1

/* */
#define SET_BIT(num, n)		(num |= (1UL << n))
/**/
#define CLR_BIT(num, n)		(num &= ~(1UL << n))
/**/
#define TOGG_BIT(num, n)	(num ^= (1 << n))
/**/
#define CHECK_BIT(num, n)	((num >> n) & 1U)
/* */
#define READ_PIN(num, n)	(num & (1 << n))
/* */
#define GET_PIN(num, n)		((num & (1 << n)) >> n)


#endif /* MAIN_H_ */
