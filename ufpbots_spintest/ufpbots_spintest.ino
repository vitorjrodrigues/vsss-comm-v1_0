#define ESQ_0  9     // ESQ_0 is the positive PWM of the left wheel
#define ESQ_1 10      // ESQ_1 is the negative PWM of the left wheel
#define DIR_0 6     // DIR_0 is the positive PWM of the right wheel
#define DIR_1 5   // DIR_1 is the negative pwm of the right wheel

void setup() {
  pinMode(ESQ_0, OUTPUT); // set pins to output
  pinMode(ESQ_1, OUTPUT);
  pinMode(DIR_0, OUTPUT);
  pinMode(DIR_1, OUTPUT);
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);
}

void loop() {
  //Controla Motor da Roda Esquerda
  analogWrite(ESQ_0, 100);
  analogWrite(ESQ_1, 0);
  //Controla Motor da Roda Direita
  analogWrite(DIR_0, 0);
  analogWrite(DIR_1, 100);
}
