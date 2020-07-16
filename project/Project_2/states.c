#include <msp430.h>
#include <stdlib.h>
#include "states.h"
#include "led.h"

void reset_state() {
  red_on = 0;
  green_on = 0;
  led_update();
}

void led_state(unsigned char g, unsigned char r) {
  green_on = g;
  red_on = r;
  led_changed = 1;
  led_update();
}
void delay(unsigned int a)
{
  unsigned int i;
  for(i = a; i > 0; i--)
    __delay_cycles(1);
}

void dim(){

  while (dim_on) {

    unsigned int i;
    
    for (i = 1; i < 1200; i++) {
      led_state(1,0);
      delay(i);
      led_state(0,1);
      delay(1200-i);
    }

    for (i = 1200; i > 1; i--) {
      led_state(1,0);
      delay(i);
      led_state(0,1);
      delay(1200-i);
    }
  }
}
