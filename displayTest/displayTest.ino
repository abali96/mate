
//left half of LED matrix are pins 32-37
//right half of LED matrix are pins 22-27

//NUMBERS
#define SPACE{B00000000,B00000000,B00000000,B00000000,B00000000}
#define NUM0{B11100000,B10100000,B10100000,B10100000,B11100000}
#define NUM1{B01000000,B01000000,B01000000,B01000000,B01000000}
#define NUM2{B11100000,B00100000,B11100000,B10000000,B11100000}
#define NUM3{B11100000,B00100000,B11100000,B00100000,B11100000}
#define NUM4{B10100000,B10100000,B11100000,B00100000,B00100000}
#define NUM5{B11100000,B10000000,B11100000,B00100000,B11100000}
#define NUM6{B11100000,B10000000,B11100000,B10100000,B11100000}
#define NUM7{B11100000,B00100000,B00100000,B00100000,B00100000}
#define NUM8{B11100000,B10100000,B11100000,B10100000,B11100000}
#define NUM9{B11100000,B10100000,B11100000,B00100000,B11100000}
#define cloudLeft1{B00000000,B00000000,B00111100,B01111100,B00111100}
#define cloudRight2{B01111000,B11111100,B01111000,B10000000,B00000000}
#define cloudLeft2{B00000000,B00000100,B01111000,B11111100,B01111000}
#define cloudRight2{B11110000,B11111000,B11110000,B00000000,B00000000}
#define sunLeft1{B00011100,B00111100,B00111100,B00111100,B00011100}
#define sunRight1{B00000000,B10000000,B10000000,B10000000,B00000000}
#define sunLeft2{B00001100,B00011100,B00011100,B00011100,B00001100}
#define sunRight2{B10000000,B11000000,B11000000,B11000000,B10000000}
#define sunLeft3{B00000100,B00001100,B00001100,B00001100,B00000100}
#define sunRight3{B11000000,B11100000,B11100000,B11100000,B11000000}
#define sunLeft4{B00000000,B00000100,B00000100,B00000100,B00000000}
#define sunRight4{B11100000,B11110000,B11110000,B11110000,B11100000}
#define sunLeft5{B00000000,B00000000,B00000000,B00000000,B00000000}
#define sunRight5{B01110000,B11111000,B11111000,B11111000,B01110000}

int x, y, i;
byte numberMap[11][5]={NUM0,NUM1,NUM2,NUM3,NUM4,NUM5,NUM6,NUM7,NUM8,NUM9,SPACE};
byte weather[14][5]={cloudRight1,cloudLeft1,cloudRight2,cloudLeft2,sunLeft1,sunRight1,sunLeft2,sunRight2,sunLeft3,sunRight3,sunLeft4,sunRight4,sunLeft5,sunRight5};

void setup() {
  DDRA = B11111111;//set all of PORTA to output
  DDRC = B11111111;//set all of PORTC to output
  
  pinMode(20,OUTPUT);
  pinMode(21,OUTPUT);
  resetCounter();
  
}

void loop() {
  int avail_count = Serial1.available();  
  if (avail_count > 0) { // we have found something to read
    if ((char)Serial1.read() == 't') {
      Serial.println("here");
      String time_int = (String)Serial1.parseInt();
      
      for (int i = 0; i = 4 - time_int.length(); i++) {
        time_int = "0" + time_int;
      }

      Serial.println(time_int);
      while (Serial1.available() == 1) {
        displayString((int)time_int[0],(int)time_int[1],(int)time_int[2],(int)time_int[3]);
      }
    }
  }
}

void displayString(int a, int b, int c, int d){
  a -= 48;
  b -= 48;
  c -= 48;
  d -= 48;
  
    for (y = 0; y < 5; y++) {
      digitalWrite(20, HIGH);
 
      PORTA = (dictionary[c][y]>>2) + (dictionary[d][y] >> 5);//right side
      PORTC = (dictionary[a][y]>>2) + (dictionary[b][y] >> 5);//left side
      
      delay(1);
      digitalWrite(20, LOW);
      delay(1);
    }
}

void resetCounter(){
  digitalWrite(21,HIGH);
  digitalWrite(21,LOW);
  for (i = 0; i < 4; i++) {
    digitalWrite(20, HIGH);
    digitalWrite(20, LOW);
  }
}

void cloudy(){
   for(i = 0; i < 100; i++){
      for (y = 0; y < 5; y++) {
        digitalWrite(20, HIGH);
   
        PORTA = (weather[0][y]>>2);//right side
        PORTC = (weather[1][y]>>2);//left side
        
        delay(1);
        digitalWrite(20, LOW);
        delay(1);
      }
   }
   for(i = 0; i < 100; i++){
     for (y = 0; y < 5; y++) {
        digitalWrite(20, HIGH);
   
        PORTA = (weather[2][y]>>2);//right side
        PORTC = (weather[3][y]>>2);//left side
        
        delay(1);
        digitalWrite(20, LOW);
        delay(1);
      }
   }
}

void sunny(){//weather 4 through 13 
}

void rain(){
  ledClear();
  raindrop(random(22,28));
  raindrop(random(32,38));
}

void raindrop(int i){
 digitalWrite(i,HIGH);
  for (y = 0; y < 10; y++) {
      digitalWrite(20, HIGH);    
      delay(30);
      digitalWrite(20, LOW);
  }
  digitalWrite(i,LOW); 
}

void ledClear(){
  PORTA = B00000000;
  PORTC = B00000000;
}

