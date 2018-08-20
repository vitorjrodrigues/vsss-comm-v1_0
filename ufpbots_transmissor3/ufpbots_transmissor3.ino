#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

#include "config.h"

// declare variables
RF24 radio(CE, CSN); //ce,csn pin
const uint64_t add1 = 0x0a0c0a0c0aLL;
uint8_t payload[10];

void printOutput(uint8_t output[]);

void setup() {
  //TransmitterConfiguration();
  Serial.begin(9600);
  radio.begin();
  printf_begin();
  radio.stopListening();
  radio.openWritingPipe(add1);
  Serial.println("|>Transmitter Initialized<|");
}

void loop() {
  while(Serial.available())
  {
    memset(payload, 0, sizeof(payload));
    Serial.readBytesUntil('\n', payload, sizeof(payload));
    radio.write(payload, sizeof(payload));
    printOutput(payload);
  }
}

void printOutput(uint8_t output[])
{
  Serial.print("\nSent:  [[ ");
  for (uint8_t i = 0; i < 10; i++)
  {
    Serial.print(output[i]);
    if (i < 9)
      Serial.print(", ");
    else
      Serial.println(" ]]");
  }
}
