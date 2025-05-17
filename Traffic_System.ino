#define segA 4//connecting segment A to PIN2


#define segB 5// connecting segment B to PIN3


#define segC 8// connecting segment C to PIN4


#define segD 7// connecting segment D to PIN5


#define segE 6// connecting segment E to PIN6


#define segF 3// connecting segment F to PIN7


#define segG 2// connecting segment G to PIN8


#define segAh A4


#define segCh A3


#define segFh 9


#define segGh A5


#define IRpin 13

const int rowPins[] = {10, 11, 12, 13};  // selects a road

const int colPins[] = {A0, A1, A2};  //selects a colour

int countdown[] = {20, 25, 25, 25};

unsigned long previousMillis = 0;

const long interval = 1000; 

int row = 0, col = 2;

int orangeTimer = 5;

bool orangeActive = false;

void lightLCD(int time){
      int higher = time/10;
      int lower = time%10;
      switch(higher){
        case 0:
          digitalWrite(segAh, HIGH);
          digitalWrite(segCh, HIGH);
          digitalWrite(segFh, HIGH);
          digitalWrite(segGh, LOW);
          break;
        case 1:
          digitalWrite(segAh, LOW);
          digitalWrite(segCh, HIGH);
          digitalWrite(segFh, LOW);
          digitalWrite(segGh, LOW);
          break;

        case 2:
          digitalWrite(segAh, HIGH);
          digitalWrite(segCh, LOW);
          digitalWrite(segFh, LOW);
          digitalWrite(segGh, HIGH);
          break;
        case 3: //displays 0, since not enough segments are there to display 3
          digitalWrite(segAh, HIGH);
          digitalWrite(segCh, HIGH);
          digitalWrite(segFh, HIGH);
          digitalWrite(segGh, LOW);
          break;

          break;

      }
      switch (lower)
      {

        case 0://when count value is zero show”0” on disp
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, LOW);
        break;

        case 1:// when count value is 1 show”1” on disp
        digitalWrite(segA, LOW);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, LOW);
        digitalWrite(segE, LOW);
        digitalWrite(segF, LOW);
        digitalWrite(segG, LOW);
        break;

        case 2:// when count value is 2 show”2” on disp
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, LOW);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, LOW);
        digitalWrite(segG, HIGH);
        break;

        case 3:// when count value is 3 show”3” on disp
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, LOW);
        digitalWrite(segF, LOW);
        digitalWrite(segG, HIGH);
        break;

        case 4:// when count value is 4 show”4” on disp
        digitalWrite(segA, LOW);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, LOW);
        digitalWrite(segE, LOW);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;

        case 5:// when count value is 5 show”5” on disp
        digitalWrite(segA, HIGH);
        digitalWrite(segB, LOW);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, LOW);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;

        case 6:// when count value is 6 show”6” on disp
        digitalWrite(segA, HIGH);
        digitalWrite(segB, LOW);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;

        case 7:// when count value is 7 show”7” on disp
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, LOW);
        digitalWrite(segE, LOW);
        digitalWrite(segF, LOW);
        digitalWrite(segG, LOW);
        break;

        case 8:// when count value is 8 show”8” on disp
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, HIGH);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;

        case 9:// when count value is 9 show”9” on disp
        digitalWrite(segA, HIGH);
        digitalWrite(segB, HIGH);
        digitalWrite(segC, HIGH);
        digitalWrite(segD, HIGH);
        digitalWrite(segE, LOW);
        digitalWrite(segF, HIGH);
        digitalWrite(segG, HIGH);
        break;

        break;
      }
}

void lightLEDs() {
    for (int i = 0; i < 4; i++) {
      digitalWrite(rowPins[i], HIGH);
    }
    for(int i = 0; i<3; i++){
      digitalWrite(colPins[i], LOW);
    }
    for (int i = 0; i < 4; i++) {
      if(i == row){
        digitalWrite(colPins[col], HIGH); //Green or orange LED for current road
      }
      else{
        digitalWrite(colPins[0], HIGH); //Red LED
      }
      digitalWrite(rowPins[i], LOW); //Activating current road
      lightLCD(countdown[i]);
      delay(5);
      digitalWrite(rowPins[i], HIGH);
      for(int j = 0; j<4; j++){
        digitalWrite(colPins[j], LOW);
      }
    }
}

void setup(){
  for (int i=2;i<9;i++)
  {
    pinMode(i, OUTPUT);// taking all pins from 2-8 as output
  }
  for (int i = 0; i < 4; i++) {
    pinMode(rowPins[i], OUTPUT);
  }
  for (int i = 0; i < 3; i++) {
    pinMode(colPins[i], OUTPUT);
  }
  pinMode(segAh, OUTPUT);
  pinMode(segCh, OUTPUT);
  pinMode(segFh, OUTPUT); 
  pinMode(segGh, OUTPUT);
  pinMode(IRpin, INPUT);
}

void loop(){
    lightLEDs();
    unsigned long currentMillis = millis();
    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;  
        for(int i = 0; i<4; i++){
          if(!orangeActive || i!=row){
            countdown[i] = countdown[i] - 1;
            if(countdown[i] == 0){
              if(i == row){
                countdown[i] = 0;
                orangeActive = true;
                col = col-1;
              }
              else{
                countdown[i] = 25;
              }
            }
          }
          else{
            orangeTimer--;
            if(orangeTimer == 0){
              orangeTimer = 5;
              orangeActive = false;
              countdown[row] = 25;
              row = (row+1)%4;
              col = 2;
              countdown[row] = 20;
              i++;
            }
          }
          int carPresent = !digitalRead(IRpin);
          if(carPresent){
            col = 2;
            countdown[0] = 20;
            for(int j = 1; j<4; j++){
              countdown[j] = 25;
            }
          }
        }
    }
}