**MIT License**

Copyright (c) 2025 Douglas Nascimento de Oliveira

---
# 🤖 Robô 2WD Radiocontrolado com Arduino, nRF24L01 e L298N

Este projeto implementa um **robô móvel 2WD (duas rodas motrizes)** controlado remotamente por rádio, utilizando **Arduino**, **módulo nRF24L01**, **ponte H L298N** e um **joystick shield**.  
O sistema foi desenvolvido com foco em **arquitetura limpa**, **controle determinístico dos motores** e **fácil extensibilidade**.

O robô utiliza **controle de velocidade por PWM nos pinos ENA e ENB da ponte H**, garantindo movimentos estáveis, resposta previsível e **curvas suaves por controle diferencial de velocidade**.

---

## 🎮 Funcionalidades

-  Controle remoto via **nRF24L01**
-  Direção por **eixo X do joystick**
-  Aceleração e **ré por botões dedicados**
-  Seletores de **velocidade média e máxima**
-  Curvas suaves por **controle diferencial**
-  **Buzina sonora** acionada pelo botão do analógico (K)

---

## C++ Arquitetura do Projeto

O código foi organizado de forma **modular**, com separação clara de responsabilidades:

-  **Transmissão:** input dos comandos digital e analógico do joystick para a transmissão por rádio
-  **Recepção:** output dos motores e buzzer por recepção dos inputs do módulo transmissor

---

## 🔧 Hardware Utilizado

- 2 Arduino **UNO R3 ATmega328P**
- Ponte H **L298N** (ENA / ENB ativos com controle PWM)
- 2 Módulos **nRF24L01**
- Chassi **2WD** com motores DC
- **Joystick Shield**
- **Buzzer passivo**

---

## 📸 Galeria (em breve)

> Imagens da montagem do chassi, esquema elétrico e controle serão adicionadas futuramente.
