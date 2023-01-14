#line 1 "c:\\Users\\sm-pc\\Desktop\\solux_arduino\\ultrasonic.h"
#ifndef ULTRASONIC_H
#define ULTRASONIC_H

#include "Arduino.h"

class Ultrasonic {
public: 
    Ultrasonic(int trig, int echo);
    void setup(); 
    int readDistance();
private:
    int trig, echo; 
};

#endif