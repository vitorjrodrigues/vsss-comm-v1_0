#include <iostream>
#include <iomanip>
using namespace std;

#include <ufpbots.h>
#include <Arduino.h>
#include <SoftwareSerial.h>

SoftwareSerial Serial("/dev/ttyUSB0");

int main(int argc, char *argv[]) {
  if (argc != 4 && argc != 7) {
    cout << argv[0] <<" <bot> <left> <right>" << endl;
    cout << "0 <= bot <= 2" << endl;
    cout << "-127 <= left <= +127" << endl;
    cout << "-127 <= right <= +127" << endl;
    cout << endl;
    cout << argv[0] << " <left_0> <right_0> <left_1> <right_1> <left_2> <right_2>" << endl;
    cout << endl;
    return 0;
  }

  int n[argc];
  for (int i=1; i<argc; i++)
    n[i] = atoi(argv[i]);

  Serial.begin(1200);

  serial_packet_t P;
  memset(&P, 0, sizeof(P));
  P.magic_1 = MAGIC1;
  P.magic_2 = MAGIC2;

  if (argc == 4) {
    int bot = n[1];
    P.payload.cmd[bot].left  = n[2];
    P.payload.cmd[bot].right = n[3];
  } else {
    P.payload.cmd[0].left  = n[1];
    P.payload.cmd[0].right = n[2];
    P.payload.cmd[1].left  = n[3];
    P.payload.cmd[1].right = n[4];
    P.payload.cmd[2].left  = n[5];
    P.payload.cmd[2].right = n[6];
  }

  P.checksum = -checksum(&P, sizeof(P));

  Serial.write((char*)&P, sizeof(P));

  return 0;
}
