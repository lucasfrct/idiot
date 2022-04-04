
#include "Arduino.h"
#include "Notify.h"

Notify::Notify(int pin)
{
    _pin = pin;
    pinMode(_pin, OUTPUT);
    digitalWrite(_pin, LOW);
};

void Notify::run()
{  
    this->event(false);
};

bool Notify::event(bool transition)
{
    _transition = transition;
    return _transition;
}

bool Notify::change(void (*func)(bool))
{
    if(_transition) {
        func(bool(_blinkCurrentState));
    }
}

bool Notify::blink(int ms) 
{
    _blinkMs = ms;
    _blinkCurrentTime = millis();

    if(_blinkCurrentTime - _blinkDeferTime > _blinkMs) {

        // pegar o stado na porta
        _blinkDeferState = digitalRead(_pin);

        // inverte o estado 
        _blinkCurrentState = !_blinkDeferState;

        // atualiza o estado da porta
        digitalWrite(_pin, _blinkCurrentState);

        _blinkDeferTime = _blinkCurrentTime;

        // notifica que houve uma event
        this->event(true);
    };

    return bool(_blinkCurrentState);
};

bool Notify::notify() 
{
   return this->blink(20);
}