/*
 * File: DWT_Delay.h
 * Driver Name: [[ DWT Delay ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

#ifndef DWT_DELAY_H_
#define DWT_DELAY_H_

#include "stm32l1xx_hal.h"


uint32_t DWT_Delay_Init(void);


// This Function Provides Delay In Microseconds Using DWT
__weak void DWT_Delay_us(volatile uint32_t au32_microseconds);

// This Function Provides Delay In Milliseconds Using DWT
__weak void DWT_Delay_ms(volatile uint32_t au32_milliseconds);
#endif /* DWT_DELAY_H_ */
