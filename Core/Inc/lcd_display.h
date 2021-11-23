/*
 * lcd_display.h
 *
 *  Created on: Oct 27, 2021
 *      Author: Velho
 *      Edited: Petri Pihla
 */

#ifndef INC_LCD_DISPLAY_H_
#define INC_LCD_DISPLAY_H_

#include <sensor_datatype.h>
#include <stdint.h>

/**
 * @brief
 *
 */
void Display_Init();

/**
 * @brief Updates lcd_buffer[] from data storage
 *
 * TODO: 1. get current mode from button.c
 *	     2. get value with that mode from data_storage.c
 *	     3. get string with that mode from lookup table
 *	     some reason i do not understand why is this not working with variables
 *
 *	     why CubeIDE gives warnings when declaring
 *       this function as a static?
 */
void Update_Buffer();

/**
 * @brief LCD Screen render function
 *
 * Writes Buffer to the LCD and jumps to a next line if \n
 * is encountered. Current behavior with multiple \n is
 * that it jumps to the second line every time.
 * So we are expecting that 16x2 LCD is used.
 *
 * TODO: what happens when there is more than 16 chars on one line?
 *       do we need to handle that somehow?
 *
 *       why CubeIDE gives warnings when declaring
 *       this function as a static?
 */
void Render_Buffer_to_LCD();

/**
 * @brief Executes LCD rendering if it's needed.
 *
 * Compares lcd_buffer[] to lcd_current[]. If they are not the same then
 * LCD screen is updated with the new data. Then the lcd_buffer[] is copied to
 * lcd_current[] to store the current render of the screen.
 */
void Display_Draw();

/**
 * @brief
 *
 */
void Display_SetMode(SensorDataType mode);

/**
 * @brief
 *
 */
uint8_t Display_IsUpdating();

#endif /* INC_LCD_DISPLAY_H_ */
