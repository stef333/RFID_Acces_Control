/*
 * rfid.h
 *
 * Created: 2/1/2021 8:38:04 PM
 *  Author: Radovan
 */ 


#ifndef RFID_H_
#define RFID_H_

#define RFID_START_BYTE				0x02
#define RFID_STOP_BYTE				0x03

#define RFID_CARD_NUM_LEN			0x05	/* Number of card data bytes after checksum valid (after conversion) */
#define RFID_NUM_OF_DATA			0x0A	/* 10ASCII Data Character */
#define RFID_DATA_WITH_CHKSUM		0x0C	/* Number of card data with checksum */
#define RFID_TOTAL_NUM_OF_BYTES		0x0E	/* START BYTE (1B) | CARD NUMBER (10B) | CHECKSUM (2B) | STOP BYTE (1B) */

/**
 * @brief Read card number from uart buffer and 
 * check if there is valid data as expected
 *  
 * START BYTE (1B) | CARD NUMBER (10B) | CHECKSUM (2B) | STOP BYTE (1B) 
 *
 * @param card_nummber Pointer to the buffer where the data will be stored
 */
int8_t rfid_read_card_number( uint8_t *buff );

int8_t rfid_get_card_number(uint8_t *buff);

int8_t rfid_calc_checksum(uint8_t *buff);


#endif /* RFID_H_ */
