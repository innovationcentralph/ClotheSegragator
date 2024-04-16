void checkDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // Measure the echo time
  long duration = pulseIn(echoPin, HIGH);

  // Calculate the distance in centimeters
  long distance_cm = duration / 58.2;

  // Print the distance to the Serial Monitor
  Serial.print("Distance: ");
  Serial.print(distance_cm);
  Serial.println(" cm");

  if (distance_cm <= ultrasonicDistanceThreshold) {
   
    Serial.println("OK " + String(music));
    if (millis() - checkMillis >= checkInterval) {
       player.playMp3Folder(music); //play specific mp3 in SD:/MP3/0004.mp3; File Name(0~65535)
       delay(500);
      Serial.println("Door is Opening");
      servoMainDoor(1);
      checkMillis = millis();
    }
  }

  else {
    checkMillis = millis();
  }

}

void servoWhiteDoor(bool currentState, int rotationVal) {
  if (currentState == 0) {
     servoWhite.write(20); ;    // Move the servo to the 0-degree position
    Serial.println("WHITE DOOR TRIGGER ON");
    delay(rotationVal * 500);       // Wait for 1 second
    servoWhite.write(90);    // Move the servo to the 0-degree position
    Serial.println("WHITE DOOR TRIGGER OFF");
    whiteState = 1;
    delay(1000);
  }
}

void servoColorDoor(bool currentState, int rotationVal) {
  if (currentState == 1) {
     servoWhite.write(160); ;    // Move the servo to the 0-degree position
    Serial.println("WHITE DOOR TRIGGER ON");
    delay(rotationVal * 500);       // Wait for 1 second
    servoWhite.write(90);    // Move the servo to the 0-degree position
    Serial.println("WHITE DOOR TRIGGER OFF");
    whiteState = 0;
    delay(1000);
  }
}

void servoLightDoor(bool currentState, int rotationVal) {
  if (currentState == 0) {
    servoColor.write(20); ;    // Move the servo to the 0-degree position
    Serial.println("LIGHT COLOR DOOR TRIGGER ON");
    delay(rotationVal * 500);       // Wait for 1 second
    servoColor.write(90);    // Move the servo to the 0-degree position
    Serial.println("LIGHT COLOR DOOR TRIGGER OFF");
    colorState = 1;
    delay(1000);
  }
}

void servoDarkDoor(bool currentState, int rotationVal) {
  if (currentState == 1) {
    servoColor.write(160);    // Move the servo to the 0-degree position
    Serial.println("DARK COLOR DOOR TRIGGER ON");
    delay(rotationVal * 500);       // Wait for 1 second
    servoColor.write(90);    // Move the servo to the 0-degree position
    Serial.println("DARK COLOR DOOR TRIGGER OFF");
    colorState = 0;
    delay(1000);
  }
}

void servoMainDoor(int rotationVal) {
  servoDoor.write(160); ;    // Move the servo to the 0-degree position
  Serial.println("MAIN  DOOR TRIGGER ON");
  delay(rotationVal * 500);       // Wait for 1 second
  servoDoor.write(90);    // Move the servo to the 0-degree position
  delay(doorOpenInterval);
  servoDoor.write(20); ;    // Move the servo to the 0-degree position
  delay(rotationVal * 500);       // Wait for 1 second
  servoDoor.write(90);    // Move the servo to the 0-degree position
  Serial.println("MAIN  DOOR TRIGGER OFF");

}
