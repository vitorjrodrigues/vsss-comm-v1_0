#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <printf.h>

#include "output.h"

// declare variables
RF24 radio(2, 3); //ce,csn pin
const uint64_t add1 = 0x0a0c0a0c0aLL;
uint8_t input[17];
uint8_t output[10] = {0, 12, 0, 0, 20, 50, 50, 20, 50, 50};
uint8_t zero[10] {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

void setup() {
  Serial.begin(9600);
  radio.begin();
  printf_begin();
  radio.stopListening();
  radio.openWritingPipe(add1);
  //radio.printDetails(); //check if there is an error appear when you try to connect nRF to arduino
  Serial.println("|>CommTest Ready<|\n Radio is ON");
  Serial.println("\t!\t Start/Resume Transmission\n\t@\tHalt Transmission");
  Serial.print("Insert your desired PWM value (0 to 255)");
}

void loop() {
  if (output[0] == 255)
  {
    radio.write(output, sizeof(output));
    printOutput(output);
  }
}

void serialEvent()
{
  memset(input, 0, sizeof(input));
  Serial.readBytesUntil('\n', input, sizeof(input));
  if(input[0]!=0)
  {
  if (input[0] == '@')
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
  else if (input[0] == '!')
  {
    output[0] = 255;
    Serial.println("\nStarted/Resumed");
  }
    else if (PWM4)
  {
    Serial.print("\nThis is not a valid input");
  }
  else if (PWM3)
  {
    if ((input[0] >= '2' && ( input[1] > '5' || (input[1] == '5' && input[2] > '5'))))
    {
      output[2] = 255;
      Serial.print("\nMaximum PWM is 255!!");
    }
    else
    {
      output [2] = (input[0] - 48) * 100 + (input[1] - 48) * 10 + (input[2] - 48);
    }
    output [3] = output[2];
    Serial.print("\nPWM is now ");
    Serial.print(output[2]);
  }
  else if (PWM2)
  {
    output [2] = (input[0] - 48) * 10 + (input[1] - 48);
    output [3] = output[2];
    Serial.print("\nPWM is now ");
    Serial.print(output[2]);
  }
  else if (PWM1)
  {
    output [2] = (input[0] - 48);
    output [3] = output[2];
    Serial.print("\nPWM is now ");
    Serial.print(output[2]);
  }
  }
  else
  {
    Serial.print("\nCommand not detected");
  }
}
