#include "pinouts.h"
#include "delimiters.h"
#include "characters.h"
#include "weathers.h"
#include "constants.h"

int x, y, i, weather; 
bool* ascii_map[255];
volatile bool mode; // 1 is time, 0 is weather
String time = constants.defaultTime;

void printBits(byte myByte){
 for(byte mask = 0x80; mask; mask >>= 1){
   if(mask  & myByte)
       Serial.print('1');
   else
       Serial.print('0');
 }
 Serial.println("");
}

unsigned char reverse(unsigned char b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

// http://stackoverflow.com/questions/8461126/creating-a-byte-out-of-8-bool-values-and-vice-versa
unsigned char ToByte(bool b[8])
{
    unsigned char c = 0;
    for (int i=0; i < 8; ++i)
        if (b[i])
            c |= 1 << i;
    return c;
}

void setup() {
  ascii_map[48] = characters.zero;
  ascii_map[49] = characters.one;
  ascii_map[50] = characters.two;
  ascii_map[51] = characters.three;
  ascii_map[52] = characters.four;
  ascii_map[53] = characters.five;
  ascii_map[54] = characters.six;
  ascii_map[55] = characters.seven;
  ascii_map[56] = characters.eight;
  ascii_map[57] = characters.nine;
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
  String str = "12";
  displayString(str);
}

void modeISR(){
  detachInterrupt(digitalPinToInterrupt(pinMap.buttonInterruptPin));
  mode = !mode;
  attachInterrupt(digitalPinToInterrupt(pinMap.buttonInterruptPin), modeISR, RISING);
}

void displayString(String data) {
  bool display_map[5][12] = {0};
  
  for (int char_idx = 0; char_idx < data.length(); char_idx++) {  // Here, concatenate the characters into one large array
    int ascii_idx = (int)(data[char_idx]);
    for (int row_idx = 0; row_idx < constants.numRows; row_idx++) {
      for (int col_idx = 0; col_idx < 3; col_idx++) {
        display_map[row_idx][col_idx + char_idx * 3] = ascii_map[ascii_idx][col_idx + row_idx * 3];
      }
    }
  }
  while (true) {
    for (int row_idx = 0; row_idx < constants.numRows; row_idx++) {
      bool port_c_bools[8] = {0}, port_a_bools[8] = {0};
      for (int count = 0; count < 6; count++) {  // Get the first six characters of the row
        port_c_bools[count] = display_map[row_idx][count];
      }
      for (int count = 0; count < 6; count++) {  // Get the 6th to 12th characters of the row
        port_a_bools[count] = display_map[row_idx][count + 6];
      }
      digitalWrite(pinMap.decadeCounterClockPin, HIGH);
//      delay(constants.clockPulseDelay);
      PORTC = reverse(ToByte(port_c_bools)) >> 2;
      PORTA = reverse(ToByte(port_a_bools)) >> 2;
      bool first_val = display_map[row_idx][0];
      for (int display_map_idx = 1; display_map_idx < 12; display_map_idx++) {
       display_map[row_idx][display_map_idx - 1] = display_map[row_idx][display_map_idx];
      }
      display_map[row_idx][12 - 1] = first_val;
      digitalWrite(pinMap.decadeCounterClockPin, LOW);
      delay(constants.clockPulseDelay);
    }
    delay(30);
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
