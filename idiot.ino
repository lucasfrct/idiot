

//#include "src/blink_new.h"
#include "src/notify.h"


//blk_n led1(LED_BUILTIN);
notify led2(LED_BUILTIN);

// the setup function runs once when you press reset or power the board
void setup() {
  //
}

// the loop function runs over and over again forever
void loop() {
//  led1.blk_led(500);
  led2.run(100);
}
