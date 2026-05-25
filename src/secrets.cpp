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
MIIDQTCCAimgAwIBAgITBmyfz5m/jAo54vB4ikPmljZbyjANBgkqhkiG9w0BAQsF
ADA5MQswCQYDVQQGEwJVUzEPMA0GA1UEChMGQW1hem9uMRkwFwYDVQQDExBBbWF6
b24gUm9vdCBDQSAxMB4XDTE1MDUyNjAwMDAwMFoXDTM4MDExNzAwMDAwMFowOTEL
MAkGA1UEBhMCVVMxDzANBgNVBAoTBkFtYXpvbjEZMBcGA1UEAxMQQW1hem9uIFJv
b3QgQ0EgMTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBALJ4gHHKeNXj
ca9HgFB0fW7Y14h29Jlo91ghYPl0hAEvrAIthtOgQ3pOsqTQNroBvo3bSMgHFzZM
9O6II8c+6zf1tRn4SWiw3te5djgdYZ6k/oI2peVKVuRF4fn9tBb6dNqcmzU5L/qw
IFAGbHrQgLKm+a/sRxmPUDgH3KKHOVj4utWp+UhnMJbulHheb4mjUcAwhmahRWa6
VOujw5H5SNz/0egwLX0tdHA114gk957EWW67c4cX8jJGKLhD+rcdqsq08p8kDi1L
93FcXmn/6pUCyziKrlA4b9v7LWIbxcceVOF34GfID5yHI9Y/QCB/IIDEgEw+OyQm
jgSubJrIqg0CAwEAAaNCMEAwDwYDVR0TAQH/BAUwAwEB/zAOBgNVHQ8BAf8EBAMC
AYYwHQYDVR0OBBYEFIQYzIU07LwMlJQuCFmcx7IQTgoIMA0GCSqGSIb3DQEBCwUA
A4IBAQCY8jdaQZChGsV2USggNiMOruYou6r4lK5IpDB/G/wkjUu0yKGX9rbxenDI
U5PMCCjjmCXPI6T53iHTfIUJrU6adTrCC2qJeHZERxhlbI1Bjjt/msv0tadQ1wUs
N+gDS63pYaACbvXy8MWy7Vu33PqUXHeeE6V/Uq2V8viTO96LXFvKWlJbYK8U90vv
o/ufQJVtMVT8QtPHRh8jrdkPSHCa2XV4cdFyQzR1bldZwgJcJmApzyMZFo6IQ6XU
5MsI+yMRQ+hDKXJioaldXgjUkK642M4UwtBV8ob2xJNDd2ZhwLnoQdeXeGADbkpy
rqXRfboQnoZsG4q5WTP468SQvvG5
-----END CERTIFICATE-----
)EOF";

const char AWS_CERTIFICADO_CRT[] PROGMEM = R"EOF(
-----BEGIN CERTIFICATE-----
MIIDWTCCAkGgAwIBAgIUfIPsefDIM59AYJdJLKILtVa+dTYwDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDUxODE3MzMy
OVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBAMmrp6tpJfGNOyzjs5Wf
1zldEQsrbndkk5hqGWYBkYaxuTMHDZGgnM2broowpuJf0b06bovPJ0beNTuREePU
iIspELzNMYrJxMkN+OHYYe7USaPJZnvuWqqHPExqfDrMTWAUz5Sgjo/IU4qu/OZ/
ykqqwOMLgsteAe3nNcLYSnz0G3oHcsLUB8zgq5GTfpCvUys0qpyasdirv9lQod10
ejfw7zISevAV20fXblWiSmA1IpWMMIDW6L8AzbHZaldMBM92bds7HbNgsEPIgEyR
6A5y+OWxLmZlSGMf9NcThIq7kDUsb/105D8eB94y/hyoyslcq6Bhz+O7OAbiAB8S
aTsCAwEAAaNgMF4wHwYDVR0jBBgwFoAUSz0tqVBF7SROjmWOef0U9C7xWT0wHQYD
VR0OBBYEFM4zujUgGyecVEVRpb+IMs0Oi0R9MAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQCViGlPB9u44sflBTihcEkHBcjJ
26EB5kPA5XTTJulswFQ+fiVKoVCCl8y8d456jIQ7OobDfo3u6ufxhChm7VMvRKuT
5IDl6XPzrM4adgtUwhXpvUKBAYs8dOOmLWB/syxaXi5NmAIgN71SyA3l6eakFXHp
8zwatOihsDWDFtpAUzf+zH51SE/F9obDtr1Fh1lA3ZBkyavSNfjaobB3LnrI/vxT
z+SBsq+dt0XgrRT/Objqtr0+MhFfPT8Ub7gwGUTnLFtO0OQAhoFPLw5PjZF8qdgD
xcn3EB35uRC3Fv/w6892hxoOMTJw2Ax/HF1F4vSySNXq9qCSym3GlkRqGA7z
-----END CERTIFICATE-----
)EOF";

