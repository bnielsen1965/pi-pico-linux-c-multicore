#include "pico/stdlib.h"
#include "pico/multicore.h"

#define LED_PIN 25
#define LED2_PIN 15


// function to continuously blink LED2
void blink2 () {
  while (true) {
    gpio_put(LED2_PIN, 0);
    sleep_ms(200);
    gpio_put(LED2_PIN, 1);
    sleep_ms(200);
  }
}


// main runs on core0
int main() {
  gpio_init(LED_PIN);
  gpio_set_dir(LED_PIN, GPIO_OUT);
  gpio_init(LED2_PIN);
  gpio_set_dir(LED2_PIN, GPIO_OUT);

  // execute the blink2 function on core1
  multicore_launch_core1(blink2);

  // loop to continuously blink LED
  while (true) {
    gpio_put(LED_PIN, 1);
    sleep_ms(2000);
    gpio_put(LED_PIN, 0);
    sleep_ms(2000);
  }
}