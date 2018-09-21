#define PWM4  ((input[3]!=0 || input[4]!=0 || input[5]!=0 || input[6]!=0 || input[7]!=0 || input[8]!=0 || input[9]!=0 ))
#define PWM3  ((input[0] >= '0' && input[0] <= '9') && (input[1] >= '0' && input[1] <= '9') && (input[2] >= '0' && input[2] <= '9'))
#define PWM2  ((input[0] >= '0' && input[0] <= '9') && (input[1] >= '0' && input[1] <= '9') && !(input[2] >= '0' && input[2] <= '9'))
#define PWM1  ((input[0] >= '0' && input[0] <= '9') && !(input[1] >= '0' && input[1] <= '9') && !(input[2] >= '0' && input[2] <= '9'))

void printOutput(uint8_t output[])
{
  Serial.print("Sent:  [[ ");
  for (uint8_t i = 0; i < 10; i++)
  {
    Serial.print(output[i]);
    if (i < 9)
      Serial.print(", ");
    else
      Serial.println(" ]]");
  }
}

void swap() {
  int v = 0;
  delay(250);
  if(swapper>3) {
    swapper = 0;
  }
  if(swapper ==0) {
    v = 12;
  }
  else if(swapper ==1) {
    v = 18;
  }
  else if(swapper ==2) {
    v = 20;
  }
  else if(swapper ==3) {
    v = 10;
  }
    output[1] = v;
    output[4] = v;
    output[7] = v;
}

void increasePWM() {
  PWMval++;
  if(PWMval>254){ PWMval = 0; swap(); }
  output[2] = PWMval;
  output[3] = PWMval;
  output[5] = PWMval;
  output[6] = PWMval;
  output[8] = PWMval;
  output[9] = PWMval;
}

