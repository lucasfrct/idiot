#include "Arduino.h"
#include <stdlib.h> 

#include "ControlEncoder.h"

ControlEncoder::ControlEncoder(int clk, int dt, int sw)
{
    _clk = clk;
    _dt = dt;
    _sw = sw;
    
    pinMode (_clk, INPUT);
    pinMode (_dt, INPUT);
    pinMode(_sw, INPUT_PULLUP);

    _lastStateClk = digitalRead(_clk);
}

int ControlEncoder::value() 
{
    _stateClk = digitalRead(_clk);

    this->event(false);

    if(_stateClk != _lastStateClk) {

        this->event(true);

        _stateDt = digitalRead(_dt);

        if (_stateDt != _stateClk) { 
            _counter = _counter + _step;
            _currentSense = _senses[1];
        } else { 
            _currentSense = _senses[0];
            _counter = _counter - _step;
        };
    };

    _lastStateClk = _stateClk;

    this->hold();

    return _counter;
}

bool ControlEncoder::hold() 
{
    _stateSw = digitalRead(_sw); 
    if(_stateSw == LOW){

        if (millis() - _lastTimeSw > 50) {
            Serial.println("Reset counter");
            _counter = 0;
        };

        _lastTimeSw = millis(); 
    };

    return _stateSw;
}

bool ControlEncoder::event(bool event) 
{
    _transition = event;
    return _transition;
}

void ControlEncoder::debug() 
{
    if(_transition) {
        Serial.print("Contador: "); Serial.print(_counter);
        Serial.print(" | sertido: "); Serial.println(_currentSense);
    }; 
}

int ControlEncoder::abs() 
{   
    this->value();

    _counter = std::abs(_counter);

    return _counter;
}

int ControlEncoder::percent() 
{   
    this->value();

    if(_counter > 99) {
        _counter = 100;
    } else if(_counter < 1) {
        _counter = 0;
    } else {
        _counter = _counter;
    }

    return _counter;
}

int ControlEncoder::step(int step) 
{   
    _step = step;
    this->value();
    return _counter;
}
