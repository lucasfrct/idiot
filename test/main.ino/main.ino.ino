#include <Arduino.h>

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define PWM_FREQ 50; //

const int CLK   = D5; //
const int DT    = D6; //
const int SW    = D7; // butun press

const int PCA9685       = D8;   //  
const int DISABLE       = HIGH; // on/off pca9685
const int RESOLUTION    = 4096; // 12bits

// Rotary Encoder variables
int counter = 0;
int currentStateCLK;
int lastStateCLK;
String currentDir ="";
unsigned long lastButtonPress = 0;
int btnState = LOW;
 
// https://naylampmechatronics.com/blog/41_tutorial-modulo-controlador-de-servos-pca9685-con-arduino.html
Adafruit_PWMServoDriver servos  = Adafruit_PWMServoDriver(0x40);

const uint8_t SERVO_BASE            = 0;    // servo da base
const uint8_t SERVO_SHOULDER        = 1;    // servo do ombro
const uint8_t SERVO_ELBOW           = 2;    // servo do cotovelo
const uint8_t SERVO_WRIST           = 3;    // servo do punho
const uint8_t SERVO_WRIST_ROTATION  = 4;    // servod da rotacao do punho
const uint8_t SERVO_CLAMP           = 5;    // pinça        

// calibragem da posição 0°
unsigned int THRESHOLD_MIN[16] = {300, 172, 172, 246, 246, 172, 246, 200, 200, 150, 160, 172, 172, 172, 200, 246};

// calibragem da posição maxima 180°/360°
unsigned int THRESHOLD_MAX[16] = {350, 256, 256, 492, 492, 565, 492, 550, 550, 600, 590, 565, 565, 565, 550, 492};         

// numero de revolução
unsigned int REVOLUTIONS[16] = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };

void setup() {
    Serial.begin(9600);
    
    Serial.println("16 channel PWM - PCA9685");

    pinMode(CLK, INPUT);
    pinMode(DT, INPUT);
    pinMode(SW, INPUT_PULLUP);

    pinMode(PCA9685, OUTPUT);

    servos.begin();
    servos.setPWMFreq(50);

    digitalWrite(PCA9685, !DISABLE);
    
    // Read the initial state of CLK
    lastStateCLK = digitalRead(CLK);
}

// setServoPulse(0, 0.001) is a ~1 millisecond pulse width!
void setServoPulse(uint8_t servo, double pulse) {
    
    double pulselength;
    
    pulselength = 1000000;   // 1,000,000 us per second
    pulselength /= PWM_FREQ; 
    
    double pulse_per_period = pulselength;
    
    pulselength /= RESOLUTION;  // 12 bits of resolution
    
    double pulse_per_bit = pulselength;

    pulse *= 1000000;  // convert input seconds to us
    pulse /= pulselength;
    servos.setPWM(servo, 0, pulse);

    Serial.print(pulse_per_period); Serial.println(" us per period"); 
    Serial.print(pulse_per_bit);    Serial.println(" us per bit"); 
    Serial.print(pulse);            Serial.println(" pulse servo");
}

void setServo(uint8_t servo, int angle) { 
    setServoPulse(0, 1500);
}

void DriverExecAll(Adafruit_PWMServoDriver servos) {
    for (uint16_t i = 0; i < 4096; i += 8) {
        for (uint8_t pwmnum = 0; pwmnum < 16; pwmnum++) {
            servos.setPWM(pwmnum, 0, (i + (4096/16 ) * pwmnum) % 4096 );
        };
    };
};

int DriveBase(int angle) {
    setServo(0, angle);
    return angle;
}

int RotaryEncoder() {
    // Read the current state of CLK
    currentStateCLK = digitalRead(CLK);

    // If last and current state of CLK are different, then pulse occurred
    // React to only 1 state change to avoid double count
    if (currentStateCLK != lastStateCLK  && currentStateCLK == 1){

        // If the DT state is different than the CLK state then
        // the encoder is rotating CCW so decrement
        if (digitalRead(DT) != currentStateCLK) {
            counter --;
            currentDir ="CCW";
        } else {
            // Encoder is rotating CW so increment
            counter ++;
            currentDir ="CW";
        };

        Serial.print("Direction: ");    Serial.println(currentDir);
        Serial.print("Counter: ");      Serial.println(counter);
    };

    // Remember last CLK state
    lastStateCLK = currentStateCLK;

    // Read the button state
    btnState = digitalRead(SW);

    //If we detect LOW signal, button is pressed
    if (btnState == LOW) {
        //if 50ms have passed since last LOW pulse, it means that the
        //button has been pressed, released and pressed again
        if (millis() - lastButtonPress > 50) {
            Serial.println("Button pressed!");
        };

        // Remember last button press event
        lastButtonPress = millis();
    };

    delay(1);
    
    return currentStateCLK;
}

void loop() {
    RotaryEncoder();
    // delay(1000);
    // DriveBase(0);
    // delay(1000);
    // DriveBase(180);
};
