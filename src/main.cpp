
#include <Arduino.h>
#include "wifimanager.h"
#include "MQTTmanager.h"
#include "DebugManager.h"

#include <ArduinoJson.h>

const char TOPICO_COMANDO[] = "senai134/diasHeitor/esp32/televisao";

void tratarMensagemRecebida(const char* topico, const String& mensagem);
void controlarJsonTelevisao(int ligardesligar, int aumentar, int diminuir);
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
    if(!doc["televisao"]["power"].is<int>() || !doc["televisao"]["upV"].is<int>() || !doc["televisao"]["downV"].is<int>())
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
      debugInfo("Comandos recebidos com sucesso!");
    }
  }

  /*String resposta;
  serializeJson(doc, resposta);
  if(ligardesligar == 0){
    doc["televisao"]["status"]
  }*/


}