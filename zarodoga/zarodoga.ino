#include <Adafruit_TCS34725.h>
#include <Wire.h>
#include "pitches.h"


Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);

#define BUZZER_PIN 10
int melody[] = {NOTE_C4, NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_B4, NOTE_C5};
  int noteDurations[] = {4, 4, 4, 4, 4, 4, 4, 4};
void setup() {
  Serial.begin(9600);
for (int i = 0; i < 8; i++) {
    int duration = 1000 / noteDurations[i];
//    tone(buzzerPin, melody[i], duration);
    delay(duration * 1.1);
  }

 // noTone(buzzerPin);
  delay(1000);
  if (tcs.begin()) {
    Serial.println("Color Sensor found");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  pinMode(BUZZER_PIN, OUTPUT);
}

void loop() {
  uint16_t clear, red, green, blue;

  tcs.setInterrupt(false);
  delay(60);  // take 60 readings per second

  tcs.getRawData(&red, &green, &blue, &clear);

  float lux = tcs.calculateLux(red, green, blue);

  Serial.print("Red: "); Serial.print(red, DEC);
  Serial.print(" Green: "); Serial.print(green, DEC);
  Serial.print(" Blue: "); Serial.print(blue, DEC);
  Serial.print(" Clear: "); Serial.print(clear, DEC);
  Serial.print(" Lux: "); Serial.print(lux, DEC);
  Serial.println();
  delay(1000);

  if (red > green && red > blue) {
    tone(BUZZER_PIN, NOTE_A5, 600); // play note A5 for 500ms
    delay(1000);
  } else if (green > red && green > blue) {
    tone(BUZZER_PIN, NOTE_C6, 300); // play note C6 for 500ms
    delay(1000);
  } else if (blue > red && blue > green) {
    tone(BUZZER_PIN, NOTE_E6, 900); // play note E6 for 500ms
    delay(1000);
  }
}