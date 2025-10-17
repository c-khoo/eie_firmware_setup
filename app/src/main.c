/*
 * main.c
 */

#include <zephyr/kernel.h>

#include "BTN.h"
#include "LED.h"

#define SLEEP_MS 1

int main(void) {
  
  if (0 > BTN_init()) {
    return 0;
  }
  if (0 > LED_init()) {
    return 0;
  }

  int count = 0;
  while(1) {
    if (BTN_check_clear_pressed(BTN0)) {
      count++;

      if (count == 16) {
        count = 0;
      }

      printk("Count is now: %d\n", count);

      if ((count >= 8 || count == 0) && (count % 8 == 0)) {
        LED_toggle(LED0);
      }

      if ((count >= 4 || count == 0) && (count % 4 == 0)) {
        LED_toggle(LED1);
      }

      if (count % 2 == 0) {
        LED_toggle(LED2);
      }

      LED_toggle(LED3);
    }
    k_msleep(SLEEP_MS);
  }
	return 0;
}
