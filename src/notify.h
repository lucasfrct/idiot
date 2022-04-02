
#ifndef notify_led
#define notify_led

#include "Arduino.h"

class notify
{
    public:
        notify(int pin);
        void run(int ms);

    private:
        int _pin;
};

#endif