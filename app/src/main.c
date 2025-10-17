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

  int passkey[] = {0, 1, 2, 1, 0};
  int n = sizeof(passkey) / sizeof(passkey[0]);

  int i = 0;
  int locked = 1;
  LED_set(LED0, LED_ON);

  while(1) {
    int user_entered[n];

    while(locked) {
      if (BTN_check_clear_pressed(BTN0)) {
        if (i < n) {
          user_entered[i] = 0;
        }
        i++;
      }

      if (BTN_check_clear_pressed(BTN1)) {
        if (i < n) {
          user_entered[i] = 1;
        }
        i++;
      }

      if (BTN_check_clear_pressed(BTN2)) {
        if (i < n) {
          user_entered[i] = 2;
        }
        i++;
      }

      if (BTN_check_clear_pressed(BTN3)) {
        int valid = 1;
        for (int j = 0; j < n; j++) {
          if (passkey[j] != user_entered[j]) {
            valid = 0;
          }
        }

        if (valid && i == n) {
          printk("Correct!\n");
        } else {
          printk("Incorrect!\n");
        }

        locked = 0;
        LED_set(LED0, LED_OFF);
      }
      k_msleep(SLEEP_MS);
    }

    if (BTN_check_clear_pressed(BTN0) || BTN_check_clear_pressed(BTN1) || BTN_check_clear_pressed(BTN2) || BTN_check_clear_pressed(BTN3)) {
      locked = 1;
      i = 0;
      LED_set(LED0, LED_ON);
    }

    k_msleep(SLEEP_MS);
  }
	return 0;
}
