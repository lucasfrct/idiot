 #include "src/ControlEncoder.h"
 
ControlEncoder en(D5, D6, D7);

 void setup() {
   Serial.begin (9600);
 } 

 void loop() {

  en.step(5);
  en.debug();
 
 }
