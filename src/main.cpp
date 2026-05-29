
#include <Arduino.h>
#include "wifimanager.h"
#include "MQTTmanager.h"
#include "DebugManager.h"

#include <ArduinoJson.h>

const char TOPICO_RECEBER[] = "senai134/diasHeitor/esp32/televisao";
const char TOPICO_PUBLICAR[] = "senai/esp32/televisao";

void tratarMensagemRecebida(const char* topico, const String& mensagem);
void controlarJsonTelevisao(int ligardesligar, int aumentar, int diminuir, int compartilharTela);
void tratarJsonComando(const String& mensagem);

int comando = 0;

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

  if(strcmp(topico, TOPICO_RECEBER) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }
  /*if(strcmp(topico, TOPICO_PUBLICAR) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }*/
  debugErro("Tópico não tratado: " + String(topico));
}

void controlarJsonTelevisao(int comando)
{
  debugInfo("Televisão configurada");
  debugInfo("Comando: " + String(comando));
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
      comando = doc["televisao"]["comando"].as<int>();
  }
      controlarJsonTelevisao(comando);

  //*MVP
  if(comando == 1)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Estado da TV trocado com sucesso");
  }
  if(comando == 2)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Volume aumentado com sucesso");
  }
  if(comando == 3)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Volume diminuido com sucesso");
  }

//*ADICIONAIS
  if(comando == 4)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Direção para cima acionada com sucesso");
  }
  if(comando == 5)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Direção para baixo acionada com sucesso");
  }
  if(comando == 6)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Direção para esquerda acionada com sucesso");
  }
  if(comando == 7)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Direção para direita acionada com sucesso");
  }
  if(comando == 8)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Botão Select acionado com sucesso");
  }
  if(comando == 9)
  {
    publicarMensagem(TOPICO_PUBLICAR, "Botão Voltar acionado com sucesso");
  }
}