#ifndef DEBUG_MANAGER_H
#define DEBUG_MANAGER_H

#include <Arduino.h>

#define DEBUG_NENHUM 0
#define DEBUG_ERRO 1
#define DEBUG_TUDO 2

void configurarDebug();

void debugErro(const String& mensagem);
void debugInfo(const String& mensagem);

void debugErroSemLinha(const String& mensagem);
void debugInfoSemLinha(const String& mensagem);

int obterNivelDebugAtual();



#endif