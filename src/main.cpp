#include <Arduino.h>

// #include <Wire.h>
// #include <Adafruit_PWMServoDriver.h>

#include <encoder.h>
#include <arm.h>

// #define PWM_FREQ 50; //

// const int PCA9685       = D8;   //  
// const int DISABLE       = HIGH; // on/off pca9685
// const int RESOLUTION    = 4096; // 12bits

 
// https://naylampmechatronics.com/blog/41_tutorial-modulo-controlador-de-servos-pca9685-con-arduino.html
// Adafruit_PWMServoDriver servos  = Adafruit_PWMServoDriver(0x40);

// const uint8_t SERVO_BASE            = 0;    // servo da base
// const uint8_t SERVO_SHOULDER        = 1;    // servo do ombro
// const uint8_t SERVO_ELBOW           = 2;    // servo do cotovelo
// const uint8_t SERVO_WRIST           = 3;    // servo do punho
// const uint8_t SERVO_WRIST_ROTATION  = 4;    // servod da rotacao do punho
// const uint8_t SERVO_CLAMP           = 5;    // pinça        

// // calibragem da posição 0°
// unsigned int THRESHOLD_MIN[16] = {300, 172, 172, 246, 246, 172, 246, 200, 200, 150, 160, 172, 172, 172, 200, 246};

// // calibragem da posição maxima 180°/360°
// unsigned int THRESHOLD_MAX[16] = {350, 256, 256, 492, 492, 565, 492, 550, 550, 600, 590, 565, 565, 565, 550, 492};         

// // numero de revolução
// unsigned int REVOLUTIONS[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void setup() {
    Serial.begin(9600);
    
    delay(1);
    Serial.println("16 channel PWM - PCA9685");

    // pinMode(PCA9685, OUTPUT);

    // servos.begin();
    // servos.setPWMFreq(50);

    // digitalWrite(PCA9685, !DISABLE);
}

// // setServoPulse(0, 0.001) is a ~1 millisecond pulse width!
// void setServoPulse(uint8_t servo, double pulse) {
    
//     double pulselength;
    
//     pulselength = 1000000;   // 1,000,000 us per second
//     pulselength /= PWM_FREQ; 
    
//     double pulse_per_period = pulselength;
    
//     pulselength /= RESOLUTION;  // 12 bits of resolution
    
//     double pulse_per_bit = pulselength;

//     pulse *= 1000000;  // convert input seconds to us
//     pulse /= pulselength;
//     servos.setPWM(servo, 0, pulse);

//     Serial.print(pulse_per_period); Serial.println(" us per period"); 
//     Serial.print(pulse_per_bit);    Serial.println(" us per bit"); 
//     Serial.print(pulse);            Serial.println(" pulse servo");
// }

// void setServo(uint8_t servo, int angle) { 
//     setServoPulse(0, 1500);
// }

// void DriverExecAll(Adafruit_PWMServoDriver servos) {
//     for (uint16_t i = 0; i < 4096; i += 8) {
//         for (uint8_t pwmnum = 0; pwmnum < 16; pwmnum++) {
//             servos.setPWM(pwmnum, 0, (i + (4096/16 ) * pwmnum) % 4096 );
//         };
//     };
// };

Encoder en = Encoder(D5, D6, D7);
Arm arm = Arm(D8);

void loop() {
    en.sweep();
    // arm.ServoPulse(0, 0.0015);
};
