#ifndef __RGBLED_H__
#define __RGBLED_H__

#include <Arduino.h>
#include <Adafruit_NeoPixel.h>

enum RGBColor {
  COLOR_NONE = 0,
  COLOR_RED,
  COLOR_GREEN,
  COLOR_BLUE,
  COLOR_YELLOW,
  COLOR_CYAN,
  COLOR_MAGENTA,
  COLOR_ORANGE,
  COLOR_PURPLE,
  COLOR_WHITE,
  COLOR_BLACK,
  COLOR_PINK,
  COLOR_LIME,
  COLOR_TEAL,
  COLOR_NAVY,
  COLOR_MAROON,
  COLOR_OLIVE,
  COLOR_GRAY,
  COLOR_SILVER,
  COLOR_BROWN,
  COLOR_GOLD
};

enum BLEVEL {
  B_NORMAL = 100,
  B_HIGH = 255
};


class RGBLed {
  public:
    RGBLed(uint8_t pin, uint16_t count);
    void begin(uint8_t brightness = 50);
    void setBrightness(uint8_t level);
    void showColor( RGBColor color);
    void turnOff();
    void rainbowCycle(uint8_t cycles = 5, uint16_t wait_ms = 10);
    void showAllColor(uint16_t wait_ms = 500);
	void setPixelColor(uint16_t index, RGBColor color, BLEVEL blevel);
	void blink(RGBColor color, uint8_t time = 3, uint16_t on_time = 1000, uint16_t off_time = 1000);
	void fadeInOut(RGBColor color, uint8_t steps = 15, uint16_t delay_ms = 300);
	void printColorListToSerial();
	
  private:
    Adafruit_NeoPixel strip;
    uint32_t getColorFromType(RGBColor color);
    uint32_t wheel(byte WheelPos);
};

#endif