const char AWS_CERTIFICADO_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEAyaunq2kl8Y07LOOzlZ/XOV0RCytud2STmGoZZgGRhrG5MwcN
kaCczZuuijCm4l/RvTpui88nRt41O5ER49SIiykQvM0xisnEyQ344dhh7tRJo8lm
e+5aqoc8TGp8OsxNYBTPlKCOj8hTiq785n/KSqrA4wuCy14B7ec1wthKfPQbegdy
wtQHzOCrkZN+kK9TKzSqnJqx2Ku/2VCh3XR6N/DvMhJ68BXbR9duVaJKYDUilYww
gNbovwDNsdlqV0wEz3Zt2zsds2CwQ8iATJHoDnL45bEuZmVIYx/01xOEiruQNSxv
/XTkPx4H3jL+HKjKyVyroGHP47s4BuIAHxJpOwIDAQABAoIBAF6WRhPdQ1Ch3wlU
2tvoljdvcRj+C9evspIf4T24qpq0LJrEShbtb933kMt7uioequ7HwyWLyW4xtmHz
zqI/ArPSVOlYjE3+CHAMP5kdtgEgTFGnmoux5ZBp0Vw97XpebEQOPrYFABhr6tL2
8+LgOO8AW2uh8HyV4O3GLa7vZzBnMHAq38sBRE2Ww1Shyp/wULxCz/kte+57uMc7
jD40VBGBwSR1l+umXy7BXqEUy1tzWsCVujQUpk1hd386mqpZ9vTFI9rQh1blYECY
AV9BJOXuQOEr5IUbphas5f+yrH7R8PS1AkkWyj9Rwe8pN4jnkmbikfzkpVvTP+ij
lNwlf8ECgYEA6LupamEAiVse50ZcYcA//F/Ks3wFQbeFWWl+T90OB6LuRUbO/uUK
oFG8Tnoa2jvqHb7m6HonRRHzTzRc35m+qfG/51IpcVeVgaUiVJyXWMyMT6jzoWd2
jjvUqv2XqmrE1APCVLg1NbNTcNiBpCXEPUsc+AA9S58S5S3djYwyorECgYEA3dUC
gNzP2hEfDfBkebqKN7mC8uE99p4c7bMYmaUdlodvvpJgUIIfJSGke4AFU8ooFnIA
J6WNdMlazuMki12NnE4QIm2D6/WdP9wgqnPgVyGggxkFhx/P1dWmfv8sOv0uOJ1e
QVSqAiVrAI2A7ItQMga6OPw3fJ5mXU8nA8p4zasCgYEAyFmVFLEA5z38MpjNupDo
BHjqZOzlEZfNQhWg2VuxUj2e5SB53dCK/0yd0Oko6Kofdw/6dDOETt+PF6Y6NXuD
OYWV8Ks4ZgxB9mOUVEahu54LRCBr64zH8NXs1G6O+/QCEYpS5t/VXq9Lq5+Wqxqf
/ywEejKqkckVWRnM2qfQh2ECgYAceSblG3Kibugphd2fsk3jcTBZtIebjBfyeraB
oiv2ElRJhchPDSSqQ3M1Vu1YH+6dUuyqKhnKD75UJ9uc99khYvO3N49jThdtBvg6
aL028d4EdcW73l1y+QVx75bhy3WPVsOuZwubUuo1G/ScaBVXFn34qocEu+AvweUk
G2z+GQKBgGBDohsll8zTLFBXFaQ0bDmmtoXGSMw81ZLkqxugu3DZwwAHcbuv1Ohk
07Sh9pahxCigSxIK6YoKycmrtTKvOsprELdHULEbOghbacA6eYV5O6k4oHdRlMIS
35sFJ5rw8hzvms+Z0J+zWbwz1VIP2otjC7KEQODZ7uduyn5wW1fe
-----END RSA PRIVATE KEY-----
)EOF";

const char* AWS_IOT_ENDPOINT = "a12r4jrc022r8n-ats.iot.us-east-1.amazonaws.com";

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
