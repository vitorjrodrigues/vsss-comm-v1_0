#ifndef UFPBOTS_H
#define UFPBOTS_H

#include <stdint.h>
#include <sys/types.h>

#define RADIO_ADDRESS 0x0a0c0a0c0aLL

struct payload_t {
  struct {
    int8_t left;
    int8_t right;
  } cmd[3];
};

#define MAGIC1 0x55
#define MAGIC2 0xAA
struct serial_packet_t {
  uint8_t magic_1;
  uint8_t magic_2;
  payload_t payload;
  uint8_t checksum;
};

uint8_t checksum(void *buffer, unsigned size);

payload_t *serialDecoder(uint8_t data);

#endif
