#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

// payload storage
uint8_t RECEBE[10]; // Variavel para receber a transmissao em RF
uint8_t OUT[10];    // Variavel para enviar dados validados

// error verification variables
int err = 0;
int e = 0;

#include "config.h"
#include "bridgemap.h"
#include "print.h"

//Define CE and CSN pins, respectively
RF24 radio(CE, CSN); 

void setup() {
  //----- Configura os pinos de PWM para a ponte H (ver bridgemap.h para definicao)
  setPWM();

  //----- Configura a serial para comunicação com o robô
  Serial.begin(115200);
  memset(OUT, 0, sizeof(OUT));
  radio.begin();
  radio.setPayloadSize(10);
  radio.openReadingPipe(1, add1);
  radio.startListening();

  //----- Configura os robos para iniciarem parados
  STOP();

  //----- Inicia o driver
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  //----- Reciever can oerrate now
  Serial.println("Reciever Ready!\n");
}

void loop() {
  //----- Recebe configuracoes para modo de tranmissao e ID (ver config.h para definicao)
  //RecieverConfiguration();  // Desativado enquanto as entradas seletoras nao estiverem sendo usadas

  //----- Recebe sinal transmitido em RF se disponivel
  if (radio.available() == true)
  {
    memset(RECEBE, 0, sizeof(RECEBE));
    radio.read(RECEBE, sizeof(RECEBE));
    checkPayload(RECEBE, sizeof(RECEBE));
    if(e==err){ 
      printPayload(OUT, sizeof(OUT));     
      Serial.println("");
    }
    e = err;
  }
  //---------------------------------------------------------------------
  //Laço para controle do robô
  //---------------------------------------------------------------------
  if (robo_ID > 0) // aqui vai ler o buffer do robo 1, 2 ou 3
  {
    //----- Switch para as logicas correspondentes (ver bridgemap.h para referencia)
    //----- A posicao no vetor recebido a ser enviada depende do id do robo
    switch (OUT[(1 + 3 * (robo_ID - 1))]) {
      case 12: //robo recebe logica para ir pra frente - F
        FRWD(robo_ID, OUT);
        break;
      case 10: //robo recebe logica para girar AntiHorario - AH
        TLFT(robo_ID, OUT);
        break;
      case 20: //robo recebe logica para girar Horario - H
        TRGT(robo_ID, OUT);
        break;
      case 18: //robo recebe logica para ir pra tras - T
        BKWD(robo_ID, OUT);
        break;
      default: //Mantem o robo parado
        STOP();
    }
  }
  else // aqui vai ler o buffer do robo 0 (robo 0 e padrao, significa que nenhum robo esta selecionado)
  {
    STOP();
  }
}
