/*
 * app.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "bme_sensor.h"
#include "lcd_display.h"
#include "data_storage.h"

#include "sensor_datatype.h"

#include "main.h"

#include "lcd16x2/LCD16x2.h"

#include <os.h>

#include <stdio.h>


static void Update_Sensors()
{
	struct bme280_data sensor_data;
	BME_GetData(BME280_ALL, &sensor_data);

	DataStorage_AppendBuffer(&sensor_data, SENSOR_TYPE_ALL);
}

int App_Init()
{
	int rslt;

	// Initialize the RX Interrupt.
	// HAL_UART_Receive_IT(&huart2, GetRXBuffer(), 2);

	DataStorage_Init();
	rslt = BME_Init();

	Display_Init();

	return rslt;
}


int App_Task()
{
	OS_ERR p_err;
	Display_Draw();
	OSTimeDlyHMSM(0, 0, 10, 0, OS_OPT_TIME_HMSM_STRICT, &p_err);
	return 0;
}

