
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
#define cloudLeft{B00000000,B00000000,B00111100,B01111100,B00111100}
#define cloudRight{B01111000,B11111100,B01111000,B10000000,B00000000}
#define cloudLeft2{B00000000,B00000100,B01111000,B11111100,B01111000}
#define cloudRight2{B11110000,B11111000,B11110000,B00000000,B00000000}

int x, y, i;
byte dictionary[11][5]={NUM0,NUM1,NUM2,NUM3,NUM4,NUM5,NUM6,NUM7,NUM8,NUM9,SPACE};
byte weather[4][5]={cloudRight,cloudLeft,cloudRight2,cloudLeft2};

void setup() {
  DDRA = B11111111;//set all of PORTA to output
  DDRC = B11111111;//set all of PORTC to output
  
  pinMode(20,OUTPUT);
  pinMode(21,OUTPUT);
  resetCounter();
  
}

void loop() {
  cloudy();
  /*
  for(int i; i < 1000; i++){
  displayString(1,2,3,4);
  }
  for(int i; i < 100; i++){
  rain();
  }
  */
}

void displayString(int a, int b, int c, int d){
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

