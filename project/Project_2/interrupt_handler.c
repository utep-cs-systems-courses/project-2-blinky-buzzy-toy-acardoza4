#include <msp430.h>
#include "switches.h"
#include "buzzer.h"
#include "states.h"
#include "led.h"

/* Switch on P2 (S2) */
void __interrupt_vec(PORT2_VECTOR) Port_2() {

  if (P2IFG & SWITCHES) {      /* did a button cause this interrupt? */
    P2IFG &= ~SWITCHES;      /* clear pending sw interrupts */
    switch_interrupt_handler();/* single handler for all switches */
  }
}

void __interrupt_vec(WDT_VECTOR) WDT() {
  static char count = 0;
  static char note = 0;
  static char delay = 0;
  static char make_noise = 0;
  static char time_until_change = 0;

  if (play_song && note < 14) {

    if (++count == time_until_change) {
      
      count = 0;

      // if we're making noise then we want to stop making noise and delay
      if (make_noise) {
	make_noise = 0;
	buzzer_set_period(0);
	//long delayAmount = (long)(100/notes[note]);
	time_until_change = delay_time[delay++];
	led_state(0,1);
      }

      // if we're not making noise, then start and change the note for next time
      else {
	make_noise = 1;
	buzzer_set_period(notes[note]);
	time_until_change = note_duration[note++];
	led_state(1,0);
      }
    }
  }
  else {
    // reset song
    delay = 0;
    note = 0;
    buzzer_set_period(0);
  }

  // dim led
  if (dim_on) {
    if (++count == 10) {
      led_state(1, 0);
      count = 0;
    }
  }
}
