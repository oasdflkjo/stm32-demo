/*
 * lcd_display.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Velho
 */

#include "lcd_display.h"

#include <string.h>
#include "data_storage.h"

#include <os.h>

#include <lcd16x2/LCD16x2.h>
#include <sensor_datatype.h>
#include <stdio.h>

#define LCD_BUFFER_SIZE 34

/*TypeDisplayInfo gTypeDisplayInfo[] =
 {
 { "BME 280 Temp \n %0.2f C", SENSOR_TYPE_TEMP },
 { "BME 280 Hum \n %0.2f %%", SENSOR_TYPE_HUMD },
 { "BME 280 Pres \n %0.2f Pa", SENSOR_TYPE_PRESS },
 };
 */

static SensorDataType g_display_mode = 0;
static uint8_t g_is_updating = 0;
static char lcd_buffer[LCD_BUFFER_SIZE];
static char lcd_current[LCD_BUFFER_SIZE];

//static uint8_t dummy_temperature = 0;
//static char dummy_string[] = "counter :%d";

typedef struct {
	const char *text;
	SensorDataType type;
} TypeDisplayInfo;

/*static TypeDisplayInfo* Get_DisplayInfo(SensorDataType datatype)
 {
 TypeDisplayInfo* display = gTypeDisplayInfo;
 while (display++ != NULL)
 {
 if (display->type == datatype)
 {
 return display;
 }
 }

 return NULL;
 }*/

void Display_Init() {
	LCD_Init();
}

void Update_Buffer() {
	snprintf(lcd_buffer, LCD_BUFFER_SIZE, "still\nworking");
}

void Render_Buffer_to_LCD() {
	LCD_Clear();
	LCD_Set_Cursor(1, 1);
	char *p = lcd_buffer;
	while (*p != '\0') {
		if (*p == '\n') {
			LCD_Set_Cursor(2, 1);
		} else {
			LCD_Write_Char(*p);
		}
		p++;
	}
}

void Display_Draw() {
	OS_ERR err;
	// I don't have any clue why this delay is needed.
	// I encountered a problem that the project gave random outputs
	// to the screen while running without breakpoints in debug. So I
	// had to manually insert dummy "breakpoint"
	OSTimeDly(200, OS_OPT_TIME_DLY, &err);
	Update_Buffer();
	// Currently expects that the buffer is correctly structured
	if (memcmp(lcd_current, lcd_buffer, LCD_BUFFER_SIZE * sizeof(char)) != 0) {
		Render_Buffer_to_LCD();
		memcpy(lcd_current, lcd_buffer, LCD_BUFFER_SIZE * sizeof(char));
	}
}



void Display_SetMode(SensorDataType mode) {
	g_display_mode = mode;
}

uint8_t Display_IsUpdating() {
	return g_is_updating;
}
