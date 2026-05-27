
#include <Arduino.h>
#include "wifimanager.h"
#include "MQTTmanager.h"
#include "DebugManager.h"

#include <ArduinoJson.h>

const char TOPICO_COMANDO[] = "senai134/diasHeitor/esp32/televisao";

void tratarMensagemRecebida(const char* topico, const String& mensagem);
void controlarJsonTelevisao(int ligardesligar, int aumentar, int diminuir);
void tratarJsonComando(const String& mensagem);



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
  ligardesligar = constrain(ligardesligar, 0, 1);
  aumentar = constrain(aumentar, 2, 2);
  diminuir = constrain(diminuir, 3, 3);

  debugInfo("Televisão configurada");
  debugInfo("ligardesligar: " + String(ligardesligar));
  debugInfo("aumentar: " + String(aumentar));
  debugInfo("diminuir: " + String(diminuir));

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
    if(!doc["televisao"]["ligardesligar"].is<int>() || !doc["televisao"]["aumentar"].is<int>() || !doc["televisao"]["diminuir"].is<int>())
    {
      debugErro("Json inválido. Use televisao.ligardesligar, televisao.aumentar, televisao.diminuir");
      return;
    }
    else
    {
      int ligardesligar = doc["televisao"]["ligardesligar"].as<int>();
      int aumentar = doc["televisao"]["aumentar"].as<int>();
      int diminuir = doc["televisao"]["diminuir"].as<int>();

      controlarJsonTelevisao(ligardesligar, aumentar, diminuir);
    }
  }

}