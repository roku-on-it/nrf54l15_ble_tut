#include <stdio.h>

#include "leds.h"
#include <zephyr/logging/log.h>
#include <zephyr/kernel.h>

LOG_MODULE_REGISTER(configure_leds, LOG_LEVEL_DBG);

void configure_leds(const struct gpio_dt_spec led_arr[], size_t len) {
  int ret;

  for (size_t i = 0; i < len; i++) {
    const struct gpio_dt_spec led = led_arr[i];

    if (!gpio_is_ready_dt(&led)) {
      LOG_ERR("Failed to get led %d ready", i);
    }

    ret = gpio_pin_configure_dt(&led, GPIO_OUTPUT);
    if (ret < 0) {
      LOG_ERR("Failed to configure led %d", i);
    } else {
      LOG_DBG("Configured led %d", i);
    }
  }
}

void cycle_leds(const struct gpio_dt_spec led_arr[], size_t len) {

  for (size_t i = 0; i < len; i++) {
    const struct gpio_dt_spec led = led_arr[i];

    gpio_pin_set_dt(&led, 1);
    k_msleep(CYCLE_SLEEP_MS);
    gpio_pin_set_dt(&led, 0);
    k_msleep(CYCLE_SLEEP_MS);
  }
}