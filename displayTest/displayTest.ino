#include "pinouts.h"
#include "delimiters.h"
#include "characters.h"
#include "weathers.h"
#include "constants.h"

int x, y, i, weather; 
volatile bool mode; // 1 is time, 0 is weather
String time = constants.defaultTime;
const byte* numberMap[11] = {characters.zero, characters.one, characters.two, characters.three, characters.four, characters.five, characters.six, characters.seven, characters.eight, characters.nine, characters.space};

void setup() {
  DDRA = B11111111;  //set all of PORTA to output
  DDRC = B11111111;  //set all of PORTC to output
  Serial.begin(constants.baudRate);  // debugging (printing) serial
  Serial1.begin(constants.baudRate); // serial for reading values from Particle Photon  
  pinMode(pinMap.decadeCounterClockPin, OUTPUT);
  pinMode(pinMap.decadeCounterResetPin, OUTPUT);
  resetCounter();
  mode = 1;

  pinMode(pinMap.buttonInterruptPin, INPUT);
  digitalWrite(pinMap.buttonInterruptPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(pinMap.buttonInterruptPin), modeISR, RISING);
}

void loop() {
  if (Serial1.available() > 0) { // we have found something to read
    char datatype = (char)Serial1.read();  // The first character will be the type of data.
    
    if (datatype == delimiters.timeStart) {
      time = (String)Serial1.parseInt();
      for (int i = 0; i = constants.timeStringLength - time.length(); i++) {  // Since parseInt will omit leading zeros, we must re-patch them on. (4 is the number of digits we desire in time string)
        time = "0" + time;
      }
    } else if (datatype == delimiters.weatherStart) {
      weather = (int)(char)(Serial1.read()) - constants.charIntOffset;
    }

    while (Serial1.available() == constants.delimiterLength) {
      if (mode)
        displayString((int)time[0] - constants.charIntOffset,(int)time[1] - constants.charIntOffset,(int)time[2] - constants.charIntOffset,(int)time[3] - constants.charIntOffset);
      else
        displayWeather(2);
    }
  }
}

void modeISR(){
  detachInterrupt(digitalPinToInterrupt(pinMap.buttonInterruptPin));
  mode = !mode;
  attachInterrupt(digitalPinToInterrupt(pinMap.buttonInterruptPin), modeISR, RISING);
}

void displayString(int a, int b, int c, int d) {
    for (y = 0; y < constants.numRows; y++) {
      digitalWrite(pinMap.decadeCounterClockPin, HIGH);
      PORTA = (numberMap[c][y] >> 2) + (numberMap[d][y] >> 5);  // right side of display
      PORTC = (numberMap[a][y] >> 2) + (numberMap[b][y] >> 5);  // l   eft side of display
      
      delay(constants.clockPulseDelay);
      digitalWrite(pinMap.decadeCounterClockPin, LOW);
      delay(constants.clockPulseDelay);
    }
}

void resetCounter() {
  digitalWrite(pinMap.decadeCounterResetPin, HIGH);  // Turning the reset pin on and off will move us to output position 1
  digitalWrite(pinMap.decadeCounterResetPin, LOW);
  for (i = 0; i < constants.numRows - 1; i++) {  // Then push the clock four more times to get us back to output position 0
    digitalWrite(pinMap.decadeCounterClockPin, HIGH);
    digitalWrite(pinMap.decadeCounterClockPin, LOW);
  }
}

void displayWeather(int weather) {
    switch (weather) {
      case SunWeatherType:
        return sun();
      case CloudWeatherType:
        return clouds();
      case RainWeatherType:
        return rain();
      case ThunderWeatherType:
        return thunder();
      case SnowWeatherType:
        return snow();
    }
}

void displayImage(const byte left_side[8], const byte right_side[8]) {
    for (y = 0; y < constants.numRows; y++) {
      digitalWrite(pinMap.decadeCounterClockPin, HIGH);
 
      PORTA = (right_side[y] >> 2);
      PORTC = (left_side[y] >> 2); 
      
      delay(constants.clockPulseDelay);
      digitalWrite(pinMap.decadeCounterClockPin, LOW);
      delay(constants.clockPulseDelay);
    }
}

void sun() {
   displayImage(weathers.sunLeft, weathers.sunRight);
}

void clouds(){
  displayImage(weathers.cloudLeft1, weathers.cloudRight1);
}

void rain(){
  clearMatrix();
  raindrop(random(22, 28));
  raindrop(random(32, 38));
  delay(1);
}

void raindrop(int i) {
  digitalWrite(i, HIGH);
    for (y = 0; y < 10; y++) {
      digitalWrite(pinMap.decadeCounterClockPin, HIGH);    
      delay(constants.rainDropDelay);
      digitalWrite(pinMap.decadeCounterClockPin, LOW);
    }
  digitalWrite(i, LOW); 
}

void thunder(){
    displayImage(weathers.thunderLeft, weathers.thunderRight);  
}

void snow() {
    displayImage(weathers.snowLeft, weathers.snowRight);
}

void clearMatrix() {
  PORTA = B00000000;
  PORTC = B00000000;
}
