
#include <Arduino.h>
#include "wifimanager.h"
#include "MQTTmanager.h"
#include "DebugManager.h"
#include "TV.h"
#include <IRremoteESP8266.h>
#include <IRsend.h>
#include <ArduinoJson.h>
#include <ezTime.h>

const char TOPICO_PUBLICAR[] = "senai134/shared/projeto/status";
const char TOPICO_RECEBER[] = "senai134/shared/projeto/yoshi";

//?MQTT
void tratarMensagemRecebida(const char *topico, const String &mensagem);
void controlarJsonTelevisao(int ligardesligar, int aumentar, int diminuir, int compartilharTela);
void tratarJsonComando(const String &mensagem);
void controlarComandos();
void agoraVai();

//?TELEVISÃO
void PowerTV();
void VolumeMais();
void VolumeMenos();
void SetaDireita();
void SetaEsquerda();
void SetaCima();
void SetaBaixo();
void Select();
void Back();

int comando = 0;
int hora = 0;
const char* horaEnviar;
String statusTV;

//?EZTIME
Timezone timeStamp;

void setup()
{
  configurarDebug();
  conectarWifi();
  configurarMQTT();
  registrarCallbackMensagem(tratarMensagemRecebida);
  conectarMQTT();
  irsend.begin();

  //?EZTIME
  setInterval(3600);
  waitForSync();
  timeStamp.setLocation("America/Sao_Paulo");
  //timeStamp.setPosix("<-03>3");


}

void loop()
{
  garantirWifiConectado();
  garantirMQTTConectado();
  loopMQTT();

  //?EZTIME
  events();
}

void tratarMensagemRecebida(const char *topico, const String &mensagem)
{
  
  debugInfo("=======================");
  debugInfo("Mensagem recebida na aplicação");
  debugInfo("=======================");

  if (topico == nullptr)
  {
    debugErro("Tópico MQTT inválido");
    return;
  }

  debugInfo("Tópico: " + String(topico));
  debugInfo("Mensagem: " + mensagem);

  if (strcmp(topico, TOPICO_RECEBER) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }
  if (strcmp(topico, TOPICO_PUBLICAR) == 0)
  {
    tratarJsonComando(mensagem);
    return;
  }
  debugErro("Tópico não tratado: " + String(topico));
}

void controlarJsonTelevisao(int comando)
{
  debugInfo("Televisão configurada");
  debugInfo("Comando: " + String(comando));
}

JsonDocument doc;

void tratarJsonComando(const String &mensagem)
{
  DeserializationError erro = deserializeJson(doc, mensagem);
  if (erro)
  {
    debugErro("Erro ao interpretar o Json Enviado.");
    debugErro(erro.c_str());
    return;
  }

  if (doc["televisao"].is<JsonObject>())
  {
    comando = doc["televisao"]["comando"].as<int>();
  }

  if(doc["hora"].is<JsonObject>())
  {
    hora = doc["hora"].as<int>();
  }

  controlarJsonTelevisao(comando);

  controlarComandos();
  }

  String respostaPosix = timeStamp.getPosix();
  JsonDocument resposta;

  void controlarComandos()
  {
    //*MVP
    if (comando == 1)
    {
      PowerTV();
    }
    if (comando == 2)
    {
      VolumeMais();
    }
    if (comando == 3)
    {
      VolumeMenos();
    }
    
    //*ADICIONAIS
    if (comando == 4)
    {
      SetaDireita();
    }
    if (comando == 5)
    {
      SetaEsquerda();
    }
    if (comando == 6)
    {
      SetaCima();
    }
    if (comando == 7)
    {
      SetaBaixo();
    }
    if (comando == 8)
    {
      Select();
    }
    if (comando == 9)
    {
      Back();
    }
  }

  void agoraVai()
  {
        if(comando > 0 && comando < 9)
        {
          statusTV = "OK";
        }
        else{
          statusTV = "NÃO";
        }
        resposta["tv"] = statusTV;
        resposta["hora"] = respostaPosix.c_str();
        
        char gravarJson[256];
        serializeJson(resposta, gravarJson);
        publicarMensagem(TOPICO_PUBLICAR, gravarJson);
  }

  /*
  {
   TV : ok
   timestamp : 1727843876842
  }
  
  
  */