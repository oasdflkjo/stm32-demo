/*
 * lcd_display.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Velho
 */

#include "lcd_display.h"

#include <string.h>
#include "data_storage.h"

#include <lcd16x2/LCD16x2.h>
#include <sensor_datatype.h>
#include <stdio.h>

#define MAX_LCD_BUFFER_SIZE 34

/*TypeDisplayInfo gTypeDisplayInfo[] =
{
    { "BME 280 Temp \n %0.2f C", SENSOR_TYPE_TEMP },
    { "BME 280 Hum \n %0.2f %%", SENSOR_TYPE_HUMD },
    { "BME 280 Pres \n %0.2f Pa", SENSOR_TYPE_PRESS },
};
*/


static SensorDataType g_display_mode = 0;
static uint8_t g_is_updating = 0;
static char lcd_buffer[MAX_LCD_BUFFER_SIZE];

static float dummy_temperature = 24.432;
static char dummy_string[] = "BME 280 Temp \n%0.2f C";

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

void Display_Init()
{
    LCD_Init();
}

static void Update_Buffer()
{
	// TODO
	// 1. get current mode from button.c
	// 2. get value with that mode from data_storage.c
	// 3. get string with that mode from lookup table
	// some reason i do not understand why is this not working with variables
	snprintf(lcd_buffer, MAX_LCD_BUFFER_SIZE, dummy_string, dummy_temperature);
}

void Display_Draw()
{
 	Update_Buffer();
    if (strlen(lcd_buffer) <= 33)
    {
        LCD_Clear();
        LCD_Set_Cursor(1, 1);
        char *p = lcd_buffer;
        while (*p != '\0')
        {
            if (*p == '\n')
            {
                LCD_Set_Cursor(2, 1);
            }
            else
            {
                LCD_Write_Char(*p);
            }
            p++;
        }
    }
}

void Display_SetMode(SensorDataType mode)
{
    g_display_mode = mode;
}

uint8_t Display_IsUpdating()
{
    return g_is_updating;
}
