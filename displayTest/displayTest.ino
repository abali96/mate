
//left half of LED matrix are pins 32-37
//right half of LED matrix are pins 22-27
#define SPACE {B00000000, B00000000, B00000000, B00000000, B00000000}
#define NUM0 {B11100000, B10100000, B10100000, B10100000, B11100000}
#define NUM1 {B01000000, B01000000, B01000000, B01000000, B01000000}
#define NUM2 {B11100000, B00100000, B11100000, B10000000, B11100000}
#define NUM3 {B11100000, B00100000, B11100000, B00100000, B11100000}
#define NUM4 {B10100000, B10100000, B11100000, B00100000, B00100000}
#define NUM5 {B11100000, B10000000, B11100000, B00100000, B11100000}
#define NUM6 {B11100000, B10000000, B11100000, B10100000, B11100000}
#define NUM7 {B11100000, B00100000, B00100000, B00100000, B00100000}
#define NUM8 {B11100000, B10100000, B11100000, B10100000, B11100000}
#define NUM9 {B11100000, B10100000, B11100000, B00100000, B11100000}
#define cloudLeft1 {B00000000, B00000000, B00111100, B01111100, B00111100}
#define cloudRight1 {B01111000, B11111100, B01111000, B10000000, B00000000}
#define cloudLeft2 {B00000000, B00000100, B01111000, B11111100, B01111000}
#define cloudRight2 {B11110000, B11111000, B11110000, B00000000, B00000000}
#define sunLeft {B00000100, B00001100, B00001100, B00001100, B00000100}
#define sunRight {B11000000, B11100000, B11100000, B11100000, B11000000}
#define thunderLeft {B00000100, B00001100, B00011100, B00001100, B00011000}
#define thunderRight {B10000000, B00000000, B10000000, B00000000, B00000000}
#define snowLeft {B01000000, B11100000, B01001000, B00011100, B00001000}
#define snowRight {B01000000, B11100000, B01001000, B00011100, B00001000}
#define timeDelimiter 't'
#define weatherDelimiter 'w'
#define charIntOffset 48
#define decadeCounterResetPin 21
#define decadeCounterClockPin 20
#define buttonInterruptPin 3


int x, y, i, weather; 
volatile bool mode;// 1 is time, 0 is weather
String time_int = "0000";

byte numberMap[11][5] = {NUM0, NUM1, NUM2, NUM3, NUM4, NUM5, NUM6, NUM7, NUM8, NUM9, SPACE};
byte weatherMap[14][5] = {cloudRight1, cloudLeft1, cloudRight2, cloudLeft2, sunLeft, sunRight, thunderLeft, thunderRight, snowLeft, snowRight};

void setup() {
  DDRA = B11111111;  //set all of PORTA to output
  DDRC = B11111111;  //set all of PORTC to output
  Serial.begin(9600);  // debugging (printing) serial
  Serial1.begin(9600); // reading in serial
  pinMode(decadeCounterClockPin, OUTPUT);
  pinMode(decadeCounterResetPin, OUTPUT);
  resetCounter();
  mode = 1;

  pinMode(buttonInterruptPin, INPUT);
  digitalWrite(buttonInterruptPin, HIGH);
  attachInterrupt(digitalPinToInterrupt(buttonInterruptPin), modeISR, RISING);
}

void loop() {
  int avail_count = Serial1.available();

  if (avail_count > 0) { // we have found something to read
    char datatype = (char)Serial1.read();
    if (datatype == timeDelimiter) {
      time_int = (String)Serial1.parseInt();

      for (int i = 0; i = 4 - time_int.length(); i++) {
        time_int = "0" + time_int;
      }

    } else if (datatype == weatherDelimiter) {
      weather = (int)(char)(Serial1.read()) - charIntOffset;
      Serial.println(weather);
    }

    while (Serial1.available() == 1) {
      if (mode) {
        displayString((int)time_int[0] - charIntOffset,(int)time_int[1] - charIntOffset,(int)time_int[2] - charIntOffset,(int)time_int[3] - charIntOffset);
      }
      else {
        Serial.println("weather");
        Serial.println(weather);
        displayWeather(weather);
      }
    }

  }
}

void modeISR(){
  detachInterrupt(digitalPinToInterrupt(buttonInterruptPin));
  mode = !mode;
  Serial.println(mode);
  attachInterrupt(digitalPinToInterrupt(buttonInterruptPin), modeISR, RISING);
}

void displayString(int a, int b, int c, int d) {
    for (y = 0; y < 5; y++) {
      digitalWrite(decadeCounterClockPin, HIGH);
 
      PORTA = (numberMap[c][y] >> 2) + (numberMap[d][y] >> 5);//right side
      PORTC = (numberMap[a][y] >> 2) + (numberMap[b][y] >> 5);//left side
      
      delay(1);
      digitalWrite(decadeCounterClockPin, LOW);
      delay(1);
    }
}

void resetCounter(){
  digitalWrite(decadeCounterResetPin,HIGH);
  digitalWrite(decadeCounterResetPin,LOW);
  for (i = 0; i < 4; i++) {
    digitalWrite(decadeCounterClockPin, HIGH);
    digitalWrite(decadeCounterClockPin, LOW);
  }
}

void displayWeather(int weather){//sun, cloud, rain, thunder, snow
    switch (weather) {
      case 0:
        return sun();
      case 1:
        return clouds();
      case 2:
        return rain();
      case 3:
        return thunder();
      case 4:
        return snow();
    }
}

void displayImage(int a, int b, int t) {// a is right side, b is left side, t is time
  for (i = 0; i < t; i++) {
      for (y = 0; y < 5; y++) {
        digitalWrite(decadeCounterClockPin, HIGH);
   
        PORTA = (weatherMap[a][y] >> 2);//right side
        PORTC = (weatherMap[b][y] >> 2);//left side
        
        delay(1);
        digitalWrite(decadeCounterClockPin, LOW);
        delay(1);
      }
   }
}

void sun(){
   displayImage(5, 4, 100);
}

void clouds(){
   displayImage(0, 1, 100);
   displayImage(2, 3, 100);
}

void rain(){
  clearMatrix();
  raindrop(random(22, 28));
  raindrop(random(32, 38));
}

void raindrop(int i){
 digitalWrite(i, HIGH);
  for (y = 0; y < 10; y++) {
      digitalWrite(decadeCounterClockPin, HIGH);    
      delay(30);
      digitalWrite(decadeCounterClockPin, LOW);
  }
  digitalWrite(i, LOW); 
}

void thunder(){
    displayImage(7, 6, 100);  
}

void snow(){
    displayImage(9, 8, 100);  
}

void clearMatrix() {
  PORTA = B00000000;
  PORTC = B00000000;
}
