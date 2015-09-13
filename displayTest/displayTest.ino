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
  displayString(2,1,4,3);
//  delay(1000);
//  displayString(3,2);
//  delay(1000);
}

void displayString(int a, int b, int c, int d){
    for (y = 0; y < 5; y++) {
      digitalWrite(20, HIGH);
      //PORTC = B10101000;
   
      PORTA = (dictionary[d][y]>>2) + (dictionary[c][y] >> 5);
      PORTC = (dictionary[b][y]) + (dictionary[a][y] >> 3);
      delay(1);
      digitalWrite(20, LOW);
      delay(1);
    }
}

void resetCounter(){
  digitalWrite(21,HIGH);
  digitalWrite(21,LOW);
  for (int i = 0; i < 4; i++) {
    digitalWrite(20, HIGH);
    digitalWrite(20, LOW);
  }
}

