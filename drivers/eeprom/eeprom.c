/*
 * eeprom.c
 *
 * Created: 2/5/2021 9:07:20 AM
 *  Author: Radovan Pljevalcic
 *  Author: Stefan Dangubic
 */ 

#include <avr/eeprom.h>


/*@brief Read multiple bytes from the atmega eeprom.
 *
 * @param readLocation: address in eeprom where reading starts
 * @param size: size of reading data in bytes
 * @param buffer: pointer to a buffer where we want to put data from eeprom
 *
 * @warnning size of a buffer must be bigger then parameter size
 *
 * @return 0 if OK, else error
 */
uint8_t eeprom_multiple_read(uint16_t readLocation, uint16_t size, uint8_t *buffer)
{
	uint8_t readBytesCounter = 0;

	while (readBytesCounter < size )
	{
		if(eeprom_is_ready()==0)
		{
			return 1;
		}
		buffer[readBytesCounter]=(eeprom_read_byte((uint8_t*)(readLocation + readBytesCounter)));
		readBytesCounter++;
	}
	return 0;
}

/*@brief Write multiple bytes from the atmega eeprom.
 *
 * @param writeLocation: address in eeprom where writing starts
 * @param size: size of writing data in bytes
 * @param data: pointer to a buffer from where we want to put data in eeprom
 *
 * @warnning size of a buffer must be bigger then parameter size
 *
 * @return 0 if OK, else error
 */
uint8_t eeprom_multiple_write(uint16_t writeLocation, uint16_t size, uint8_t *data)
{
	uint8_t writeBytesCounter = 0;

	while (writeBytesCounter < size )
	{
		if(eeprom_is_ready()==0)
		{
			return 1;
		}
		eeprom_update_byte((uint8_t*)(writeLocation + writeBytesCounter),data[writeBytesCounter]);
		writeBytesCounter++;
	}
	return 0;
}
