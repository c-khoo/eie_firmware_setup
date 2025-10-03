/*
 * main.c
 */

#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

#define LED0_NODE DT_ALIAS(led0)
#define LED1_NODE DT_ALIAS(led1)
#define LED2_NODE DT_ALIAS(led2)
#define LED3_NODE DT_ALIAS(led3)

static const struct gpio_dt_spec led0 = GPIO_DT_SPEC_GET(LED0_NODE, gpios);
static const struct gpio_dt_spec led1 = GPIO_DT_SPEC_GET(LED1_NODE, gpios);
static const struct gpio_dt_spec led2 = GPIO_DT_SPEC_GET(LED2_NODE, gpios);
static const struct gpio_dt_spec led3 = GPIO_DT_SPEC_GET(LED3_NODE, gpios);

int main(void) {
    int ret0, ret1, ret2, ret3;

    if (!gpio_is_ready_dt(&led0) || !gpio_is_ready_dt(&led1) || !gpio_is_ready_dt(&led2) || !gpio_is_ready_dt(&led3)) {
        return -1;
    }

    ret0 = gpio_pin_configure_dt(&led0, GPIO_OUTPUT_ACTIVE);
    ret1 = gpio_pin_configure_dt(&led1, GPIO_OUTPUT_ACTIVE);
    ret2 = gpio_pin_configure_dt(&led2, GPIO_OUTPUT_ACTIVE);
    ret3 = gpio_pin_configure_dt(&led3, GPIO_OUTPUT_ACTIVE);
    if (ret0 < 0) {
        return ret0;
    } else if (ret1 < 0) {
        return ret1;
    } else if (ret2 < 0) {
        return ret2;
    } else if (ret3 < 0) {
        return ret3;
    }

    int toggle = 1;

    while (1) {
        toggle = !toggle;
        
        gpio_pin_toggle_dt(&led0);
        
        if (toggle) {
            gpio_pin_toggle_dt(&led1);
            gpio_pin_toggle_dt(&led2);
            gpio_pin_toggle_dt(&led3);
        }

        k_msleep(500);
    }

    return 0;

}