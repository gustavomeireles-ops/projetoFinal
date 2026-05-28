
#include <Arduino.h>
#include "wifimanager.h"
#include "MQTTmanager.h"
#include "DebugManager.h"

#include <ArduinoJson.h>

const char TOPICO_COMANDO[] = "senai134/diasHeitor/esp32/televisao";

void tratarMensagemRecebida(const char* topico, const String& mensagem);
void controlarJsonTelevisao(int ligardesligar, int aumentar, int diminuir, int compartilharTela);
void tratarJsonComando(const String& mensagem);

int ligardesligar = 0; //0 não faz NADA! por isso inicializei com 0 (boa prática)
int aumentar = 0;
int diminuir = 0;

void setup()
{
  configurarDebug();
  conectarWifi();
  configurarMQTT();
  registrarCallbackMensagem(tratarMensagemRecebida);
  conectarMQTT();
}

void loop() 
{
  garantirWifiConectado();
  garantirMQTTConectado();
  loopMQTT();
}

void tratarMensagemRecebida(const char* topico, const String& mensagem)
{
  debugInfo("=======================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("=======================");
  
  if(topico == nullptr)
  {
    debugErro("Tópico MQTT inválido");
    return;
  }
  
  debugInfo("Tópico: " + String(topico));
  debugInfo("Mensagem: " + mensagem);

  if(strcmp(topico, TOPICO_COMANDO) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }
  debugErro("Tópico não tratado: " + String(topico));
}

void controlarJsonTelevisao(int ligardesligar, int aumentar, int diminuir)
{
  //TODO: adicionar aqui o código da televisao! com os ifs! para realmente poder controlar a televisão, assim os valores que eu der apra a variável são os únicos que vão responder aos comandos da televisão.

  debugInfo("Televisão configurada");
  debugInfo("power: " + String(ligardesligar));
  debugInfo("upV: " + String(aumentar));
  debugInfo("downV: " + String(diminuir));
}

// & = referência
void tratarJsonComando(const String& mensagem)
{
  JsonDocument doc;
  DeserializationError erro = deserializeJson(doc, mensagem);
  if(erro)
  {
    debugErro("Erro ao interpretar o Json Enviado.");
    debugErro(erro.c_str());
    return;
  }

  if(doc["televisao"].is<JsonObject>())
  {
      ligardesligar = doc["televisao"]["power"].as<int>(); //lIGAR DESLIGAR SE TORNA IGUAL AO JSON POWER E ASSIM EM DIANTE.
      aumentar = doc["televisao"]["upV"].as<int>();
      diminuir = doc["televisao"]["downV"].as<int>();

      controlarJsonTelevisao(ligardesligar, aumentar, diminuir);
  }

  if(ligardesligar == 1) //*mudei aqui os valores
  {
    publicarMensagem("senai/esp32/televisao", "Estado da TV trocado com sucesso");
  }
  if(aumentar == 2)
  {
    publicarMensagem("senai/esp32/televisao", "Volume aumentado com sucesso");
  }
  if(diminuir == 3)
  {
    publicarMensagem("senai/esp32/televisao", "Volume diminuido com sucesso");
  }
}
