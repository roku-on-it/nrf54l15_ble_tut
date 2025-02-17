#include "leds.h"
#include <zephyr/device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(main, LOG_LEVEL_DBG);

#define STACKSIZE KB(1)

void leds_thread(void *led_arr, void *p2, void *p3) {
  LOG_INF("Starting LED control thread");
  configure_leds((const struct gpio_dt_spec *)led_arr, 4);

  while (1) {
    cycle_leds(led_arr, 4);
    cycle_leds(led_arr, 4);
    cycle_leds(led_arr, 4);

    k_msleep(700);
  }
}

K_THREAD_STACK_DEFINE(led_thread_stack, STACKSIZE);
static struct k_thread led_thread_data;

int main(void) {
  const struct gpio_dt_spec led_arr[] = {led0, led1, led3, led2};

  k_tid_t led_tid =
      k_thread_create(&led_thread_data, led_thread_stack, STACKSIZE,
                      leds_thread, (void *)led_arr, NULL, NULL,
                      K_LOWEST_APPLICATION_THREAD_PRIO, 0, K_NO_WAIT);

  LOG_INF("LED thread started with tid %p", (void *)led_tid);

  // Optionally we can while(1) {}
  k_sleep(K_FOREVER);

  return 0;
}