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

/*
static void Update_Sensors()
{
	struct bme280_data sensor_data;
	BME_GetData(BME280_ALL, &sensor_data);

	DataStorage_AppendBuffer(&sensor_data, SENSOR_TYPE_ALL);
}
*/

int App_Init()
{
	Display_Init();
	return 0;
}


int App_Task()
{
	OS_ERR p_err;
	Display_Draw();
	OSTimeDlyHMSM(0, 0, 1, 0, OS_OPT_TIME_HMSM_STRICT, &p_err);
	return 0;
}

