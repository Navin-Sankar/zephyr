/*
 * Copyright (c) 2020 Linumiz
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#define DT_DRV_COMPAT ti_bq34110

#include <device.h>
#include <drivers/i2c.h>
#include <kernel.h>
#include <logging/log.h>
#include <drivers/sensor.h>
#include "bq34110.h"

LOG_MODULE_DECLARE(BQ34110, CONFIG_SENSOR_LOG_LEVEL);

int bq34110_init_interrupt(const struct device *dev)
{
	struct bq34110_data *data = dev->data; 
	const struct bq34110_config *cfg = dev->config;

	data->dev = dev;

	/* setup alert1 gpio interrupt */
	data->alert_dev = device_get_binding(cfg->alert_controller);
	if (data->alert_dev == NULL) {
		LOG_ERR("Cannot get pointer to %s device.",
			cfg->alert_controller);
		return -EINVAL;
	}

	gpio_pin_configure(data->alert_dev, cfg->alert_pin,
			   GPIO_INPUT | cfg->alert_flags);

	gpio_init_callback(&data->alert_cb, bq34110_alert_callback,
			   BIT(cfg->alert_pin));

	if (gpio_add_callback(data->alert_dev, &data->alert_cb) < 0) {
		LOG_ERR("Could not set gpio callback");
		return -EIO;
	}

#if defined(CONFIG_BQ34110_TRIGGER_OWN_THREAD)
	k_sem_init
}
