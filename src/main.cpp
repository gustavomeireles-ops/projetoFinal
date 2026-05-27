
#include <Arduino.h>
#include "wifimanager.h"
#include "MQTTmanager.h"
#include "DebugManager.h"

#include <ArduinoJson.h>

const char TOPICO_COMANDO[] = "senai134/diasHeitor/esp32/televisao";

void tratarMensagemRecebida(const char* topico, const String& mensagem);
void controlarJsonTelevisao(int ligardesligar, int aumentar, int diminuir, int compartilharTela);
void tratarJsonComando(const String& mensagem);

int ligardesligar;
int aumentar;
int diminuir;

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

      controlarJsonTelevisao(ligardesligar, aumentar, diminuir);
    }
  }

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
}