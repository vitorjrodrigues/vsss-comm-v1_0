#ifndef FAKE_ARDUINO_H
#define FAKE_ARDUINO_H

#include <unistd.h>
#include <poll.h>
#include <fcntl.h>
#include <time.h>
#include <pthread.h>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stdint.h>

inline void delay(int ms) {
  usleep(ms*1000);
}

inline uint32_t millis() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
}
inline uint32_t micros() {
  struct timespec ts;
  clock_gettime(CLOCK_MONOTONIC, &ts);
  return ts.tv_sec * 1000000 + ts.tv_nsec / 1000;
}

#define INPUT 0
#define OUTPUT 1
#define INPUT_PULLUP 2
inline void pinMode(int pin, int mode) {
  char buff[64];
  int fd;

  // Export pin for use as GPIO
  fd = open("/sys/class/gpio/export", O_WRONLY);
  sprintf(buff, "%d", pin);
  write(fd, buff, std::strlen(buff));
  close(fd);

  // Set desired mode, pullup ignored
  sprintf(buff, "/sys/class/gpio/gpio%d/direction", pin);
  fd = open(buff, O_WRONLY);
  if (mode == OUTPUT)
    write(fd, "out", 3);
  else
    write(fd, "in", 2);
  close(fd);
}

#define HIGH 1
#define LOW 0
inline void digitalWrite(int pin, int value) {
  char buff[64];
  sprintf(buff,"/sys/class/gpio/gpio%d/value", pin);
  int fd = open(buff, O_WRONLY);
  write(fd, value ? "1" : "0", 1);
  close(fd);
}

inline int digitalRead(int pin) {
  char buff[64];
  sprintf(buff,"/sys/class/gpio/gpio%d/value", pin);
  int fd = open(buff, O_RDONLY);
  int r = read(fd, buff, 64);
  if (r>=0) {
    buff[r] = 0;
    r = std::atoi(buff);
  } else {
    buff[0] = 0;
    r = 0;
  }
  fprintf(stderr, "digitalRead %d \"%s\" %d\n", fd, buff, r);
  close(fd);
  return r;
}

inline int digitalPinToInterrupt(int interruptPin) {
  return interruptPin;
}

//#define LOW   0
//#define HIGH  1
#define RISING  2
#define FALLING 3
#define CHANGE  4
void attachInterrupt(int pin, void (*isr)(), int mode);

#endif
