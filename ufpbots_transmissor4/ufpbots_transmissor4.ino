#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "config.h"

// declare variables
RF24 radio(CE, CSN); //ce,csn pin
uint8_t payload[10];
int  sent;

void setup() {
  //TransmitterConfiguration();
  radio.begin();
  radio.stopListening();
  radio.openWritingPipe(add1);
}

void loop() {
  if(Serial.available()) {
    memset(payload, 0, sizeof(payload));
    Serial.readBytes(payload, sizeof(payload));
        sent = radio.write(payload,sizeof(payload)); 
        sent = radio.write(payload,sizeof(payload)); 
  }
}
