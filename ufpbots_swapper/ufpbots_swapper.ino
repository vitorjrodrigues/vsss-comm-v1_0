#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// declare variables
RF24 radio(2, 3); //ce,csn pin
const uint64_t add1 = 0x0a0c0a0c0aLL;
uint8_t output[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t zero[10] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
uint8_t PWMval = 0;
int swapper = 0;

#include "output.h"

void setup() {
  Serial.begin(38400);
  radio.begin();
  radio.stopListening();
  radio.openWritingPipe(add1);
  Serial.println("|>PWM Swapper Ready<|");
  Serial.println("\t!\t Start/Resume Transmission\n\t@\tHalt Transmission");
}

void loop() {
  if (output[0] == 255)
  {
    increasePWM();
    radio.write(output, sizeof(output));
    printOutput(output);
  }
}

void serialEvent()
{
  memset(output, 0, sizeof(output));
  Serial.readBytesUntil('\n', output, sizeof(output));
  if(output[0]!=0)
  {
  if (output[0] == '@')
  {
    output[0] = 0;
    radio.write(zero, sizeof(zero));
    radio.write(zero, sizeof(zero));
    radio.write(zero, sizeof(zero));
    radio.write(zero, sizeof(zero));
    radio.write(zero, sizeof(zero));
    radio.write(zero, sizeof(zero));
    Serial.println("\nHalted");
  }
  else if (output[0] == '!')
  {
    output[0] = 255;
    Serial.println("\nStarted/Resumed");
  }
  else
  {
    Serial.print("\nCommand not detected");
  }
}
}
