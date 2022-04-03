
// #include "Arduino.h"
// #include "Notify.h"

// Notify::Notify(int pin)
// {
//     _pin = pin;
//     pinMode(_pin, OUTPUT);
// };

// void Notify::run()
// {  
//     this->blink(50);
// };

// void Notify::blink(int ms) 
// {
//     _blink_ms = ms;
//     _blink_currentTime = millis();

//     if(_blink_currentTime - _blink_deferTime > _blink_ms) {
//         _blink_deferTime = _blink_currentTime;
//         digitalWrite(_pin, !digitalRead(_pin));
//     };
// };

// void Notify::event(int ms) 
// {
//     _event_ms = ms;
    
//     _event_currentTime = millis();
    
//     if(!_event_state) {
//         digitalWrite(_pin, HIGH);
//     }

//     if(_event_currentTime - _event_targetTime > _event_ms) {
//         _event_targetTime = _event_currentTime;
//         _event_state = !_event_state;
//     };

//     if(_event_state) {
//         this->run();
//     }; 
          
// };
