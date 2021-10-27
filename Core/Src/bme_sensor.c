/*
 * bme_sensor.c
 *
 *  Created on: Oct 26, 2021
 *      Author: Velho
 */

#include "bme_sensor.h"

#include <stdint.h>

#include <bme280/bme280.h>

#define BME_DELAY(MS, X) \
		HAL_Delay(MS)

struct bme280_dev g_device;

static int8_t BME_I2C_Reg_Write(uint8_t reg_addr, const uint8_t *reg_data,
		uint32_t len, void *intf_ptr);

static int8_t BME_I2C_Reg_Read(uint8_t reg_addr, uint8_t *reg_data,
		uint32_t len, void *intf_ptr);



static struct bme280_dev* configure_device(struct bme280_dev*);


static struct bme280_dev* configure_device(struct bme280_dev* device)
{
	device->read = BME_I2C_Reg_Read;
	device->write = BME_I2C_Reg_Write;

	// typedef void (*bme280_delay_us_fptr_t)(uint32_t period, void *intf_ptr);
	// bme280_delay_us_fptr_t delay_us;
	// HAL_Delay for now?
	//	device->delay_us = BME_DELAY;
}

int bme_init()
{
	int8_t result;

	result = bme280_init(&g_device);

	return (int) result;
}

struct bme280_dev* get_bme280_device()
{
	return &g_device;
}

// TODO Does these I2C functions belong here? Or is there usage out somewhere else for these? Tho they are implemented just for BME280 drivers.

static int8_t BME_I2C_Reg_Read(uint8_t reg_addr, uint8_t *reg_data,
		uint32_t len, void *intf_ptr)
{
	uint16_t device_addr;
	device_addr = ((*(uint16_t*) g_device.intf_ptr) << 1);

	if (HAL_I2C_Mem_Read(&hi2c1, (uint8_t) device_addr, (uint8_t) reg_addr, 1,
			reg_data, len, 500) == HAL_OK)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

static int8_t BME_I2C_Reg_Write(uint8_t reg_addr, const uint8_t *reg_data,
		uint32_t len, void *intf_ptr)
{
	uint16_t device_addr = ((*(uint16_t*) g_device.intf_ptr) << 1);

	if (HAL_I2C_Mem_Write(&hi2c1, device_addr, reg_addr, 1, (uint8_t*) reg_data,
			len, 500) == HAL_OK)
	{
		return 0;
	}
	else
	{
		return -1;
	}
}

