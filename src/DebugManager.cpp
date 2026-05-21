#include <Arduino.h>
#include "DebugManager.h"
#include "secrets.h"

int nivelDebugAtual = DEBUG_NIVEL_INICIAL;

void debugErro(const String&mensagem){
    if(nivelDebugAtual >= DEBUG_ERRO){
        Serial.println("[ERRO] ");
        Serial.println(mensagem);
    }
}
void debugErroSemLinha(const String& mensagem){
    if(nivelDebugAtual >= DEBUG_ERRO){
        Serial.println(mensagem);
    }
}
void debugInfo(const String&mensagem){
    if(nivelDebugAtual >= DEBUG_TUDO){
        Serial.println("[INFO] ");
        Serial.println(mensagem);
    }
}
void debugInfoSemLinha(const String& mensagem){
    if(nivelDebugAtual >= DEBUG_TUDO){
        Serial.println(mensagem);
    }
}
void configurarDebug(){
    Serial.begin(9600);
    delay(1000);

    pinMode(PINO_HABILITA_DEBUG_COMPLETO, INPUT_PULLUP);

    if(digitalRead(PINO_HABILITA_DEBUG_COMPLETO) == LOW){
        nivelDebugAtual = DEBUG_TUDO;
    }
    else{
        nivelDebugAtual = DEBUG_NIVEL_INICIAL;
    }

    for(int i = 0; i < 5; i++){
        debugInfo("");
    }
    debugInfo("=================");
    debugInfo(" ESP32 Iniciado");
    debugInfo(" Sistema de debug ativo");
    if(nivelDebugAtual == DEBUG_ERRO){
        debugInfo(" Debug iniciado em modo apenas erro");
    }
    else{
        debugInfo(" Debug iniciado em modo completo");
    }
    debugInfo("=================");
}

//TODO: Criar a função obterNivelDebugAtual