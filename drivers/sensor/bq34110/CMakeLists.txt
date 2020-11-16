# Copyright (c) 2020 Linumiz
#
# SPDX-License-Identifier: Apache-2.0

zephyr_library()

zephyr_library_sources_ifdef(CONFIG_BQ34110 bq34110.c)
zephyr_library_sources_ifdef(CONFIG_BQ34110_TRIGGER bq34110_trigger.c)
