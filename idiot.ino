#include <map>

#include "src/ControlEncoder.h"
 
ControlEncoder en(D5, D6, D7);

 void setup() {
   Serial.begin (9600);
 } 

 void event(std::map<String, String> notify) {

    Serial.print("sentido: ");    Serial.print(notify["sense"]);
    Serial.print(" | ");          Serial.print(en.sense());
    Serial.print(" | value: ");   Serial.print(notify["value"]);
    Serial.print(" | hold: ");    Serial.print(notify["hold"]);
    Serial.print(" | press: ");    Serial.print(en.press());
    Serial.print(" | absolute: "); Serial.print(en.abs());
    Serial.print(" | percent: "); Serial.print(en.percent());
    Serial.print(" | step: "); Serial.print(en.step(5));    
    Serial.println("");
 }

 void loop() {
  en.run();
  
  en.change(&event);
//  en.debug();
 
 }
