
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
//WEATHER SYMBOLS



int x, y;
byte dictionary[11][5]={NUM0,NUM1,NUM2,NUM3,NUM4,NUM5,NUM6,NUM7,NUM8,NUM9,SPACE};

void setup() {
  DDRA = B11111111;//set all of PORTA to output
  DDRC = B11111111;//set all of PORTC to output
  
  pinMode(20,OUTPUT);
  pinMode(21,OUTPUT);
  resetCounter();
  
}

void loop() {
  //displayString(1,2,3,4);
  displayWeather();
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

void displayWeather(){
  raindrop(random(22,28));
  raindrop(random(32,38));
}

void resetCounter(){
  digitalWrite(21,HIGH);
  digitalWrite(21,LOW);
  for (int i = 0; i < 4; i++) {
    digitalWrite(20, HIGH);
    digitalWrite(20, LOW);
  }
 }

void raindrop(int i){
 digitalWrite(i,HIGH);
  for (y = 0; y < 10; y++) {
      digitalWrite(20, HIGH);    
      delay(30);
      digitalWrite(20, LOW);
      //delay(20);
  }
  digitalWrite(i,LOW); 
}

