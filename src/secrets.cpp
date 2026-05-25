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
MIIDWTCCAkGgAwIBAgIUYXbdAI0xdLlNzvGq26t9pRTFN28wDQYJKoZIhvcNAQEL
BQAwTTFLMEkGA1UECwxCQW1hem9uIFdlYiBTZXJ2aWNlcyBPPUFtYXpvbi5jb20g
SW5jLiBMPVNlYXR0bGUgU1Q9V2FzaGluZ3RvbiBDPVVTMB4XDTI2MDUxODE3MzIw
MVoXDTQ5MTIzMTIzNTk1OVowHjEcMBoGA1UEAwwTQVdTIElvVCBDZXJ0aWZpY2F0
ZTCCASIwDQYJKoZIhvcNAQEBBQADggEPADCCAQoCggEBANGOo2XeznyjZxYgMz4n
zPf7et922939JdayXcGv6z58XFiGk9U2naHYGQ+Rw986OyFemSEYc5Du9PvXSvxQ
JEUix0BraozPpSwWu6X47DRT4S699Cy9A0RXnXulZzPdCnbIds74hISDGcu5yBs1
qLwKdVUaIqKC0USc4pCfu8ZwCsxErNCuNbgenEZVljwABfniQIgHsr6gcf6xv0AA
tUTesli8Q93fXaIwvScGCiUy71NsRWHkosuo43iV2xQWrLw3pVURfTPeZ3y3kLYI
0sXfgPm80WKru+z0ohVTnrRj86+7p5GnDojjfdgF+VakfakpqGsMINOCEdC9bhBe
xEMCAwEAAaNgMF4wHwYDVR0jBBgwFoAUT4sowO2DF7wrCclvSoYYXLgHY0YwHQYD
VR0OBBYEFI2AvgRGG6vb5Vuo0PmJLQqgnggcMAwGA1UdEwEB/wQCMAAwDgYDVR0P
AQH/BAQDAgeAMA0GCSqGSIb3DQEBCwUAA4IBAQBvix1S8Gel5fkHQ0ZEqMxxArpi
mUM19dfNh4+X+31mkAJZZCg7fJDO/jm7iRasN/C+lKeRhE23LnvIGy7DLVe2dQtN
dz6LlTiCMbLEeBBdtIAvKGy31U1TtHhJuURyZUGG98Uw7XFNtrWkTdIUgpsskXv/
makqxO1C6UD0B4LDmvJYIjiIaR/piEftdMXAJmjXhI5FzMs8hL4SBz7xpXESwmVC
lz4allnpLBcjVK34o9OspfZ8ZqxTaflULmXbBF9PYUFaGFPOxG6nnxLe2esfIfsW
xqXZnfKV9fViy25/VYGNzGr9f9eRlI5tzU2fICgsCTU3HOjvF1xd13uEMFVO
-----END CERTIFICATE-----
)EOF";


const char AWS_CERTIFICADO_PRIVATE[] PROGMEM = R"EOF(
-----BEGIN RSA PRIVATE KEY-----
MIIEpAIBAAKCAQEA0Y6jZd7OfKNnFiAzPifM9/t633bb3f0l1rJdwa/rPnxcWIaT
1TadodgZD5HD3zo7IV6ZIRhzkO70+9dK/FAkRSLHQGtqjM+lLBa7pfjsNFPhLr30
LL0DRFede6VnM90Kdsh2zviEhIMZy7nIGzWovAp1VRoiooLRRJzikJ+7xnAKzESs
0K41uB6cRlWWPAAF+eJAiAeyvqBx/rG/QAC1RN6yWLxD3d9dojC9JwYKJTLvU2xF
YeSiy6jjeJXbFBasvDelVRF9M95nfLeQtgjSxd+A+bzRYqu77PSiFVOetGPzr7un
kacOiON92AX5VqR9qSmoawwg04IR0L1uEF7EQwIDAQABAoIBADSKvw1bwAogLkit
6is7b3j95OECvD38qvAZ6MgXg7Q3GjBYDdj3yK47sIzmz2W5A/pp7ZsOtmswftxm
Lrb0oSN0hODyDdUgexmC2anTr+Wu4lcF6aMOATOxhBrsbePjGCyQNrnONevDs0QR
YMrxuUzskl60HtsAUdgSPfxlEH/AQ44uO8G0Tez/KqjU0fUW5sVehsZfC9KHXoSk
Lnkk6scJu4ivvRjtPNOjCdM3hV9F4dkHsdBbKQjOUoqPRPLVzd90yJFg3YfzpU3v
b4xrMXpAuRK9Ha4l3DYi+hhFsmr3VQzjEdyv6mgCy3+jIAD+c1nQGq+UqGjT2vMX
9QKy7IECgYEA92quNZk6aDq6RNHZ5QC4EWpCAS1qoPNLW/OM7lsR2DFJpWD3RW4s
fYuLi9PH+weoImHFCrliPReKqxP0iynBb/ZAmbjfErMtDcPlP0gQFnOKL9hkMcAx
LZkyHcBlSLsWuCDrG89IAbu6o4Kh2S8B27x4ZfiocyIn33+VB++sBicCgYEA2NO5
tQlWJTZlOCv0K7fHJbmrhlHMZYY8JJA2N2LC7lbQlgdMQdp5dCQboqU7LuqEDYWS
Hxz3KJIaTfDw1j0sGMvn9tMjehG/2dJsKB2KF7gAQ52ipnBSA0wLjKG1lcbMHFVb
KM2PjA4DaGEg1BA6Xr4GcJEPTQPrNnJD8Q3hHoUCgYEAj65hSvkYJS1tvMeNXWME
ggCOIjboxF1ltxmCD23NuBovZZ4hGy33IlVmjaZIbWyt5IGYtzifZ1EDk4Q8MJDo
KAf+zgbBbQ+mq2bG++/yf8dLSavFy+qL5Koho4t2hj033WgogPboHzGRGqGjMggN
cTlLRhSYZnxAYZeqyXgTE2MCgYAy2eTxylDDxXATrmtDXYR9GoBZrhFrtgGg6Zlt
f+ILl5yvsuJ1h1F4pYc9q9aneCSkLzFHzrlAcJNuuBUjiZEv95JdVsM5O7Rs12a6
OcNLMMIPGYct1aXGVC1ZPAukJs1zz6jjduI1jIvMDQtv8KZf1d0YxUx7WXHugPni
LMkhKQKBgQCLCOxQU7Cs7hZOEtK4ZZOkdcZP4urvvZzct/r07Z5SdFNSIvhQqT4w
Q3QTON/Nfmm5isw+eG4vdkdHclkeW9sXmzxEA5wLbsN5KGgQqieDz1CPJy6STU6F
ZzDvdc6dKeJMv0CvTmDTT+hj0O+McgCszYAZJDbPjIaO4qYPZI0Qfw==
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
