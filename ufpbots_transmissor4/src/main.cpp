#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// declare variables
const uint64_t add1 = 0x0a0c0a0c0aLL;
uint8_t payload[10];
int filled;
int sent;

#include "config.h"

RF24 radio(CE, CSN); //ce,csn pin

void setup() {
  //TransmitterConfiguration();
  Serial.begin(38400);

  radio.begin();
  radio.setPayloadSize(10);
  radio.stopListening();
  radio.openWritingPipe(add1);

  filled = -2;
}

void loop() {
  while(Serial.available()) {
    uint8_t ch = Serial.read();

    switch (filled) {
      case -2:
        if (ch == 0x55)
          filled = -1;
        break;

      case -1:
        if (ch == 0xAA) {
          filled = 0;
        } else if (ch == 0x55) {
          filled = -1;
        } else {
          filled = -2;
        }
        break;

      default:
        payload[filled++] = ch;
    }
    if (filled == sizeof(payload)) {
      radio.write(payload, sizeof(payload));
      filled = -2;
    }
  }
}
