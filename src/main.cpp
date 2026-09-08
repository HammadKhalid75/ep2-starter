#include <Arduino.h>

#define EXTERNAL_LED_PIN 4 

void setup() {
  Serial.begin(115200);
  delay(300); 

  pinMode(EXTERNAL_LED_PIN, OUTPUT);
  
  Serial.println();
  Serial.println("External LED Blinky Started!");
}

void loop() {
  digitalWrite(EXTERNAL_LED_PIN, HIGH); 
  Serial.println("blink: on");
  delay(500);

  digitalWrite(EXTERNAL_LED_PIN, LOW);  
  Serial.println("blink: off");
  delay(500);
}