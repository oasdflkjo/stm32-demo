/*
 * bme.h
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#ifndef INC_BME_SENSOR_H_
#define INC_BME_SENSOR_H_


// TODO Naming gooood?
enum bme_sensor_state {
	BME_INIT_SUCCESS,
	BME_INIT_WARNING,
	BME_INIT_FAILED,
};

int bme_init();

struct bme280_dev* get_bme280_device();


#endif /* INC_BME_SENSOR_H_ */
