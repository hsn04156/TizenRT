/* ****************************************************************
 *
 * Copyright 2018 Samsung Electronics All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 ******************************************************************/

#include <tinyara/config.h>
#include <stdio.h>
#include <tinyara/gpio.h>
#include <iotbus/iotbus_gpio.h>

#if !defined(CONFIG_EXAMPLES_IOTBUS_TEST_RED_LED_GPIO_NUM)
#error To run this sample, input GPIO numbers on menuconfig.
#endif

#define LED_POWER_PORT CONFIG_EXAMPLES_IOTBUS_TEST_RED_LED_GPIO_NUM

const char *get_led_power(void);
int set_led_power(char *value);
int blink_start(void);
int blink_end(void);
void blink_init(void);