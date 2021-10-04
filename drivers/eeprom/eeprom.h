/*
 * eeprom.h
 *
 * Created: 2/5/2021 9:07:31 AM
 *  Author: Radovan
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_


uint8_t eeprom_multiple_write(uint16_t writeLocation, uint16_t size, uint8_t *data);
uint8_t eeprom_multiple_read(uint16_t readLocation, uint16_t size, uint8_t *buffer);


#endif /* EEPROM_H_ */
