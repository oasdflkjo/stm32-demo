/*
 * lcd_display.h
 *
 *  Created on: Oct 27, 2021
 *      Author: Velho
 */

#ifndef INC_LCD_DISPLAY_H_
#define INC_LCD_DISPLAY_H_

#include <stdint.h>

#define DISPLAY_SENSOR_TEMP     1
#define DISPLAY_SENSOR_HUMD     2
#define DISPLAY_SENSOR_PRES     4

/**
 * @brief
 *
 */
void Display_Init();

/**
 * @brief
 *
 */
void Display_Update();

/**
 * @brief
 *
 */
void Display_SetMode(int mode);

uint8_t Display_IsUpdating();


#endif /* INC_LCD_DISPLAY_H_ */
