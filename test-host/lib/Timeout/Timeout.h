#ifndef LVH_TIMEOUT_H
#define LVH_TIMEOUT_H

#include <Arduino.h>

class Timeout {
  unsigned long end;
public:
  void start(unsigned duration_ms) {
    end = millis() + duration_ms;
  }
  bool expired() {
    unsigned diff = end - millis();
    constexpr unsigned mask = ~(~0U >> 1);
    return diff & mask;
  }

  Timeout(unsigned duration_ms) {
    start(duration_ms);
  }
};

#endif // LVH_TIMEOUT_H
