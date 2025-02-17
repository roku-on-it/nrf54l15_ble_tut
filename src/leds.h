#pragma once

#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_PATH(leds, led_0)
#define LED1_NODE DT_PATH(leds, led_1)
#define LED2_NODE DT_PATH(leds, led_2)
#define LED3_NODE DT_PATH(leds, led_3)

#define CYCLE_SLEEP_MS 20

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

void configure_leds(const struct gpio_dt_spec led_arr[], size_t len);
void cycle_leds(const struct gpio_dt_spec led_arr[], size_t len);
