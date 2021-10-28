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

void App_Init()
{
	int rslt;

	// Initialize the RX Interrupt.
	// HAL_UART_Receive_IT(&huart2, GetRXBuffer(), 2);

	rslt = BME_Init();

	Display_Init();
}

static char buffer[33];

int App_Task()
{
	struct bme280_data sensor_data;
	BME_GetData(BME280_ALL, &sensor_data);

	// sensor_data.temperature = 1;
	snprintf(buffer, 32, "%f", sensor_data.temperature);

	LCD_Clear();
	LCD_Set_Cursor(1, 1);
	LCD_Write_String("Hello, World");
	LCD_Set_Cursor(2, 1);
	LCD_Write_String(buffer);
	HAL_Delay(1000);

	// Display_Update();
	return 0;
}

