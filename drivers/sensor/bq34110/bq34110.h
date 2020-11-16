/*
 * Copyright (c) 2020 Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef ZEPHYR_DRIVERS_SENSOR_BATTERY_BQ34110_H_
#define ZEPHYR_DRIVERS_SENSOR_BATTERY_BQ34110_H_

#include <device.h>
#include <sys/util.h>
#include <logging/log.h>
#include <drivers/gpio.h>
LOG_MODULE_REGISTER(bq34110, CONFIG_SENSOR_LOG_LEVEL);

/* Control Subcommands */
#define CONTROL_STATUS			0x0000
#define SUB_DEVICE_TYPE			0x0001
#define BOARD_OFFSET			0x0009
#define PIN_VEN_SET			0x006C
#define PIN_VEN_RESET			0x006D
#define PIN_LEN_SET			0x006E
#define PIN_LEN_RESET			0x006F
#define CAL_TOOGLE			0x002D
#define MANUFACTURING_STATUS		0x0057

/* Commands */
#define CONTROL				0x00
#define VOLTAGE				0x08
#define CURRENT				0x14
#define REMAINING_CHARGE_CAPACITY	0x10
#define FULL_CHARGE_CAPACITY		0x12
#define TIME_TO_EMPTY			0x16
#define TIME_TO_FULL			0x18
#define AVERAGE_POWER			0x24
#define INTERNAL_TEMPERATURE		0x28
#define RELATIVE_STATE_OF_CHARGE	0x2C
#define STATE_OF_HEALTH			0x2E
#define MANUFACTURER_ACCESS_CONTROL	0x3E
#define MAC_DATA			0x40
#define MAC_DATA_SUM			0x60
#define RAW_VOLTAGE			0x7C
#define ANALOG_COUNT			0x79
#define RAW_CURRENT			0x7A
#define RAW_INT_TEMP			0x7E

/* Calibration */
#define CC_GAIN				0x4000
#define INT_TEMP_OFFSET			0x400D
#define PACK_V_OFFSET			0x400F
#define EXT_COEFF_3			0x41D1
#define CC_OFFSET			0x4008

/* Device ID */
#define BQ34110_DEVICE_ID		0x0110

/* GaugeCommands */
#define DESIGN_CAPACITY_MAH		0x41F5
#define DESIGN_VOLTAGE			0x41F9

/* Charger Control */
#define TAPER_CURRENT			0x411C
#define TAPER_VOLTAGE			0x4120

/* Configuration Commands */
#define OPERATION_CONFIG_A		0x413A

struct bq34110_data {
	const struct device *i2c;
	uint16_t voltage;
	int16_t avg_power;
	int16_t avg_current;
	uint16_t time_to_full;
	uint16_t time_to_empty;
	int16_t state_of_health;
	uint16_t state_of_charge;
	int16_t max_load_current;
	uint16_t nom_avail_capacity;
	uint16_t full_avail_capacity;
	uint16_t internal_temperature;
	uint16_t full_charge_capacity;
	uint16_t remaining_charge_capacity;

#ifdef CONFIG_BQ34110_TRIGGER
	const struct device *alert_dev;
	struct gpio_callback alert_cb;

	struct sensor_trigger alert_trigger;
	sensor_trigger_handler_t alert_handler;

#if defined(CONFIG_BQ34110_TRIGGER_OWN_THREAD)
	K_KERNEL_STACK_MEMBER(thread_stack, CONFIG_BQ34110_THREAD_STACK_SIZE);
	struct k_thread thread;
	struct k_sem alert_sem;
#elif defined(CONFIG_BQ34110_TRIGGER_GLOBAL_THREAD)
	struct k_work work;
#endif

#endif /* CONFIG_BQ34110_TRIGGER */
};

struct rawDataAvg {
	int16_t raw_current_avg;
	uint16_t raw_voltage_avg;
	uint16_t raw_temperature_avg;
};

struct bq34110_config {
	char *bus_name;
	uint16_t taper_current;
	uint16_t design_voltage;
	int16_t design_capacity;
	uint16_t taper_voltage;
	uint8_t no_of_series_cells;
#if CONFIG_BQ34110_TRIGGER
	gpio_pin_t alert_pin;
	gpio_flags_t alert_flags;
	const char *alert_controller;
#endif
};

#ifdef CONFIG_BQ34110_TRIGGER
int bq34110_trigger_set(const struct device *dev,
			const struct sensor_trigger *trig,
			sensor_trigger_handler_t handler);
#endif

#endif
