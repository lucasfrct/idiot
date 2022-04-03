#ifndef ControlEncoder_n
#define ControlEncoder_n

#include "Arduino.h"


class ControlEncoder
{
    public:
       ControlEncoder(int clk, int dt, int sw);
       int value();
       bool hold();
       bool event(bool event);
       void debug();
       int abs();
       int percent();
       int step(int step);

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
        unsigned long _lastTimeSw;

        String _senses[2] = {"CCW", "CW"}; // "CCW" = anti horário, "CW" = horário
        String _currentSense = "CW";

        bool _transition = false;
       
};

#endif