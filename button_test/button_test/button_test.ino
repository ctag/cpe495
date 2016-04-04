/*
 * This firmware will print to serial on button actuation.
 */

// Included to keep compatibility between PIO and IDE
#include <Arduino.h>

/**
 * setup() - a poem
 * We do what we must \
 * because they make us.
 */
void setup() {
  Serial.begin(115200);
  pinMode(7, INPUT_PULLUP);
  pinMode(13, OUTPUT);
}

void loop() {
  if (digitalRead(7) == LOW)
  {
    Serial.println("click");
    digitalWrite(13, HIGH);
    delay(200);
    digitalWrite(13, LOW);
  }
  //  else {
  //   Serial.println("no click");
  // }
  // delay(1000);
}
