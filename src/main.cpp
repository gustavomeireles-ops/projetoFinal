
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
int cima = 0;
int baixo = 0;
int esquerda = 0;
int direita = 0;
int selectButton = 0;
int voltar = 0;

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

void controlarJsonTelevisao(int ligardesligar, int aumentar, int diminuir,int cima,int baixo, int esquerda, int direita, int select, int voltar )
{
  ligardesligar = constrain(ligardesligar, 0, 0);
  aumentar = constrain(aumentar, 1, 1);
  diminuir = constrain(diminuir, 2, 2);

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
    if(!doc["televisao"]["power"].is<int>() && !doc["televisao"]["upV"].is<int>() && !doc["televisao"]["downV"].is<int>())
    {
      debugErro("Json inválido. Use televisao.power, televisao.upV, televisao.downV");
      return;
    }
    else
    {
      ligardesligar = doc["televisao"]["power"].as<int>();
      aumentar = doc["televisao"]["upV"].as<int>();
      diminuir = doc["televisao"]["downV"].as<int>();
      cima = doc["televisao"]["cima"].as<int>();
      baixo = doc["televisao"]["baixo"].as<int>();
      esquerda = doc["televisao"]["esquerda"].as<int>();
      direita = doc["televisao"]["direita"].as<int>();
      selectButton = doc["televisao"]["select"].as<int>();
      voltar = doc["televisao"]["voltar"].as<int>();
    }

      controlarJsonTelevisao(ligardesligar, aumentar, diminuir, cima, baixo, esquerda, direita, selectButton, voltar);

  if(ligardesligar == 0)
  {
    publicarMensagem("senai/esp32/televisao", "Estado da TV trocado com sucesso");
  }
  if(aumentar == 1)
  {
    publicarMensagem("senai/esp32/televisao", "Volume aumentado com sucesso");
  }
  if(diminuir == 2)
  {
    publicarMensagem("senai/esp32/televisao", "Volume diminuido com sucesso");
  }
   if(cima == 4)
  {
    publicarMensagem("senai/esp32/televisao", "Direção para cima acionada com sucesso");
  }
   if(baixo == 5)
  {
    publicarMensagem("senai/esp32/televisao", "Direção para baixo acionada com sucesso");
  }
   if(esquerda == 6)
  {
    publicarMensagem("senai/esp32/televisao", "Direção para esquerda acionada com sucesso");
  }
   if(direita == 7)
  {
    publicarMensagem("senai/esp32/televisao", "Direção para direita acionada com sucesso");
  }
   if(selectButton == 8)
  {
    publicarMensagem("senai/esp32/televisao", "Botão select acionado com sucesso");
  }
   if(voltar == 9)
  {
    publicarMensagem("senai/esp32/televisao", "Botão voltar acionado com sucesso");
  }
}
}
