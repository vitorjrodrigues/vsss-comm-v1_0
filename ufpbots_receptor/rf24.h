#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define CE  8
#define CSN 7

RF24 radio(CE, CSN); //ce,cs pin
const uint64_t add1 = 0x0a0c0a0c0aLL;