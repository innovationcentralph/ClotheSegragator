#include "System_Config.h"
#include "User_Config.h"
#include <ESP32Servo.h>
#include "DFRobotDFPlayerMini.h"

#define rxPin 17// 4
#define txPin 16 //2
#define BAUD_RATE 9600

HardwareSerial softwareSerial(2);

Servo servoDoor;
Servo servo_1;
Servo servo_2;

DFRobotDFPlayerMini player;
int music = 1;

bool whiteState = 0;
bool colorState = 0;


void setup() {
  Serial.begin(9600); /*Set the baudrate to 115200*/

  softwareSerial.begin(9600, SERIAL_8N1, /*rx =*/rxPin, /*tx =*/txPin);
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  if (player.begin(softwareSerial)) {
    Serial.println("OK");
    player.volume(20);
    // Play the first MP3 file on the SD card
     player.playMp3Folder(1);
  } else {
    Serial.println("Connecting to DFPlayer Mini failed!");
    delay(500);
    ESP.restart();
  }


  pinMode(S2, OUTPUT); /*Define S2 Pin as a OUTPUT*/
  pinMode(S3, OUTPUT); /*Define S3 Pin as a OUTPUT*/
  pinMode(sensorVCC, OUTPUT); /*Define S3 Pin as a OUTPUT*/
  pinMode(sensorOut, INPUT); /*Define Sensor Output Pin as a INPUT*/
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  servoDoor.attach(14);  
  servo_1.attach(26);  
  servo_2.attach(33);  

  

}

void loop() {
    getColorValue();
    colorDetected();
    checkDistance();

    servo_1.write(COLOR_POS);
    servo_2.write(COLOR_POS);
    
}

void colorDetected() {
  if (colorValue < whiteColor) {
    servo_1.write(WHITE_POS);
    servo_2.write(WHITE_POS);
    music=2;
  }

  else if (colorValue < LightColor) {
    Serial.println("DRESS = LIGHT COLOR");
    servo_1.write(COLOR_POS);
    servo_2.write(COLOR_POS);
    music=3;    
  }

  else if (colorValue < DarkColor) {
    Serial.println("DRESS = DARK COLOR");
    servo_1.write(BLACK_POS);
    servo_2.write(BLACK_POS);
    music=4;
  }
}
