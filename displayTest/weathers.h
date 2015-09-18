//left half of LED matrix are pins 32-37
//right half of LED matrix are pins 22-27
#include "Arduino.h"
static const struct Weathers {
    const byte cloudLeft1[5] = {B00000000, B00000000, B00111100, B01111100, B00111100};
    const byte cloudRight1[5] = {B01111000, B11111100, B01111000, B10000000, B00000000};
    const byte cloudLeft2[5] = {B00000000, B00000100, B01111000, B11111100, B01111000};
    const byte cloudRight2[5] = {B11110000, B11111000, B11110000, B00000000, B00000000};
    const byte sunLeft[5] = {B00000100, B00001100, B00001100, B00001100, B00000100};
    const byte sunRight[5] = {B11000000, B11100000, B11100000, B11100000, B11000000};
    const byte thunderLeft[5] = {B00000100, B00001100, B00011100, B00001100, B00011000};
    const byte thunderRight[5] = {B10000000, B00000000, B10000000, B00000000, B00000000};
    const byte snowLeft[5] = {B01000000, B11100000, B01001000, B00011100, B00001000};
    const byte snowRight[5] = {B01000000, B11100000, B01001000, B00011100, B00001000};
} weathers;


static const int SunWeatherType = 0;
static const int CloudWeatherType = 1;
static const int RainWeatherType = 2;
static const int ThunderWeatherType = 4;
static const int SnowWeatherType = 5;
