#include "rgb_library.h"

RGBLed::RGBLed(uint8_t pin, uint16_t count)
  : strip(count, pin, NEO_GRB + NEO_KHZ800) {}

void RGBLed::begin(uint8_t brightness) {
  strip.begin();
  strip.setBrightness(brightness);
  strip.show();
}
void RGBLed::setBrightness(uint8_t level) {
  strip.setBrightness(level);
  strip.show(); 
}

uint32_t RGBLed::getColorFromType(RGBColor color) {
  switch (color) {
    case COLOR_RED:      return strip.Color(255, 0, 0);
    case COLOR_GREEN:    return strip.Color(0, 255, 0);
    case COLOR_BLUE:     return strip.Color(0, 0, 255);
    case COLOR_YELLOW:   return strip.Color(255, 255, 0);
    case COLOR_CYAN:     return strip.Color(0, 255, 255);
    case COLOR_MAGENTA:  return strip.Color(255, 0, 255);
    case COLOR_ORANGE:   return strip.Color(255, 165, 0);
    case COLOR_PURPLE:   return strip.Color(128, 0, 128);
    case COLOR_WHITE:    return strip.Color(255, 255, 255);
    case COLOR_BLACK:    return strip.Color(0, 0, 0);
    case COLOR_PINK:     return strip.Color(255, 192, 203);
    case COLOR_LIME:     return strip.Color(50, 205, 50);
    case COLOR_TEAL:     return strip.Color(0, 128, 128);
    case COLOR_NAVY:     return strip.Color(0, 0, 128);
    case COLOR_MAROON:   return strip.Color(128, 0, 0);
    case COLOR_OLIVE:    return strip.Color(128, 128, 0);
    case COLOR_GRAY:     return strip.Color(128, 128, 128);
    case COLOR_SILVER:   return strip.Color(192, 192, 192);
    case COLOR_BROWN:    return strip.Color(139, 69, 19);
    case COLOR_GOLD:     return strip.Color(255, 215, 0);
    default:             return 0;
  }
}
void RGBLed::showColor(RGBColor color_type) {
  uint32_t color = getColorFromType(color_type);
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, color);
  }
  strip.show();
}

void RGBLed::turnOff(){
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, 0);
  }
  strip.show();
}

void RGBLed::rainbowCycle(uint8_t cycles, uint16_t wait_ms) {
  for (int j = 0; j < 256 * cycles; j++) {
    for (int i = 0; i < strip.numPixels(); i++) {
      strip.setPixelColor(i, wheel(((i * 256 / strip.numPixels()) + j) & 255));
    }
    strip.show();
    delay(wait_ms);
  }
}

void RGBLed::showAllColor(uint16_t wait_ms){
  for (int color = COLOR_RED; color <= COLOR_GOLD; color++) {
    showColor(static_cast<RGBColor>(color));
    delay(wait_ms);  // 500ms mỗi màu
  }
}

void RGBLed::setPixelColor(uint16_t index, RGBColor color, BLEVEL bsness){
  if (index < strip.numPixels()) {
    strip.setBrightness(static_cast<uint8_t>(bsness));  // chuyển enum → int
    strip.setPixelColor(index, getColorFromType(color));
    strip.show();
  }
}

void RGBLed::blink(RGBColor color, uint8_t times, uint16_t on_time, uint16_t off_time) {
  for (uint8_t i = 0; i < times; i++) {
    showColor(color);
    delay(on_time);
    showColor(COLOR_BLACK);
    delay(off_time);
  }
}
void RGBLed::fadeInOut(RGBColor color, uint8_t steps, uint16_t delay_ms) {
  uint32_t c = getColorFromType(color);
  uint8_t r = (c >> 16) & 0xFF;
  uint8_t g = (c >> 8) & 0xFF;
  uint8_t b = c & 0xFF;

  for (int bLevel = 0; bLevel <= 255; bLevel += 255 / steps) {
    strip.setBrightness(bLevel);
    showColor(color);
    delay(delay_ms);
  }
  for (int bLevel = 255; bLevel >= 0; bLevel -= 255 / steps) {
    strip.setBrightness(bLevel);
    showColor(color);
    delay(delay_ms);
  }
  strip.setBrightness(50); // reset to default brightness
}

void RGBLed::printColorListToSerial() {
  const char* names[] = {
    "NONE", "COLOR_RED", "COLOR_GREEN", "COLOR_BLUE", "COLOR_YELLOW", "COLOR_CYAN", "COLOR_MAGENTA", "COLOR_ORANGE", "COLOR_PURPLE",
    "COLOR_WHITE", "COLOR_BLACK", "COLOR_PINK", "COLOR_LIME", "COLOR_TEAL", "COLOR_NAVY", "COLOR_MAROON", "COLOR_OLIVE", "COLOR_GRAY",
    "COLOR_SILVER", "COLOR_BROWN", "COLOR_GOLD"
  };

  Serial.println("Available Colors:");
  for (int i = 0; i <= COLOR_GOLD; i++) {
    Serial.print(i);
    Serial.print(": ");
    Serial.println(names[i]);
  }
}

uint32_t RGBLed::wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

