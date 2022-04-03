#include "Arduino.h"
#include <stdlib.h> 
#include <map>

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

/**
 * @brief Captura o valor do encoder
 */ 
int ControlEncoder::run() 
{
    // Captura o sinal da porta digital
    _stateClk = digitalRead(_clk);

    // faz reset no evento para false
    this->event(false);

    // verifica se o sinal do encoder mudou
    if(_stateClk != _lastStateClk) {

        this->event(true);
        
        // captura o sinal da porta digital
        _stateDt = digitalRead(_dt);

        // verifica se o houve rotação e para qual sentido
        if (_stateDt != _stateClk) { 
            _counter = _counter + _step;
            _currentSense = _senses[1];
        } else { 
            _currentSense = _senses[0];
            _counter = _counter - _step;
        };
    };

    _lastStateClk = _stateClk;

    // verifica se o encoder está em hold
    this->pressSW();

    return _counter;
}

/**
 * @brief Verifica se o houve uma evento no encoder
 */
bool ControlEncoder::event(bool event) 
{
    _transition = event;
    return _transition;
}

/** 
 * notifica as mudancas no encoder
*/
bool ControlEncoder::change(void (*func)(std::map<String, String>))
{
    std::map<String, String> notify;
    notify["value"] = String(_counter);
    notify["sense"] = _currentSense;
    notify["hold"] = String(_hold);
    notify["press"] = String(_press);

    if(_transition) { func(notify); }

    return _transition;
}

/**
 * @brief Verifica se o SW do encoder foi pressionado
 */
bool ControlEncoder::pressSW() 
{
    _stateSw = digitalRead(_sw);
    _press = false; 

    if(_stateSw == LOW){
        _currentTimeSw = millis();
        if (_currentTimeSw - _lastTimeSw > _bounceSw) { 
            _press = true; 
            this->event(true);
        };
        _lastTimeSw = millis(); 
    };

    // inicia uma evento hold
    if(!_hold && _press) {
        _hold = true;
    }

    // seguro o hold por 50 ms (_holdTime)
    if(_hold && millis() - _lastTimeSw > _holdTime) {
        _hold = false; 
    }

    return _press;
}

/** 
 * retorna o estado atual do hold
*/
bool ControlEncoder::press()
{
    return _press;
}

/**
 * @brief Verifica se o encoder está em hold
 */
bool ControlEncoder::hold() 
{
    return _hold;
}

/** 
 * retorna o valor 
*/
int ControlEncoder::value() 
{
    return _counter;
}

/**
 * @brief Retorna o valor absoluto do encoder
 */
int ControlEncoder::abs() 
{   
    return std::abs(_counter);
}

/**
 * @brief Retorna o valor percentual do encoder
 */
int ControlEncoder::percent() 
{   
    if (_counter >= 100) {  _counter = 100; };
    if (_counter <= 0) {    _counter = 0;   };
    return _counter;
}

/**
 * @brief Retorna o valor de passo do encoder
 */
int ControlEncoder::step(int step) 
{   
    _step = step;
    return _counter;
}

/**
 * @brief Retorna o sentido do encoder
 */
String ControlEncoder::sense() 
{   
    return _currentSense;
}

/**
 * @brief Debug do encoder
 */
String ControlEncoder::debug() 
{
    if(_transition) {
        Serial.print("Contador: "); Serial.print(_counter);
        Serial.print(" | sertido: "); Serial.println(_currentSense);
        Serial.print("Hold: "); Serial.println(_hold);
    }; 

    return "";
}