#include "Arduino.h"

struct fakeInterruptData {
  int pin, mode;
  void (*isr)();
};

static void *fakeInterrupt(void *p) {
  fakeInterruptData *I = (fakeInterruptData *) p;

  const char *modeStr = 0;
  switch (I->mode) {
  case RISING:  modeStr = "rising";  break;
  case FALLING: modeStr = "falling"; break;
  case CHANGE:  modeStr = "both";    break;
  case HIGH:    modeStr = "rising";  break;
  case LOW:     modeStr = "falling"; break;
  default:      delete I; return 0;
  }

  char buff[64];
  sprintf(buff,"/sys/class/gpio/gpio%d/edge", I->pin);
  int fd = open(buff, O_WRONLY);
  if (fd < 0) {
    delete I;
    return 0;
  }
  if (write(fd, modeStr, strlen(modeStr)) < 0) {
    close(fd);
    delete I;
    return 0;
  }
  close(fd);

  sprintf(buff,"/sys/class/gpio/gpio%d/value", I->pin);
  fd = open(buff, O_RDONLY);
  while (true) {
    pollfd fds[1];
    fds[0].fd = fd;
    fds[0].events = POLLIN;
    poll(fds, 1, -1);

    if (fds[0].revents & POLLIN) {
      I->isr();
    }
  }

  return 0;
}

void attachInterrupt(int pin, void (*isr)(), int mode) {
  pthread_t tid;
  fakeInterruptData *I = new fakeInterruptData();
  I->pin = pin;
  I->mode = mode;
  I->isr = isr;
  if (pthread_create(&tid, 0, fakeInterrupt, I) < 0) {
    delete I;
    return;
  }
  pthread_detach(tid);
}
