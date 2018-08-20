#include <SPI.h>
#include <RF24.h>
#include <nRF24L01.h>

#define CE  8
#define CSN 7

RF24 radio(CE, CSN); //ce,cs pin
const uint64_t add1 = 0x0a0c0a0c0aLL;

#include "config.h"
#include "bridgemap.h"
#include "print.h"

// payload storage
uint8_t RECEBE[10];  // Variavel a receber a transmissao em RF

void setup() {
  //----- Define fisicamente o endereço do robô
  //pinMode(2,INPUT);//para robo 1
  //pinMode(3,INPUT);//para robo 2

  //----- Configura os pinos de PWM para a ponte H (ver bridgemap.h para definicao)
  setPWM();

  //----- Configura a serial para comunicação com o robô
  Serial.begin(9600);
  radio.begin();
  radio.setPALevel(RF24_PA_LOW);
  radio.openReadingPipe(1, add1);
  radio.startListening();

  //----- Configura os robos para iniciarem parados
  STOP();

  //----- Inicia o driver
  pinMode(2, OUTPUT);
  digitalWrite(2, HIGH);

  //----- Reciever can operate now
  Serial.println("Reciever Ready!\n");
}

void loop() {
  //----- Recebe configuracoes para modo de tranmissao e ID (ver config.h para definicao)
  //RecieverConfiguration();  // Desativado enquanto as entradas seletoras nao estiverem sendo usadas

  //----- Recebe sinal transmitido em RF se disponivel
  if (radio.available() == true)
  {
    memset(RECEBE, ' ', sizeof(RECEBE));
    radio.read(RECEBE, sizeof(RECEBE));
    printMode();
    printPayload(RECEBE);
  }

  //---------------------------------------------------------------------
  //Laço para controle do robô
  //---------------------------------------------------------------------
  if (robo_ID > 0) // aqui vai ler o buffer do robo 1, 2 ou 3
  {
    //----- Switch para as logicas correspondentes (ver bridgemap.h para referencia)
    //----- A posicao no vetor recebido a ser enviada depende do id do robo
    switch (RECEBE[(1 + 3 * (robo_ID - 1))]) {
      case 12: //robo recebe logica para ir pra frente - F
        FRWD(robo_ID, RECEBE);
        break;
      case 10: //robo recebe logica para girar AntiHorario - AH
        TLFT(robo_ID, RECEBE);
        break;
      case 20: //robo recebe logica para girar Horario - H
        TRGT(robo_ID, RECEBE);
        break;
      case 18: //robo recebe logica para ir pra tras - T
        BKWD(robo_ID, RECEBE);
        break;
      //----- Debug modes
      case 64: // todos os robos andam pra frente em velocidade máxima
        onTest();
        break;
      case 128: // todos os robos param imediatamente
        offTest();
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
