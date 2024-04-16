#include "System_Config.h"
#include "User_Config.h"
#include <ESP32Servo.h>
#include "DFRobotDFPlayerMini.h"

#define rxPin 17// 4
#define txPin 16 //2
#define BAUD_RATE 9600

HardwareSerial softwareSerial(2);

Servo servoDoor;
Servo servoWhite;
Servo servoColor;

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

  servoDoor.attach(14);  // Attach the servo to pin 2 on the ESP32
  servoWhite.attach(26);  // Attach the servo to pin 2 on the ESP32
  servoColor.attach(33);  // Attach the servo to pin 2 on the ESP32

}

void loop() {
    getColorValue();
    colorDetected();
    checkDistance();
}

void colorDetected() {
  if (colorValue < whiteColor) {
    servoWhiteDoor(whiteState, 1);
    music=2;
  }

  else if (colorValue < LightColor) {
    Serial.println("DRESS = LIGHT COLOR");
    servoColorDoor(whiteState, 1);
    servoLightDoor(colorState, 1);
    music=3;    
  }

  else if (colorValue < DarkColor) {
    Serial.println("DRESS = DARK COLOR");
    servoColorDoor(whiteState, 1);
    servoDarkDoor(colorState, 1);
    music=4;
  }
}

void getColorValue() {
  Red = getRed();
  delay(100); /*wait a 200mS*/
  Green = getGreen();
  delay(200); /*wait a 200mS*/
  Blue = getBlue();
  delay(200); /*wait a 200mS*/
  Serial.print("Red Freq = ");
  Serial.print(Red); /*Print Red Color Value on Serial Monitor*/
  Serial.print("   ");
  Serial.print("Green Freq = ");
  Serial.print(Green); /*Print Green Color Value on Serial Monitor*/
  Serial.print("   ");
  Serial.print("Blue Freq = ");
  Serial.println(Blue); /*Print Blue Color Value on Serial Monitor*/
  colorValue = calculateColor(Red, Green, Blue);
  Serial.println("Color Value = " + String(colorValue));
}

int getRed() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  Frequency = pulseIn(sensorOut, LOW); /*Get the Red Color Frequency*/
  return Frequency;
}

int getGreen() {
  digitalWrite(S2, HIGH);
  digitalWrite(S3, HIGH);
  Frequency = pulseIn(sensorOut, LOW); /*Get the Green Color Frequency*/
  return Frequency;
}

int getBlue() {
  digitalWrite(S2, LOW);
  digitalWrite(S3, HIGH);
  Frequency = pulseIn(sensorOut, LOW); /*Get the Blue Color Frequency*/
  return Frequency;
}

float calculateColor(float A, float B, float C) {
  float result = sqrt(pow(A, 2) + pow(B, 2) + pow(C, 2));
  return result;
}
