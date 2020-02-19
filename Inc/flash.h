/*
 * flash.h
 *
 *  Created on: 2019/09/16
 *      Author: sf199
 */

#ifndef FLASH_H_
#define FLASH_H_

extern const uint32_t start_address; //sentor11 start address
extern const uint32_t end_adress; // sector11 end address

extern uint8_t *flash_test;


void writeFlash(uint32_t , uint16_t *, uint32_t , uint8_t);
void loadFlash(uint32_t, uint16_t *, uint32_t );



#endif /* FLASH_H_ */
