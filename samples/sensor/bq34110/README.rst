.. _bq34110-sample:

BQ34110 Sensor Sample
#####################

Overview
********

This sample application retrieves all the fuel gauge parameters,
- Voltage, in volts
- Average current, in amps
- Gauge temperature
- State of charge measurement in percentage
- Full Charge Capacity in mAh
- Remaining Charge Capacity in mAh
- Average power in W
- Time to full in minutes
- Time to empty in minutes

from BQ34110 sensor and prints this information to the UART console.

Requirements
************

This sample requires a `BQ34110 Fuel Gauge`_ and :dtcompatible:`ti,bq34110`
overlay must be provided to connect the sensor to the I2C bus.

Building and Running
********************

This project outputs fuel gauge data to the console. In this example below the
:ref:`frdm_k64f` board is used.

.. zephyr-app-commands::
   :zephyr-app: samples/sensor/bq34110
   :board: frdm_k64f
   :goals: build flash

References
**********

.. target-notes::

.. _BQ34110 Fuel Gauge: https://www.ti.com/lit/ds/symlink/bq34110.pdf?ts=1611978545089
