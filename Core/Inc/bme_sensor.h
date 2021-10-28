/*
 * bme.h
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#ifndef INC_BME_SENSOR_H_
#define INC_BME_SENSOR_H_

#include <bme280/bme280_defs.h>

extern struct bme280_dev bme280_device;

int BME_Init();

int BME_GetData(struct bme280_data* data);


#endif /* INC_BME_SENSOR_H_ */
