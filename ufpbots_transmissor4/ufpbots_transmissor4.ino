#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include "config.h"

// declare variables
RF24 radio(CE, CSN); //ce,csn pin
const uint64_t add1 = 0x0a0c0a0c0aLL;
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
