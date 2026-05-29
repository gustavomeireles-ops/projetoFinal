#ifndef TV_H
#define TV_H
#include <IRremoteESP8266.h>
#include <IRsend.h>

extern const uint16_t pinIR;
extern IRsend irsend;

extern const uint32_t codigoPower;
extern const uint32_t codigoVolMais;
extern const uint32_t codigoVolMenos;
extern const uint32_t codigoSetaDireita;
extern const uint32_t codigoSetaEsquerda;
extern const uint32_t codigoSetaCima;
extern const uint32_t codigoSetaBaixo;
extern const uint32_t codigoSelect;
extern const uint32_t codigoBack;


void PowerTV();
void VolumeMais();
void VolumeMenos();
void SetaDireita();
void SetaEsquerda();
void SetaCima();
void SetaBaixo();
void Select();
void Back();

#endif