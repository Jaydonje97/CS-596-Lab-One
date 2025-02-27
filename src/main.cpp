#include <Arduino.h>
#include <TFT_eSPI.h>

// put function declarations here:

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial.println("Running...");
}

void loop() {
  // put your main code here, to run repeatedly:

    unsigned long secondsElapsed = (millis() / 1000);
    Serial.print("Time Elapsed: "), Serial.println(secondsElapsed);
    
    delay(1000);
}

// put function definitions here:
