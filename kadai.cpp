#include "Adafruit_LEDBackpack.h"
#include <Keypad.h>
Adafruit_7segment dis = Adafruit_7segment();

const byte numRows= 4;
const byte numCols= 4;

char keymap[numRows][numCols]= 
{
{'1', '2', '3'}, 
{'4', '5', '6'}, 
{'7', '8', '9'},
{'a', '0'}
};


int room[3] = {1101, 1728, 1357};
int password[3] = {1234, 5678, 9012};


byte rowPins[numRows] = {9,8,7,6}; 
byte colPins[numCols]= {5,4,3,2}; 

Keypad myKeypad= Keypad(makeKeymap(keymap), rowPins, colPins, numRows, numCols);

int num = 0;
int ret = 0;
int disp = 0;
int led_mode = 2;
int room_num = 0;
int counter = 0;



void setup()
{
  dis.begin(0x70);
  Serial.begin(9600);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

}

void loop() {

  turnOnLED();
  dis.println(num);
  dis.writeDisplay();
  if(num < 1000)
  {
    ret = pad();
  }else if(room_num == 0){
    if(num == room[0] || num == room[1] || num == room[2]){
      led_mode = 1;
      room_num = num;
      dis.println(num);
      dis.writeDisplay();
      delay(1000);
      turnOnLED();
      num = 0;
      Serial.println(room_num);
    }else{
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
        delay(200);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        delay(200);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        delay(200);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        delay(200);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
      num = 0;
      dis.println(num);
      dis.writeDisplay();
    }
    

  }
  else{
    led_mode = 2;
    dis.println(num);
    dis.writeDisplay();
    Serial.println(num);
    delay(1000);
    _auth();
  }


  
    
}

int pad(){
  int temp;
  char keypressed = myKeypad.getKey();
  if (keypressed != NO_KEY)
  {
    //Serial.println(keypressed);
    if(keypressed == 'a'){
    }else{
    num = num*10;
    num = num + keypressed -48;
    }


  }
}

void turnOnLED(){
  switch(led_mode){
    case 0:
      digitalWrite(11, LOW);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      break;
    case 1:
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);
      digitalWrite(13, HIGH);
      break;
    case 2:
      digitalWrite(11, HIGH);
      digitalWrite(12, HIGH);
      digitalWrite(13, LOW);
      break;
  }
}

void _auth(){
  switch(room_num){
    case 1101:
      if(num == password[0]){
        led_mode = 0;
        turnOnLED();
        Serial.println("Door Unlocked");
        delay(10000);
      }
      else{
        password_faild();
      }
      break;
    case 1728:
      if(num == password[1]){
        led_mode = 0;
        turnOnLED();
        room_num = 0;
        num = 0;
        Serial.println("Door Unlocked");
        delay(10000);
      }
      else{
        password_faild();
      }
      break;
    case 1357:
      if(num == password[2]){
        led_mode = 0;
        turnOnLED();
        room_num = 0;
        num = 0;
        Serial.println("Door Unlocked");
        delay(10000);
      }
      else{
        password_faild();
      }
      break;
      default:
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        digitalWrite(13, LOW);
        delay(200);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        delay(200);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        delay(200);
        digitalWrite(11, LOW);
        digitalWrite(12, LOW);
        delay(200);
        digitalWrite(11, HIGH);
        digitalWrite(12, HIGH);
        delay(10000);

        led_mode = 0;
        room_num = 0;
        num = 0;


        break;
  }
}

void password_faild(){
  led_mode = 1;
  num = 0;
  Serial.println("Door Locked");
  counter++;
  alert(); 
  if(counter == 3){
    digitalWrite(11, HIGH);
    delay(10000);
    Serial.println("Faild to unlock door 3 times");
  }
}

void alert(){
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  digitalWrite(13, LOW);
  delay(200);
  for(int i = 0; i < 3; i++){
    digitalWrite(11, HIGH);
    delay(200);
    digitalWrite(11, LOW);
    delay(200);
  }
  digitalWrite(11, HIGH);
  delay(1000);
}
