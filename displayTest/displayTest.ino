#include "pinouts.h"
#include "delimiters.h"
#include "characters.h"
#include "weathers.h"
#include "constants.h"

int x, y, i, weather; 
bool ascii_map[255];
volatile bool mode; // 1 is time, 0 is weather
String time = constants.defaultTime;

void setup() {
//  ascii_map[48] = characters.zero;
//  ascii_map[49] = characters.one;
//  ascii_map[50] = characters.two;
//  ascii_map[51] = characters.three;
//  ascii_map[52] = characters.four;
//  ascii_map[53] = characters.five;
//  ascii_map[54] = characters.six;
//  ascii_map[55] = characters.seven;
//  ascii_map[56] = characters.eight;
//  ascii_map[57] = characters.nine;
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
  String str = "11111";
  displayString(str);
  delay(5000);
}

void modeISR(){
  detachInterrupt(digitalPinToInterrupt(pinMap.buttonInterruptPin));
  mode = !mode;
  attachInterrupt(digitalPinToInterrupt(pinMap.buttonInterruptPin), modeISR, RISING);
}

void displayString(String data) {
  bool display_map[999][5];
  
  for (int char_idx = 0; char_idx < data.length(); char_idx++) {
    for (int row = 0; row < constants.numRows; row++) {
      for (int col = 0; col < constants.numCols; col++) {
        int ascii_idx = (int)(data[char_idx]);
        Serial.println(ascii_map[ascii_idx]);
        delay(500);
      }
    }
  }
//  for (int i = 0; i < 999; i++) {
//    for (int j = 0; j < 5; j++) {
//      Serial.print(display_map[i][j]);
//    }
//    Serial.println("");
//  }
  
//    for (y = 0; y < constants.numRows; y++) {
//      digitalWrite(pinMap.decadeCounterClockPin, HIGH);
//      PORTA = (ascii_map[c][y] >> 2) + (ascii_map[d][y] >> 5);  // right side of display
//      PORTC = (ascii_map[a][y] >> 2) + (ascii_map[b][y] >> 5);  // l   eft side of display
//      
//      delay(constants.clockPulseDelay);
//      digitalWrite(pinMap.decadeCounterClockPin, LOW);
//      delay(constants.clockPulseDelay);
//    }
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
