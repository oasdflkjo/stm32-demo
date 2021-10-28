/*
 * bme_sensor.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "bme_sensor.h"
#include "i2c.h"

#include <bme280/bme280.h>

#include <stdint.h>

#define MS_TO_US_DIV	1000
#define DEVICE_ADDR		BME280_I2C_ADDR_PRIM


static uint32_t request_delay = 0;
static uint8_t is_operational = 0;

static struct bme280_dev bme280_device = { 0 };


static void Delay_Ms(uint32_t period, void* intf_ptr)
{
	HAL_Delay(period / MS_TO_US_DIV);
}

static void Configure_Device(struct bme280_dev* device)
{
	device->read = BME_I2C_Read;
	device->write = BME_I2C_Write;

	device->delay_us = Delay_Ms;

	device->intf_ptr = BME280_I2C_ADDR_PRIM;
	device->intf = BME280_I2C_INTF;
}

static int8_t Set_Device_Operational(struct bme280_dev* device)
{
	int8_t rslt;
	uint8_t settings;
//	struct bme280_data


	device->settings.osr_h = BME280_OVERSAMPLING_1X;
	device->settings.osr_p = BME280_OVERSAMPLING_16X;
	device->settings.osr_t = BME280_OVERSAMPLING_2X;

	device->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings = BME280_OSR_PRESS_SEL | BME280_OSR_TEMP_SEL | BME280_OSR_HUM_SEL
			| BME280_STANDBY_SEL | BME280_FILTER_SEL;

	rslt = bme280_set_sensor_settings(settings, device);

	request_delay = bme280_cal_meas_delay(&device->settings);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, device);

	is_operational = rslt == BME280_OK;

	return is_operational;
}

struct bme280_dev* BME_Get_Sensor()
{
	return &bme280_device;
}

int BME_GetData(uint8_t comp_data, struct bme280_data* data)
{
	if (data == NULL)
	{
		return 0;
	}

	int8_t rslt = 0;

	bme280_device.delay_us(100, bme280_device.intf_ptr); // Wait for min amount to request data.

	// int8_t bme280_get_sensor_data(uint8_t sensor_comp, struct bme280_data *comp_data, struct bme280_dev *dev)
	rslt = bme280_get_sensor_data(comp_data, data, &bme280_device);

	return rslt;
}


int BME_Init()
{
	int8_t result = 0;

	Configure_Device(&bme280_device);

	result = bme280_init(&bme280_device);

	return result;
}

