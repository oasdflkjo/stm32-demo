/*
 * data_storage.h
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#ifndef INC_DATA_STORAGE_H_
#define INC_DATA_STORAGE_H_

#include <stdint.h>


uint8_t* GetRXBuffer();

void DataStorage_Init();

void DataStorage_Write();
void DataStorage_Read();


#endif /* INC_DATA_STORAGE_H_ */
