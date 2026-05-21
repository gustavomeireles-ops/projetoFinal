//?secrets.cpp
#include "secrets.h"
#include <Arduino.h>

const char * WIFI_SSID = "SALA 09";
const char * WIFI_SENHA = "info@134";


//====MQTT=====
const char* MQTT_BROKER = "------";
const int MQTT_PORTA = 8883;

const char* MQTT_CLIENTE_ID = "esp32Televisão";

const char* MQTT_USUARIO = "TVUser";
const char* MQTT_SENHA = "Senai@134";

const bool MQTT_USAR_TLS = true; //modo de conexão de segurança

//Raw string
const char MQTT_CERTIFICADO_CA[] PROGMEM = R"EOF(
)EOF";

//-------------------------
//   AWS
//-------------------------

const bool USAR_AWS_IOT = true; //modo de conexão via AWS

const char* AWS_IOT_CLIENT_ID = "TVUser";

const char AWS_CERTIFICADO_CA[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

const char AWS_CERTIFICADO_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----

-----END CERTIFICATE-----
)EOF";

const char AWS_CERTIFICADO_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----

-----END RSA PRIVATE KEY-----
)EOF";

const char* AWS_IOT_ENDPOINT = "-------";

const int AWS_IOT_PORT = 8883;

//-----------------
//   MQTT
//-----------------

const char* TOPICOS_PUBLICAR[] = { //o ponteiro não separa um espaço específico de memória para não limitar o usuário, por isso o uso do ponteiro(indica o começo e só para quando achar um \0)
    "senai/esp32/status",
    "senai/esp32/log",
    "senai/esp32/televisao"
};
const int TOTAL_TOPICOS_PUBLICAR = sizeof(TOPICOS_PUBLICAR) / sizeof(TOPICOS_PUBLICAR[0]);

const char* TOPICOS_RECEBER[] = {
    "senai134/diasHeitor/esp32/comando",
    "senai134/diasHeitor/esp32/config",
    "senai134/diasHeitor/esp32/televisao"
};
const int TOTAL_TOPICOS_RECEBER = sizeof(TOPICOS_RECEBER) / sizeof(TOPICOS_RECEBER[0]);
//===================================
//DEBUG
//===================================

// 0 = sem mensagens
// 1 = apenas erros
// 2 = todas as mensagens
const int DEBUG_NIVEL_INICIAL = 2;

//Pino usado para forçar todas as mensagens na inicialização
const int PINO_HABILITA_DEBUG_COMPLETO = 4;
