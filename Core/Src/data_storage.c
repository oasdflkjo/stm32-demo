/*
 * data_storage.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "data_storage.h"

static uint8_t echoBuffer[12] = { 0 };
static uint8_t displayBuffer[33] = { 0 };


void DataStorage_AppendBuffer(const char* str)
{

}



uint8_t* GetRxBuffer()
{
	return echoBuffer;
}

void DataStorage_Init()
{

}

void DataStorage_Write()
{
}

void DataStorage_Read()
{

}




