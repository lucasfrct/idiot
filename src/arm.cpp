#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "arm.h"


Arm::Arm(int PCA9685) {
    _PCA9685 = PCA9685;

    // https://naylampmechatronics.com/blog/41_tutorial-modulo-controlador-de-servos-pca9685-con-arduino.html
    _servos  = Adafruit_PWMServoDriver(0x40);

    _SERVO_BASE            = 0;    // servo da base
    _SERVO_SHOULDER        = 1;    // servo do ombro
    _SERVO_ELBOW           = 2;    // servo do cotovelo
    _SERVO_WRIST           = 3;    // servo do punho
    _SERVO_WRIST_ROTATION  = 4;    // servod da rotacao do punho
    _SERVO_CLAMP           = 5;    // pinça   

    pinMode(_PCA9685, OUTPUT);
    digitalWrite(_PCA9685, !_DISABLE);

    _servos.begin();
    _servos.setPWMFreq(_PWM_FREQ);
};

// setServoPulse(0, 0.001) is a ~1 millisecond pulse width!
void Arm::ServoPulse(uint8_t servo, double pulse) {
    
    double pulselength;
    
    pulselength = 1000000;   // 1,000,000 us per second
    pulselength /= _PWM_FREQ; 
    
    double pulse_per_period = pulselength;
    
    pulselength /= _RESOLUTION;  // 12 bits of resolution
    
    double pulse_per_bit = pulselength;

    pulse *= 1000000;  // convert input seconds to us
    pulse /= pulselength;
    _servos.setPWM(servo, 0, pulse);

    Serial.print(pulse_per_period); Serial.println(" us per period"); 
    Serial.print(pulse_per_bit);    Serial.println(" us per bit"); 
    Serial.print(pulse);            Serial.println(" pulse servo");
    delay(1000);
};


void Arm::DriverExecAll() {
    for (uint16_t i = 0; i < 4096; i += 8) {
        for (uint8_t pwmnum = 0; pwmnum < 16; pwmnum++) {
            _servos.setPWM(pwmnum, 0, (i + (4096/16 ) * pwmnum) % 4096 );
        };
    };
};
