// #include "Arduino.h"
// #include <Wire.h>
// #include <Adafruit_PWMServoDriver.h>

// class Arm 
// {
//     public:
//         Arm(int PCA9685);
//         void RunPositive(int mcs);
//         void Encoder(int value);
//         // void RunNegative();
//         // void ServoPulse(uint8_t servo, double pulse);
//         // void DriverExecAll();
//     private:
//         int _PWM_FREQ   = 50;
//         int _RESOLUTION = 4096;
//         int _DISABLE = HIGH;
//         int _PCA9685;

//         Adafruit_PWMServoDriver _servos;
//         uint8_t _SERVO_BASE;
//         uint8_t _SERVO_SHOULDER;
//         uint8_t _SERVO_ELBOW;
//         uint8_t _SERVO_WRIST;
//         uint8_t _SERVO_WRIST_ROTATION;
//         uint8_t _SERVO_CLAMP;
//         int _encoder;

// };