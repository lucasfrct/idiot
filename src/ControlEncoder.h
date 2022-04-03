#include "Arduino.h"
#include <map>
#include <string>

class ControlEncoder
{
    public:
       ControlEncoder(int clk, int dt, int sw);
       int run();
       bool event(bool event);
       bool change(void (*func)(std::map<String, String>));
       bool pressSW();
       bool press();
       bool hold();
       int value();
       int abs();
       int percent();
       int step(int step);
       String sense();
       String debug();

    private:
        int _clk;
        int _dt;
        int _sw;

        int _counter = 0;
        int _step = 1;

        int _stateClk; 
        int _lastStateClk;

        int _stateDt;

        int _stateSw;
        unsigned long _currentTimeSw;
        unsigned long _lastTimeSw;
        int _bounceSw = 50;
        bool _press = false;

        bool _hold = false;
        int _holdTime = 80;

        String _senses[2] = {"CCW", "CW"}; // "CCW" = anti horário, "CW" = horário
        String _currentSense = "CW";

        bool _transition = false;
       
};