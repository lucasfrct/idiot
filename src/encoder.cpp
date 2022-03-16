#include "Arduino.h"
#include "encoder.h"

Encoder::Encoder(int clk, int dt, int sw)
{

    pinMode(clk, INPUT);
    pinMode(dt, INPUT);
    pinMode(sw, INPUT_PULLUP);

    _clk = clk;
    _dt = dt;
    _sw = sw;

    _clkStateLast = digitalRead(_clk);

    this->directionToggle();
}

int Encoder::value()
{

    _clkStateCurrent = digitalRead(_clk);

    if (_clkStateCurrent != _clkStateLast && _clkStateCurrent == 1)
    {
        this->event(true);

        // the encoder is rotating CCW so decrement
        if (digitalRead(_dt) != _clkStateCurrent)
        {
            (!_directionToggle) ? _counter-- : _counter++;
            _directionCurrent = (!_directionToggle) ? _directions[0] : _directions[1];
        }
        else
        {
            // Encoder is rotating CW so increment
            (_directionToggle) ? _counter-- : _counter++;
            _directionCurrent = (_directionToggle) ? _directions[0] : _directions[1];
        };
    };

    this->event(false);

    // Remember last CLK state
    _clkStateLast = _clkStateCurrent;

    delay(1);

    return _clkStateCurrent;
}

String Encoder::directionToggle()
{
    _directionToggle = !_directionToggle;
    return _directionCurrent;
}

int Encoder::sweep()
{

    this->value();

    _btnState = digitalRead(_sw);

    if (_btnState == LOW)
    {
        if (millis() - _btnLastPress > 50)
        {
            Serial.println("Button pressed!");
        };

        _btnLastPress = millis();
    };

    this->debug();

    return _clkStateCurrent;
}

void Encoder::event(boolean transition)
{
    _trasition = transition;
    this->debug();
}

void Encoder::debug()
{

    if (_trasition)
    {

        Serial.print("Button state: ");
        Serial.print(_btnState);
        Serial.print(" | Direction: ");
        Serial.print(_directionCurrent);
        Serial.print(" | Counter: ");
        Serial.println(_counter);
    };
}