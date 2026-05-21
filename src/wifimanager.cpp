//?wifimanager.cpp
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include "wifimanager.h"
#include "secrets.h"
#include "DebugManager.h"

bool wifiEstaConectado()
{
    return WiFi.status() == WL_CONNECTED;
}

void conectarWifi()
{
  debugInfo ("0000000000000000");
  debugInfo ("Iniciando conexão WiFi...");
  debugInfo ("==============================");

 //Configura o Esp32 como station, ou seja
 //ele vai se conectar a um roteador existente
  WiFi.mode(WIFI_STA);

  //Inicia a conexão com SSID e senha
  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  debugInfo("Conectando...");

  int tentativasWifi = 0;
  const int maxTentativasWifi = 30;

  //Aguarda a conexão por até 30 tentativas
  while (WiFi.status() != WL_CONNECTED && tentativasWifi < maxTentativasWifi) 
  {
    delay(500);
    debugInfoSemLinha(".");
    tentativasWifi++;
  }
  
  debugInfo("");

  if (WiFi.status() == WL_CONNECTED) 
  {
    debugInfo("WiFi Conectado com Sucesso!");
    debugInfo("Endereço IP: ");
    debugInfoSemLinha(String(WiFi.localIP().toString()));
    debugInfoSemLinha("\n\r");
  }

  else 
  {
    debugErro("Falha ao Conectar ao WiFi.");
    debugErro("Verifique SSID, senha e sinal de rede");
  }
}


void garantirWifiConectado()
{
  if(WiFi.status() != WL_CONNECTED)
  {
    debugErro("WiFi desconectado. Tentando reconectar...");
    conectarWifi();
  }

  if (WiFi.status() != WL_CONNECTED) 
  {
    debugErro("Não foi possível reconectar ao WiFi.");
  }
}