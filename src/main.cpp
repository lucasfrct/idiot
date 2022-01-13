// #include "Servo.h"
#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
 
// int servo_pin = D7;  // for ESP8266 microcontroller
// int angle = 0; 
// Servo myservo;

// https://naylampmechatronics.com/blog/41_tutorial-modulo-controlador-de-servos-pca9685-con-arduino.html
Adafruit_PWMServoDriver servos  = Adafruit_PWMServoDriver();
// @param n_servo: 0-15 - numero do servo
// @param up: 0-4096 (12bits) - valor para ocorrer a borda de subida 
// @param down: 0-4096 (12bits) - valor para ocorrer a borda de descida  
// servos.setPWM(n_servo, up, down);

int servo_base              = 1;    // servo da base
int servo_shoulder          = 2;    // servo do ombro
int servo_elbow             = 3;    // servo do cotovelo
int servo_wrist             = 4;    // servo do punho
int servo_wrist_rotation    = 5;    // servod da rotacao do punho
int servo_clamp             = 6;    // pinça


// Cinesiologia e biomecanica do braco
// 01 - flexao/extensao do punho
// 02 - abducao/aducao do punho
// 03 - pronacao/supnacao do punho

// 01 - flaxao/extensao do omboro

void setup() {

    // Serial.begin(9600);
    // Serial.println("16 channel PWM test!");
    
    // servos.begin();
    // servos.setPWMFreq(1600);
    
    // save I2C bitrate
    // uint8_t twbrbackup = TWBR;
    // must be changed after calling Wire.begin() (inside servos.begin())
    // TWBR = 12; // upgrade to 400KHz!

    // myservo.attach(servo_pin);
    pinMode(LED_BUILTIN, OUTPUT);
}

void loop() {

    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);

    // DriverExecAll(servos);
}

// void DriverExecAll(Adafruit_PWMServoDriver servos) {
//     for (uint16_t i = 0; i < 4096; i += 8) {
//         for (uint8_t pwmnum = 0; pwmnum < 16; pwmnum++) {
//             servos.setPWM(pwmnum, 0, (i + (4096/16 ) * pwmnum) % 4096 );
//         }
//     }
// }
