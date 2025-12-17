/*

MIT License

Copyright (c) 2025 Douglas Nascimento de Oliveira

Para detralhes da licença, leia o campo apropriado no repositório original:
https://github.com/DouglasNOliveira/2WD-Arduino-Robot-Radio-Controlled.git

*/

//------------------------------------------------------//
//         Robô Radiocontrolado - TRANSMISSOR          //
//      Ponte H L298N com ENA / ENB ativos (PWM)        //
//              Controle via nRF24L01                   //
//------------------------------------------------------//

#include <RF24.h>

const byte endereco[6] = "31415";

#define CE  9
#define CSN 10

#define eixoX A0

#define botaoA 2   // Acelerador (frente)
#define botaoB 3   // Velocidade máxima
#define botaoC 4   // Ré
#define botaoD 5   // Velocidade média

#define botaoK 8   // Botão do analógico (K)

RF24 radio(CE, CSN);

char comando = 'P';

void setup() {
  Serial.begin(9600);

  radio.begin();
  radio.openWritingPipe(endereco);
  radio.setPALevel(RF24_PA_MIN);
  radio.stopListening();

  pinMode(botaoA, INPUT_PULLUP);
  pinMode(botaoB, INPUT_PULLUP);
  pinMode(botaoC, INPUT_PULLUP);
  pinMode(botaoD, INPUT_PULLUP);
  pinMode(botaoK, INPUT_PULLUP);
}

void loop() {

  int x = analogRead(eixoX);

  if (digitalRead(botaoK) == LOW) {
    char buzina = 'H';
    radio.write(&buzina, sizeof(buzina));
    Serial.println("Buzina!");
    delay(150);
  }

  // Seletores de velocidade
  if (digitalRead(botaoD) == LOW) {
    comando = '2'; // velocidade média
    radio.write(&comando, sizeof(comando));
    delay(200);
  }

  if (digitalRead(botaoB) == LOW) {
    comando = '3'; // velocidade máxima
    radio.write(&comando, sizeof(comando));
    delay(200);
  }

  // Movimento
  bool frente = (digitalRead(botaoA) == LOW);
  bool re     = (digitalRead(botaoC) == LOW);

  if (frente) {
    if (x < 400)      comando = 'E'; // frente + esquerda
    else if (x > 600) comando = 'D'; // frente + direita
    else              comando = 'F'; // frente reto
  }
  else if (re) {
    if (x < 400)      comando = 'L'; // ré + esquerda
    else if (x > 600) comando = 'G'; // ré + direita
    else              comando = 'R'; // ré reto
  }
  else {
    comando = 'P'; // parado
  }

  radio.write(&comando, sizeof(comando));
  Serial.println("Comando enviado: " + String(comando));

  delay(50);
}