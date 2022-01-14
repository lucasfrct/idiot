#include "Servo.h"
#include <Arduino.h>

int servo_pin = D7;  // for ESP8266 microcontroller
int angle = 0; 
Servo myservo;

void setup() {
    Serial.begin(9600);
    Serial.println("Micro-servo test!");
    myservo.attach(servo_pin);
}


void loop() {

    for (angle = 0; angle <= 180; angle += 1) { 
        myservo.write(angle);
        delay(15);
    };

    for (angle = 180; angle >= 0; angle -= 1) {
        myservo.write(angle);
        delay(15);
    };
    
};