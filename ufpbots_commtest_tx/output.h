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




