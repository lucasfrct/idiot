
#include "Arduino.h"

class Notify
{
    public:
        Notify(int pin);
        void run();
        bool event(bool transition);
        bool change(void (*func)(bool));
        bool blink(int ms);
        bool notify();

    private:
        int _pin;
        
        bool _transition = false;

        int _blinkMs;
        
        unsigned long _blinkCurrentTime;
        unsigned long _blinkDeferTime = 0;

        uint8_t _blinkDeferState;
        uint8_t _blinkCurrentState;

        unsigned long _notifyCurrentTime;
        unsigned long _notifyDeferTime = 0;

};
