
//#define SEL_1 8
//#define SEL_0 7
//#define MODE  2
#define CE  8
#define CSN 7

const uint64_t add1 = 0x0a0c0a0c0aLL;
uint8_t transmit_mode = 0;
uint8_t robo_ID = 1;//0;

void RecieverConfiguration()
{
  /*pinMode(SEL_1, INPUT);
  pinMode(SEL_0, INPUT);
  pinMode(MODE, INPUT);
  //----- Verifica qual o modo ativo
  transmit_mode = digitalRead(MODE);
  //----- Verifica qual o endereço ativo
    if (digitalRead(SEL_0) && digitalRead(SEL_1))
    {
      robo_ID = 3;
    }
    else if (digitalRead(SEL_1)) {
      robo_ID = 2;
    }
    else if (digitalRead(SEL_0)) {
      robo_ID = 1;
    }
    else {
      robo_ID = 0;
    }*/
}



