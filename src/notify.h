
#ifndef notify_led
#define notify_led

#include "Arduino.h"

class Notify
{
    public:
        notify(int pin);
        void run();
        void blink(int ms);
        void event(int ms);

    private:
        int _pin;
        int _blink_ms;
        unsigned long _blink_currentTime;
        long _blink_deferTime = 0;
        int _event_ms;
        unsigned long _event_currentTime;
        long _event_targetTime = 0;
        bool _event_state = false;
};

#endif