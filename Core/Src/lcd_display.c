/*
 * lcd_display.c
 *
 *  Created on: Oct 28, 2021
 *      Author: Velho
 */

#include "lcd_display.h"

#include "data_storage.h"

#include <lcd16x2/LCD16x2.h>



static uint8_t g_display_mode = 0;
static uint8_t g_is_updating = 0;


void Display_Init()
{
    g_display_mode = DISPLAY_SENSOR_TEMP;

    LCD_Init();
}

void Display_Update()
{
    switch (g_display_mode)
    {
        case DISPLAY_SENSOR_TEMP:

            break;
        case DISPLAY_SENSOR_HUMD:

            break;
        case DISPLAY_SENSOR_PRES:

            break;
    }
}

void Display_SetMode(int mode)
{
    g_display_mode = mode;
}

uint8_t Display_IsUpdating()
{
    return g_is_updating;
}
