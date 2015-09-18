#include "Arduino.h"
static const struct Constants {
   static const int charIntOffset = 48;
   static const int baudRate = 9600;
   const char defaultTime[4] = {'0'};
   static const int clockPulseDelay = 1;  // milliseconds
   static const int rainDropDelay = 1;  // We send a delimiter 'A' right now between data strings.
   static const int cloudAnimateDelay = 1000;  // 1 second == 1000 milliseconds
   static const int numRows = 5;
   static const int timeStringLength = 4;  // We want time to consist of two hour digits and two minute digits.
   static const int delimiterLength = 1;  // We send a delimiter 'A' right now between data strings.
   
} constants;
