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

static uint8_t dev_addr = BME280_I2C_ADDR_PRIM;

struct bme280_dev bme280_device;


static void Delay_Ms(uint32_t period, void* intf_ptr)
{
	HAL_Delay(period);
}

static void Configure_Device()
{
	bme280_device.read = BME_I2C_Read;
	bme280_device.write = BME_I2C_Write;
	bme280_device.delay_us = Delay_Ms;
	bme280_device.intf_ptr = &dev_addr; // BME280_I2C_ADDR_SEC
	bme280_device.intf = BME280_I2C_INTF;
}
//stream_sensor_data_normal_mode
static int8_t Set_Sensor_NormalMode(struct bme280_dev *dev)
{
	int8_t rslt;
	uint8_t settings_sel;

	/* Recommended mode of operation: Indoor navigation */
	dev->settings.osr_h = BME280_OVERSAMPLING_1X;
	dev->settings.osr_p = BME280_OVERSAMPLING_16X;
	dev->settings.osr_t = BME280_OVERSAMPLING_2X;
	dev->settings.filter = BME280_FILTER_COEFF_16;
	dev->settings.standby_time = BME280_STANDBY_TIME_62_5_MS;

	settings_sel = BME280_OSR_PRESS_SEL;
	settings_sel |= BME280_OSR_TEMP_SEL;
	settings_sel |= BME280_OSR_HUM_SEL;
	settings_sel |= BME280_STANDBY_SEL;
	settings_sel |= BME280_FILTER_SEL;
	rslt = bme280_set_sensor_settings(settings_sel, dev);
	rslt = bme280_set_sensor_mode(BME280_NORMAL_MODE, dev);

	return rslt;
}


static int8_t Set_Device_Operational(struct bme280_dev* device)
{
	return Set_Sensor_NormalMode(device);
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

	bme280_device.delay_us(70, bme280_device.intf_ptr);
	rslt = bme280_get_sensor_data(comp_data, data, &bme280_device);

	return rslt;
}


int BME_Init()
{
	int8_t result = 0;

	Configure_Device();
	Set_Device_Operational(&bme280_device);

	result = bme280_init(&bme280_device);

	return result;
}

