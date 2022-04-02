

#include "Arduino.h"
#include "notify.h"


notify::notify(int pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
}

void notify::run(int ms)
{
    digitalWrite(_pin, HIGH);
    delay(ms);
    digitalWrite(_pin, LOW);
    delay(ms);
}
