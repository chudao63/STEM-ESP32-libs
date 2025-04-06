#include <Arduino.h>
#include "joystick_lib.h"
#include "rgb_library.h"

Joystick joystick;
RGBLed rgb(15, 15); // cấu hình giả định, bạn có thể thay bằng RGBLed(25,26,27) nếu dùng rời

unsigned long pressedTime = 0;


void setup() {
    Serial.begin(115200);
    joystick.begin(36);  // chân SW
    rgb.begin();
}

void loop() {
    joystick.update();

    // Xử lý hướng
    Direction dir = joystick.getDirection();

    // Đổi màu LED theo hướng
    switch (dir) {
        case CENTER:     rgb.showColor(COLOR_WHITE);   break;
        case UP:         rgb.showColor(COLOR_BLUE);    break;
        case DOWN:       rgb.showColor(COLOR_GOLD);    break;
        case LEFT:       rgb.showColor(COLOR_ORANGE);  break;
        case RIGHT:      rgb.showColor(COLOR_GREEN);   break;
        case UP_LEFT:    rgb.showColor(COLOR_PINK);    break;
        case UP_RIGHT:   rgb.showColor(COLOR_GRAY);    break;
        case DOWN_LEFT:  rgb.showColor(COLOR_TEAL);    break;
        case DOWN_RIGHT: rgb.showColor(COLOR_LIME);    break;
    }


    if (joystick.isPressed()) {
    
        pressedTime = millis();
        rgb.turnOff();
        Serial.println("BUTTON PRESSED");
    }
    // Test nhấn nút 1 lần
    // if (joystick.wasPressed()) {
    //   Serial.println("Button was just pressed!");
    //   rgb.turnOff();
    // }

    Serial.println();
    delay(50);
}
