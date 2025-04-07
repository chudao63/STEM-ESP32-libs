#ifndef __HCSR04_STEM_H__
#define __HCSR04_STEM_H__

#include "Arduino.h"

class HCSR04_STEM {
private:
    int trigPin;
    int echoPin;


public:
    HCSR04_STEM(int trig, int echo); 

    void begin();
    int getDistance();
};

#endif
