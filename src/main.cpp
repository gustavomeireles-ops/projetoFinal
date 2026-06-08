
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
void respostaPublicacao();
void configurarNTP();

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
unsigned long hora = 0;

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
  configurarNTP();
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

  if(doc["hora"].is<long>())
  {
    hora = doc["hora"].as<unsigned long>();
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
      respostaPublicacao();
    }
    if (comando == 2)
    {
      VolumeMais();
      respostaPublicacao();
    }
    if (comando == 3)
    {
      VolumeMenos();
      respostaPublicacao();
    }
    
    //*ADICIONAIS
    if (comando == 4)
    {
      SetaDireita();
      respostaPublicacao();

    }
    if (comando == 5)
    {
      SetaEsquerda();
      respostaPublicacao();

    }
    if (comando == 6)
    {
      SetaCima();
      respostaPublicacao();
    }
    if (comando == 7)
    {
      SetaBaixo();
      respostaPublicacao();
    }
    if (comando == 8)
    {
      Select();
      respostaPublicacao();
    }
    if (comando == 9)
    {
      Back();
      respostaPublicacao();
    }
  }

  void configurarNTP()
  {
    configTime(-3 * 3600, 0, "pool.ntp.org", "time.google.com");
  }
  void respostaPublicacao()
  {
    time_t respostaPosix = time(nullptr);
        if(comando > 0 && comando <= 9)
        {
          statusTV = "tv ok";
        }
        else
        {
          statusTV = "tv nao ok";
        }
        resposta["modulo"] = statusTV;
        resposta["hora"] = respostaPosix;

        if(respostaPosix < 1000000000)
        {
          debugInfo("NTP ainda não sincronizado!");
          return;
        }
        
        char gravarJson[1000];
        
        serializeJson(resposta, gravarJson);
        publicarMensagem(TOPICO_PUBLICAR, gravarJson);
  }
