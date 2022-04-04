#include "Arduino.h"
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "Arm.h"


// Ângulos entre 180 e 110 graus executam movimentos com diferentes velocidades no sentido horário.
// Ângulos entre 0 e 70 graus executam movimentos com diferentes velocidades no sentido anti-horário.
// O ângulo de 90 graus determina um momento de parada para o Servo Motor.
// O delay determina quanto tempo o motor irá ficar acionado.
// https://naylampmechatronics.com/blog/41_tutorial-modulo-controlador-de-servos-pca9685-con-arduino.html

Arm::Arm() {
    _servos  = Adafruit_PWMServoDriver(0x40);

    _servoBase          = 0;    // servo da base
    _servorShoulder     = 1;    // servo do ombro
    _servoElbow         = 2;    // servo do cotovelo
    _servoWrist         = 3;    // servo do punho
    _servoWristRotation = 4;    // servod da rotacao do punho
    _servoClamp         = 5;    // pinça   

    delay(1);

    _servos.begin();
    _servos.setOscillatorFrequency(_oscillatorFreq);
    _servos.setPWMFreq(_PWMFreq);

};

// gera um sinal de rotacao positivo
// CW (sentido horatio): 350 - 1350 | 700;
// respouso: 1350 - 1390 | 1370;
// CCW (sentido anti-horario): 1340 - 2350 | 2000;
// 1400 = repouso
void Arm::run()
{
    if(_holdBase) {
        unsigned long currentBase = millis();
        if(currentBase >  _targetTimeBase) {
            Serial.print("Base paused: ");    Serial.println(_servoBaseMcs);
            _holdBase = false;
            _servoBaseMcs = 1350;
        }
    }

    _servos.writeMicroseconds(_servoBase, _servoBaseMcs);
}

//
int Arm::base(String sense) {

    _servoBaseMcs = 1370;
    _holdBase = true;
    _targetTimeBase = (millis() + 60);	

    if(sense == "CW") {   _servoBaseMcs = 700; } 
    if(sense == "CCW") {  _servoBaseMcs = 2000; }

    return _servoBaseMcs;
}
