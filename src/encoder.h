#include "Arduino.h"

class Encoder 
{
    public:
        Encoder(int clk, int dt, int sw);      
        
        boolean btnHold();
        boolean btnPress();
        boolean btnDown();
        boolean btnUp();
        
        String direction();
        String directionToggle();

        void mode(String mode);

        int start(int start);
        int end(int end);

        int percent();
        int angle();
        int pulde();

        int abs();

        int value();
        int sweep();  

        void event(boolean transition);
        void debug();

    private:
        int _clk;
        int _dt;
        int _sw;

        boolean _trasition = false;

        int _counterStart   = 0;
        int _counterEnd     = 100;
        int _counter        = 0;

        int _btnState   = LOW;
        unsigned long _btnLastPress = 0;
        
        int _clkStateCurrent;
        int _clkStateLast;
        
        String _directionCurrent = "";
        boolean _directionToggle = false;
        String _directions[2] = { "CCW", "CW" };
};
