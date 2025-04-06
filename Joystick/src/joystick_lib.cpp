#include "joystick_lib.h"

Joystick::Joystick(uint8_t vrxPin, uint8_t vryPin)
    : pinVRX(vrxPin), pinVRY(vryPin), rawVrx(0), rawVry(0),
      vrxValue(0), vryValue(0), swState(false), lastSwState(false),
      wasPressedFlag(false), pinSW(255), lastDebounceTime(0) {}

void Joystick::begin(uint8_t swPin) {
    if (swPin != 255) {
        pinSW = swPin;
        pinMode(pinSW, INPUT_PULLUP);
    }
}

void Joystick::update() {
    rawVrx = analogRead(pinVRX);
    rawVry = analogRead(pinVRY);

    vrxValue = map(rawVrx, 0, 4095, 0, 7);
    vryValue = map(rawVry, 0, 4095, 0, 7);

   if (pinSW != 255) {
        bool reading = (digitalRead(pinSW) == LOW);

        if (reading != lastSwState) {
            lastDebounceTime = millis();
        }

        if ((millis() - lastDebounceTime) > debounceDelay) {
            if (reading != swState) {
                swState = reading;
                if (swState == true) {
                    wasPressedFlag = true; // phát hiện sự kiện nhấn xuống
                }
            }
        }

        lastSwState = reading;
    }
}

int Joystick::getX() {
    return vrxValue;
}

int Joystick::getY() {
    return vryValue;
}

int Joystick::getRawX() {
    return rawVrx;
}

int Joystick::getRawY() {
    return rawVry;
}

Direction Joystick::getDirection() {
    if (vrxValue == 7 && vryValue == 0) return UP_LEFT;
    if (vrxValue == 0 && vryValue == 0) return UP_RIGHT;
    if (vrxValue == 7 && vryValue == 7) return DOWN_LEFT;
    if (vrxValue == 0 && vryValue == 7) return DOWN_RIGHT;
    if (vrxValue == 3 && vryValue == 0) return UP;
    if (vrxValue == 3 && vryValue == 7) return DOWN;
    if (vrxValue == 7 && vryValue == 3) return LEFT;
    if (vrxValue == 0 && vryValue == 3) return RIGHT;
    return CENTER;
}

const char* Joystick::getPositionName() {
    switch (getDirection()) {
        case LEFT: return "LEFT";
        case RIGHT: return "RIGHT";
        case UP: return "UP";
        case DOWN: return "DOWN";
        case UP_LEFT: return "UP_LEFT";
        case UP_RIGHT: return "UP_RIGHT";
        case DOWN_LEFT: return "DOWN_LEFT";
        case DOWN_RIGHT: return "DOWN_RIGHT";
        default: return "CENTER";
    }
}

bool Joystick::isPressed() {
    return swState;
}
bool Joystick::wasPressed() {
    if (wasPressedFlag) {
        wasPressedFlag = false;
        return true;
    }
    return false;
}
