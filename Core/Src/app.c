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


void App_Init()
{
	int rslt;

	HAL_UART_Receive_IT(&huart2, GetRXBuffer(), 2);

	rslt = BME_Init();

	Display_Init();
}

int App_Task()
{
	return 0;
}

