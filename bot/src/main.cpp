#include <ufpbots.h>
#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define BOT_ID 0

#define MOTOR_ENABLE 2
#define PWM_LEFT_FWD 9
#define PWM_LEFT_BWD 10
#define PWM_RIGHT_FWD 6
#define PWM_RIGHT_BWD 5
#define RADIO_CS 7
#define RADIO_CE 8

payload_t payload;

void setPwm(int8_t left, int8_t right) {
  // left and right are [-127..+127] for max backward to max forward.
  // -2 * -128 would overflow a byte.
  if (left == -128) {
    left++;
  }
  if (left >= 0) {
    analogWrite(PWM_LEFT_FWD, +2*left);
    analogWrite(PWM_LEFT_BWD, 0);
  } else {
    analogWrite(PWM_LEFT_FWD, 0);
    analogWrite(PWM_LEFT_BWD, -2*left);
  }

  if (right == -128) {
    right++;
  }
  if (right >= 0) {
    analogWrite(PWM_RIGHT_FWD, +2*right);
    analogWrite(PWM_RIGHT_BWD, 0);
  } else {
    analogWrite(PWM_RIGHT_FWD, 0);
    analogWrite(PWM_RIGHT_BWD, -2*right);
  }
}

void setPins() {
  pinMode(MOTOR_ENABLE, OUTPUT);
  digitalWrite(MOTOR_ENABLE, 0);
  pinMode(PWM_LEFT_FWD, OUTPUT);
  pinMode(PWM_LEFT_BWD, OUTPUT);
  pinMode(PWM_RIGHT_FWD, OUTPUT);
  pinMode(PWM_RIGHT_BWD, OUTPUT);
  setPwm(0,0);
}

//Define CE and CSN pins, respectively
RF24 radio(RADIO_CE, RADIO_CS);

void setup() {
  //----- Configura os robos para iniciarem parados
  setPins();
  digitalWrite(MOTOR_ENABLE, HIGH);

  // Remote control inputs
  Serial.begin(1200);
  radio.begin();
  radio.setPayloadSize(sizeof(payload_t));
  radio.openReadingPipe(1, RADIO_ADDRESS);
  radio.startListening();
}

void loop() {
  if (radio.available()) {
    radio.read(&payload, sizeof(payload));
    setPwm(payload.cmd[BOT_ID].left, payload.cmd[BOT_ID].right);
  }

  if (Serial.available()) {
    payload_t *payload = serialDecoder(Serial.read());
    if (payload) setPwm(
      payload->cmd[BOT_ID].left,
      payload->cmd[BOT_ID].right
    );
  }
}
