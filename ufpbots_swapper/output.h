uint8_t PWMval = PWMMin;
int v = 12;

void printOutput(uint8_t output[])
{
  Serial.print("Sent: ");
  for (uint8_t i = 1; i < 4; i++)
  {
    Serial.print(output[i]);
    if (i < 3)
      Serial.print(", ");
  }
  Serial.println();
}

void swap() {
  if(swapper >3) swapper = 0;
  if(swapper ==0) v = 12;
  else if(swapper ==1) v = 18;
  else if(swapper ==2) v = 20;
  else if(swapper ==3) v = 10;
  output[1] = v;
  output[4] = v;
  output[7] = v;
  swapper++;
}

void increasePWM() {
  PWMval++;
  if(PWMval>PWMMax){ PWMval = 10; swap(); }
  output[2] = PWMval;
  output[3] = PWMval;
  output[5] = PWMval;
  output[6] = PWMval;
  output[8] = PWMval;
  output[9] = PWMval;
}

