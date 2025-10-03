/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)
#define NUM_LEDS 4
#define BLINK_SPD_MS 150

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

int main(void) {
    struct gpio_dt_spec leds[] = {led0, led1, led3, led2};
    int ret;

    for (int i = 0; i < NUM_LEDS; i++) {
        if (!gpio_is_ready_dt(&leds[i])) {
            return -1;
        }

        ret = gpio_pin_configure_dt(&leds[i], GPIO_OUTPUT_INACTIVE);
        if (ret < 0) {
            return ret;
        }
    }

    while (1) {
        
        for (int i = 0; i < 4; i++) {
            gpio_pin_toggle_dt(&leds[i]);
            k_msleep(BLINK_SPD_MS);
            gpio_pin_toggle_dt(&leds[i]);
            k_msleep(BLINK_SPD_MS);
        }

    }

    return 0;

}