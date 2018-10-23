#ifndef FAKEDUINO_SOFTWARE_SERIAL_H
#define FAKEDUINO_SOFTWARE_SERIAL_H

#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <cstdio>
#include <cstring>
#include <stdint.h>
#include <poll.h>

class SoftwareSerial {
  int fd;
  bool debug;

public:
  operator bool() {
    return fd >= 0;
  }

  SoftwareSerial(const char *name, bool debug_ = false) {
    fd = open(name, O_RDWR | O_NOCTTY | O_NDELAY);
    debug = debug_;
  }

  ~SoftwareSerial() {
    if (fd >= 0)
      close(fd);
  }

  void begin(int baud) {
    unsigned B = 0;
    switch (baud) {
      case 0: B = B0; break;
      case 50: B = B50; break;
      case 75: B = B75; break;
      case 110: B = B110; break;
      case 134: B = B134; break;
      case 150: B = B150; break;
      case 200: B = B200; break;
      case 300: B = B300; break;
      case 600: B = B600; break;
      case 1200: B = B1200; break;
      case 1800: B = B1800; break;
      case 2400: B = B2400; break;
      case 4800: B = B4800; break;
      case 9600: B = B9600; break;
      case 19200: B = B19200; break;
      case 38400: B = B38400; break;
      case 57600: B = B57600; break;
      case 115200: B = B115200; break;
      case 230400: B = B230400; break;
      case 460800: B = B460800; break;
      case 500000: B = B500000; break;
      case 576000: B = B576000; break;
      case 921600: B = B921600; break;
      case 1000000: B = B1000000; break;
      case 1152000: B = B1152000; break;
      case 1500000: B = B1500000; break;
      case 2000000: B = B2000000; break;
      case 2500000: B = B2500000; break;
      case 3000000: B = B3000000; break;
      case 3500000: B = B3500000; break;
      case 4000000: B = B4000000; break;
    }
    if (!B) return;

    struct termios options;
    tcgetattr(fd, &options);
    cfsetispeed(&options, B);
    cfsetospeed(&options, B);
    options.c_cflag &= ~(CSTOPB | CSIZE | PARENB | CRTSCTS);
    options.c_cflag |= CS8 | CREAD | CLOCAL;

    options.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    options.c_iflag &= ~(IXON | IXOFF | IXANY);
    options.c_oflag &= ~(OPOST);

    tcsetattr(fd, TCSANOW, &options);
  }

  bool available() {
    struct pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;
    poll(fds, 1, 0);
    return fds[0].revents & POLLIN;
  }

  bool isListening() {
    return true;
  }

  bool overflow() {
    return false;
  }

  int peek() {
    // totally unsuported, die!
    throw 0;
  }

  int read() {
    if (!available())
      return -1;

    unsigned char ch;
    ::read(fd, &ch, 1);

    if (debug) {
       ::write(STDERR_FILENO, "SSR -> ", 7);
       ::write(STDERR_FILENO, &ch, 1);
       ::write(STDERR_FILENO, "\n", 1);
     }
    return ch;
  }

  void listen() {
    // Do nothing, always listening.
  }

  ssize_t write(uint8_t ch) {
    if (debug) {
      ::write(STDERR_FILENO, "SSR <- ", 7);
      ::write(STDERR_FILENO, &ch, 1);
      ::write(STDERR_FILENO, "\n", 1);
    }
    return ::write(fd, &ch, 1);
  }

  ssize_t write(const char *str) {
    if (debug) {
      ::write(STDERR_FILENO, "SSR <- ", 7);
      ::write(STDERR_FILENO, str, strlen(str));
      ::write(STDERR_FILENO, "\n", 1);
    }
    return ::write(fd, str, std::strlen(str));
  }

  ssize_t write(void *buff, size_t size) {
    if (debug) {
      ::write(STDERR_FILENO, "SSR <- ", 7);
      ::write(STDERR_FILENO, buff, size);
      ::write(STDERR_FILENO, "\n", 1);
    }
    return ::write(fd, buff, size);
  }

  void print(int i, int base=10) {
    char buff[64];

    switch(base) {
    case 8:
      sprintf(buff, "%o", i);
      break;

    case 16:
      sprintf(buff, "%x", i);
      break;

    default:
      sprintf(buff, "%d", i);
    }

    write(buff);
  }

  void print(float f) {
    char buff[16];
    sprintf(buff, "%f", f);
    write(buff);
  }

  void print(char ch) {
    char buff[16];
    sprintf(buff, "%c", ch);
    write(buff);
  }

  void print(const char *str) {
    write(str);
  }

  void println() {
    print('\n');
  }

  template <class arg>
  void println(arg a) {
    print(a);
    println();
  }
};


#endif
