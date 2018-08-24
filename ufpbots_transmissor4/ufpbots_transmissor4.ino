#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "config.h"

// declare variables
RF24 radio(CE, CSN); //ce,csn pin
uint8_t payload[10];

void setup() {
  //TransmitterConfiguration();
  radio.begin();
  radio.stopListening();
  radio.openWritingPipe(add1);
}

void loop() {
  while(Serial.available())
  {
    memset(payload, 0, sizeof(payload));
    Serial.readBytesUntil('\n', payload, sizeof(payload));
    radio.write(payload, sizeof(payload));
  }
}
