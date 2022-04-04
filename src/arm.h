#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

class Arm 
{
    public:
        Arm();
        void run();
        int base(String sense);


    private:
        Adafruit_PWMServoDriver _servos;
        uint8_t _servorShoulder;
        uint8_t _servoElbow;
        uint8_t _servoWrist;
        uint8_t _servoWristRotation;
        uint8_t _servoClamp;

        int _oscillatorFreq = 27000000;
        int _PWMFreq = 50;

        uint8_t _servoBase;
        int _servoBaseMcs = 1370;
        bool _holdBase = false;
        unsigned long _targetTimeBase = 0;
        int _angle = 0;


};