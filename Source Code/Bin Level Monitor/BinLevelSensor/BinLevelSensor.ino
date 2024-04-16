#include "Ultrasonic.h"


Ultrasonic Level_White(23, 22);
Ultrasonic Level_Light(26, 27);
Ultrasonic Level_Colored(19, 18);



void setup() {
  Level_White.begin();
  Level_Light.begin();
  Level_Colored.begin();

  pinMode(5, OUTPUT);
  pinMode(17, OUTPUT);
  pinMode(16, OUTPUT);

  digitalWrite(5, LOW);
  digitalWrite(17, LOW);
  digitalWrite(16, LOW);
  

  
Serial.begin(9600);
}

void loop() {
  int level_white = Level_White.getProximity();
  int level_light = Level_Light.getProximity();
  int level_colored = Level_Colored.getProximity();

  if(level_white < 20){
    digitalWrite(5, HIGH);
  }else{
    digitalWrite(5, LOW);
  }

  if(level_light < 20){
    digitalWrite(17, HIGH);
  }else{
    digitalWrite(17, LOW);
  }

  if(level_colored < 20){
    digitalWrite(16, HIGH);
  }else{
    digitalWrite(16, LOW);
  }

  Serial.println("WHITE: " + String(level_white));
  Serial.println("LIGHT: " + String(level_light));
  Serial.println("COLORED: " + String(level_colored));

  delay(2000);

}
