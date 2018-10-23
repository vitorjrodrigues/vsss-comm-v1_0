#include <ufpbots.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define RADIO_CS 10
#define RADIO_CE 9

//Define CE and CSN pins, respectively
RF24 radio(RADIO_CE, RADIO_CS);

void setup() {
  Serial.begin(1200);
  radio.begin();
  radio.setPayloadSize(sizeof(payload_t));
  radio.stopListening();
  radio.openWritingPipe(RADIO_ADDRESS);
}

void loop() {
  if (Serial.available()) {
    payload_t *payload = serialDecoder(Serial.read());
    if (payload) {
      radio.write(payload, sizeof(payload_t));
    };
  }
}
