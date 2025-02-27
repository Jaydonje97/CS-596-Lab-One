#include <Arduino.h>
#include <TFT_eSPI.h> 
#include <Wire.h>
#include <SPI.h>
#include <Adafruit_CAP1188.h>
#include "driver/gpio.h"

#define MODE 2 // 0 for task 0, 1 for task 1, etc.


#define CLK 25
#define MISO 13
#define MOSI 15
#define CS 33
#define RESET 32


TFT_eSPI tft = TFT_eSPI();  // Invoke library, pins defined in platformio.ini

#if MODE == 1
Adafruit_CAP1188 cap = Adafruit_CAP1188(); // SDA = 21 SCL = 22
#elif MODE == 2
Adafruit_CAP1188 cap = Adafruit_CAP1188(CLK, MISO, MOSI, CS, RESET);
#endif


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  Serial.print("Hello world.\n");

  Serial.print("GPIO Inititialized\n");


  tft.init();
  tft.setRotation(1);
  tft.fillScreen(TFT_BLACK);
  tft.setTextColor(TFT_WHITE, TFT_BLACK);

  tft.drawNumber(4, 0, 0, 6);


  #if MODE > 0
  if (!cap.begin()) {
    Serial.println("CAP1188 not found");
    while (1);
  }
  Serial.println("CAP1188 found!\n");
  #endif

}

void loop() {
  // put your main code here, to run repeatedly:

    #if MODE == 0

    int sec = millis()/1000;
    tft.drawNumber(sec, 0, 0, 6);
    delay(1000);
    
    #else

    uint8_t touched = cap.touched();

    int num_touched = 0;

    while (touched) {
      num_touched += touched & 1;
      touched = touched >> 1;
    }

    tft.drawNumber(num_touched, 0, 0, 6);

    delay(50);

    #endif

}
