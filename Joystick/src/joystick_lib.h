#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <Arduino.h>

enum Direction {
    CENTER,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT
};

class Joystick {
private:
    uint8_t pinVRX;
    uint8_t pinVRY;
    int rawVrx;
    int rawVry;
    int vrxValue;
    int vryValue;
	bool wasPressedFlag;

    bool swState;
    bool lastSwState;
    uint8_t pinSW;
    unsigned long lastDebounceTime;
    const unsigned long debounceDelay = 50;

public:
    Joystick(uint8_t vrxPin = 34, uint8_t vryPin = 39);

    void begin(uint8_t swPin = 255);
    void update();

    int getX();            // Đã map về 0 - 7
    int getY();
    int getRawX();         // Giá trị gốc ADC
    int getRawY();

    Direction getDirection();        // Trả về enum
    const char* getPositionName();   // Trả về chuỗi tên hướng
    bool isPressed();                // true nếu đang nhấn nút
	bool wasPressed();  
};

#endif // JOYSTICK_H
