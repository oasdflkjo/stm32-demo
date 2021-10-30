/*
 * data_storage.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "data_storage.h"

#include <string.h>

#define STORAGE_BUFFER_MASK		STORAGE_BUFFER_LENGTH - 1

/**
 * TODO These buffers are used for testing purposes at the moment.
 */
static uint8_t echoBuffer[12] = { 0 };
static uint8_t displayBuffer[33] = { 0 };

static uint8_t errorBuffer[33] = { 0 };


static DataStorageTypeList gStorageList = { 0 };

static uint8_t Storage_IsTypeAtEnd(DataStorageType* type)
{
	DataStorageType * end = (&gStorageList.storage_list[STORAGE_BUFFER_LENGTH]);
	return type == end;
}

void DataStorage_AppendBuffer(struct bme280_data* sdata, SensorDataType type)
{
	// TODO
	// Check if the Buffer is full and move the tail forward.

	// Create the Storage object.
	DataStorageType storage_object;
	storage_object.data_type = type;
	memcpy(&storage_object.sensor_data, sdata, sizeof(struct bme280_data));

	// Copy the Storage Object into the RingBuffer.
	memcpy(gStorageList.head, &storage_object, sizeof(DataStorageType));

	// End of the buffer.
	if (Storage_IsTypeAtEnd(gStorageList.head))
	{
		gStorageList.head = gStorageList.storage_list;
	}
	else
	{
		// Increase the Head
		gStorageList.head++;
		// TODO Make sure this one works.
		gStorageList.size = (gStorageList.size + 1) % STORAGE_BUFFER_MASK;
	}

}


uint8_t DataStorage_GetDataStorageType(DataStorageType* type, SensorDataType sensor_datatype)
{
	DataStorageType* tmp = gStorageList.storage_list;

	while (tmp != NULL)
	{
		if (tmp->data_type == sensor_datatype)
		{
			type = tmp; // TODO Requires pointer to a pointer?
			return 1;
		}
	}

	return 0;
}


uint8_t* GetRxBuffer()
{
	return echoBuffer;
}

void DataStorage_Init()
{
	gStorageList.head = gStorageList.storage_list;
	gStorageList.tail = gStorageList.storage_list;
	gStorageList.size = 0;
}

void DataStorage_Write()
{
}

void DataStorage_Read()
{

}




