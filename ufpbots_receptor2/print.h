void printMode()
{
    //----- Shows corresponding robot ID and operation mode (for debug purposes only)
    Serial.print("Hi, I am Robot ");
    Serial.println(robo_ID);
    Serial.print("Recieving data as ");
    if (transmit_mode == 0)
    {
      Serial.println("RF");
    }
    else
    {
      Serial.println("IR");
    }
}

void printPayload(uint8_t* payload, int sz)
{
    //----- Prints the payload recieved via radio through the serial port
    Serial.print("Recieved: [[ ");
    for (uint8_t i = 0; i < sz; i++)
    {
      Serial.print(payload[i]);
      if (i < sz-1)
        Serial.print(", ");
      else
        Serial.println(" ]]");
    }
    Serial.print("My velocities: [[ ");
    Serial.print(payload[(2 + 3 * (robo_ID - 1))]);
    Serial.print(", ");
    Serial.print(payload[(3 + 3 * (robo_ID - 1))]);
    Serial.println("  ]]");
}
