#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include "TV.h"

const uint32_t codigoPower = 0x20DF10EF;
const uint32_t codigoVolMais = 0x20DF40BF;
const uint32_t codigoVolMenos = 0x20DFC03F;
const uint32_t codigoSetaDireita = 0x20DF609F;
const uint32_t codigoSetaEsquerda = 0x20DFE01F;
const uint32_t codigoSetaCima = 0x20DF02FD;
const uint32_t codigoSetaBaixo = 0x20DF827D;
const uint32_t codigoSelect = 0x20DF22DD;
const uint32_t codigoBack = 0x20DF14EB;

int bits = 32;  // é o numero de bits que o controle remoto utiliza para enviar os códigos, no caso da TV é 32 bits.

const uint16_t pinIR = 1;
IRsend irsend(pinIR);

//?Comandos de Tela
void PowerTV()
{
  irsend.sendNEC(codigoPower, bits); 
  debugInfo("TV Ligada/Desligada"); 
}

void VolumeMais()
{
  irsend.sendNEC(codigoVolMais, bits);
  debugInfo("Volume Aumentado");
}

void VolumeMenos()
{
  irsend.sendNEC(codigoVolMenos, bits);
  debugInfo("Volume Diminuido");
}

//?Comandos Ok, Voltar e Direcionais
void SetaDireita()
{
  irsend.sendNEC(codigoSetaDireita, bits);
  debugInfo("Seta Direita");
}

void SetaEsquerda()
{
  irsend.sendNEC(codigoSetaEsquerda, bits);
  debugInfo("Seta Esquerda");
}

void SetaCima()
{
  irsend.sendNEC(codigoSetaCima, bits);
  debugInfo("Seta Cima");
}

void SetaBaixo()
{
  irsend.sendNEC(codigoSetaBaixo, bits);
  debugInfo("Seta Baixo");
}   

void Select()
{
  irsend.sendNEC(codigoSelect, bits);
  debugInfo("Select");
}

void Back()
{
  irsend.sendNEC(codigoBack, bits);
  debugInfo("Back");
}