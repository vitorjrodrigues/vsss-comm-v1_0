#include <ufpbots.h>
#include <Arduino.h>

static uint8_t serial_state = 0;
static serial_packet_t serial_packet;

uint8_t checksum(void *buffer, unsigned size) {
  uint8_t *p = (uint8_t *)buffer;
  uint8_t cs = 0;
  while (size--) cs += *p++;

  return cs;
}

payload_t *serialDecoder(uint8_t data) {
  uint8_t *b = ((uint8_t*)&serial_packet);

  b[serial_state++] = data;

  if (serial_state == 1 && data != MAGIC1) {
    return 0;
  }

  if (serial_state == 2 && data != MAGIC2) {
    serial_state = 0;
    return 0;
  }

  if (serial_state != sizeof(serial_packet))
    return 0;

  serial_state = 0;

  if (checksum(&serial_packet, sizeof(serial_packet)) == 0)
    return &serial_packet.payload;

  return 0;
}
