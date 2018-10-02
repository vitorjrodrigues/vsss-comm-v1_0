#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// declare variables
const uint64_t add1 = 0x0a0c0a0c0aLL;
uint8_t payload[10];
int  sent;

#include "config.h"

RF24 radio(CE, CSN); //ce,csn pin

void setup() {
  //TransmitterConfiguration();
  Serial.begin(38400);
  radio.begin();
  radio.setPayloadSize(10);
  radio.stopListening();
  radio.openWritingPipe(add1);
}

void loop() {
  if(Serial.available()) {
    memset(payload, 0, sizeof(payload));
    Serial.readBytes(payload, sizeof(payload));
    if(payload[0] == 255) {
      sent = radio.write(payload,sizeof(payload)); 
      sent = radio.write(payload,sizeof(payload)); 
    }
  }
  radio.flush_tx();
}
