/*

MIT License

Copyright (c) 2025 Douglas Nascimento de Oliveira

Para detralhes da licença, leia o campo apropriado no repositório original:
https://github.com/DouglasNOliveira/2WD-Arduino-Robot-Radio-Controlled.git

*/

//------------------------------------------------------//
//          Robô Radiocontrolado - RECEPTOR             //
//      Ponte H L298N com ENA / ENB ativos (PWM)        //
//              Controle via nRF24L01                   //
//------------------------------------------------------//

#include <RF24.h>
#include <L298NX2.h>

const byte endereco[6] = "31415"; // endereço RF

// Pinos da ponte H
#define ENA 10
#define IN1 9
#define IN2 8
#define IN3 7
#define IN4 6
#define ENB 5

// Pinos do Rádio
#define CE  4
#define CSN 3

// Pino do Buzzer
#define BUZZER 2

// Objetos
RF24 radio(CE, CSN);

L298NX2 motores(ENA, IN1, IN2, ENB, IN3, IN4); // Importante manter esta ordem

// Variáveis
char comando = 'P';
int velocidade = 150;


// Função buzina
void Buzina() {
  tone(BUZZER, 1500);   // frequência em Hz (1000–3000 é ideal)
  delay(200);
  noTone(BUZZER);
}


//------------------------------------------------------//
//                Funções de Movimento                  //
//------------------------------------------------------//
void Frente() {
  motores.setSpeed(velocidade);
  motores.forward();
}

void Re() {
  motores.setSpeed(velocidade);
  motores.backward();
}

void FrenteDireita() {
  motores.setSpeedA(velocidade);
  motores.setSpeedB(velocidade / 2);
  motores.forward();
}

void FrenteEsquerda() {
  motores.setSpeedA(velocidade / 2);
  motores.setSpeedB(velocidade);
  motores.forward();
}

void ReDireita() {
  motores.setSpeedA(velocidade);
  motores.setSpeedB(velocidade / 2);
  motores.backward();
}

void ReEsquerda() {
  motores.setSpeedA(velocidade / 2);
  motores.setSpeedB(velocidade);
  motores.backward();
}

void Pare() {
  motores.stop();
}


void setup() {
  Serial.begin(9600);
  Pare();

  radio.begin();
  radio.openReadingPipe(1, endereco);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();

  pinMode(BUZZER, OUTPUT);
  digitalWrite(BUZZER, LOW);
}


void loop() {

  if (radio.available()) {
    radio.read(&comando, sizeof(comando));
    Serial.println("Comando recebido: " + String(comando));
  }

  switch (comando) {

    case 'H':   // Buzina
    Buzina();
    break;

    case '2':   // Velocidade média
      velocidade = 150;
      break;

    case '3':   // Velocidade máxima
      velocidade = 255;
      break;

    case 'F':   // Frente
      Frente();
      break;

    case 'R':   // Ré
      Re();
      break;

    case 'D':   // Frente + Direita
      FrenteDireita();
      break;

    case 'E':   // Frente + Esquerda
      FrenteEsquerda();
      break;

    case 'G':   // Ré + Direita
      ReDireita();
      break;

    case 'L':   // Ré + Esquerda
      ReEsquerda();
      break;

    default:    // Parar
      Pare();
      break;
  }
}