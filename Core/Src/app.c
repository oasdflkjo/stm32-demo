/*
 * app.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "bme_sensor.h"
#include "lcd_display.h"
#include "data_storage.h"

#include "usart.h"
#include "stm32l1xx_hal_uart.h"

#include "lcd16x2/LCD16x2.h"

#include <stdio.h>

int App_Init()
{
	int rslt;

	// Initialize the RX Interrupt.
	// HAL_UART_Receive_IT(&huart2, GetRXBuffer(), 2);

	rslt = BME_Init();

	Display_Init();

	return rslt;
}


int App_Task()
{
	char buffer[33];
	struct bme280_data sensor_data;
	BME_GetData(BME280_ALL, &sensor_data);

	// sensor_data.temperature = 1;
	snprintf(buffer, 32, "%0.2f", sensor_data.temperature);
			// sensor_data.pressure, sensor_data.humidity);

	LCD_Clear();
	LCD_Set_Cursor(1, 1);
	LCD_Write_String("Temperature");
	LCD_Set_Cursor(2, 1);
	LCD_Write_String(buffer);
	HAL_Delay(10000);

	// Display_Update();
	return 0;
}

