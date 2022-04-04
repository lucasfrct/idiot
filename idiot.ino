#include <map>

#include "src/ControlEncoder.h"
#include "src/Notify.h"
#include "src/Arm.h"
 
ControlEncoder en(D5, D6, D7);
Notify led(LED_BUILTIN);
Arm arm;

int microsec = 0;

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

 void eventLed(std::map<String, String> notify) {
    bool state = led.notify();
    Serial.print("LED: ");    Serial.print(state);  
    Serial.println("");
 }

  void eventArm(std::map<String, String> notify) {
    led.notify();
    microsec = arm.base(en.sense());
    Serial.print("Arm base init: ");    Serial.print(microsec); 
    Serial.print(" | Sentido: "); Serial.print(en.sense()); 
    Serial.println("");
 }



 void loop() {
  en.run();
  led.run();
  arm.run();
  
//  en.change(&event);
//  en.change(&eventLed);
  en.change(&eventArm);


 
 }
