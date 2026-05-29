//?MQTTmanager.cpp
#include <WiFiClient.h>
#include <Arduino.h>
#include <PubSubClient.h>
#include <WiFiClientSecure.h>

#include "wifimanager.h"
#include "secrets.h"
#include "DebugManager.h"
#include "MQTTmanager.h"

//======Objetos/Instâncias=========
WiFiClient wifiCliente;
WiFiClientSecure wifiClienteSecure;
PubSubClient mqttCliente;

CallbackMensagemMQTT callbackDoApp = nullptr;

void registrarCallbackMensagem(CallbackMensagemMQTT callback)
{
    callbackDoApp = callback;

    if (callbackDoApp != nullptr)
    {
        debugInfo("Callback da aplicação resgistrado com sucesso");
    }
    else
    {
        debugErro("Callback da aplicação não foi registrado");
    }
}

const char *obterTopicoPublicacao(int indiceTopico)
{
    if (indiceTopico < 0 || indiceTopico >= TOTAL_TOPICOS_PUBLICAR)
    {
        debugErro("Indice inválido para tópico de publicação: " + String(indiceTopico));
        return "";
    }
    return TOPICOS_PUBLICAR[indiceTopico];
}
const char *obterTopicoRecebimento(int indiceTopico)
{
    if (indiceTopico < 0 || indiceTopico >= TOTAL_TOPICOS_RECEBER)
    {
        debugErro("Indice inválido para tópico de recebimento: " + String(indiceTopico));
        return "";
    }
    return TOPICOS_RECEBER[indiceTopico];
}

void callbackInternoMQTT(char *topico, byte *payload, unsigned int tamanho)
{
    String mensagem = "";
    for (unsigned int i = 0; i < tamanho; i++)
    {
        mensagem += (char)payload[i];
    }
    if (callbackDoApp != nullptr)
    {
        callbackDoApp(topico, mensagem);
    }
    else
    {
        debugErro("Mensagem foi recebida porém nenhum callback da aplicação foi registrado");
    }
}

void configurarMQTT()
{
    debugInfo("============");
    debugInfo("Configurando MQTT...");
    debugInfo("============");

    if (USAR_AWS_IOT)
    {
        debugInfo("Modo Selecionado: AWS IoT Core.");
            debugInfo("Configurando certificados da AWS IoT Core.");

            wifiClienteSecure.setCACert(AWS_CERTIFICADO_CA);
            wifiClienteSecure.setCertificate(AWS_CERTIFICADO_CRT);
            wifiClienteSecure.setPrivateKey(AWS_CERTIFICADO_PRIVATE);

            mqttCliente.setClient(wifiClienteSecure);
            mqttCliente.setServer(AWS_IOT_ENDPOINT, AWS_IOT_PORT);
            debugInfo("EndPoint AWS IoT: " + String(AWS_IOT_ENDPOINT));
            debugInfo("Porta AWS IoT: " + String(AWS_IOT_PORT));
    }
    else if (MQTT_USAR_TLS)
    {
        debugInfo("Modo selecionado: MQTT COM TLS.");

        if(strlen(MQTT_CERTIFICADO_CA) > 100) //se o comprimento da string MQTT for maior que 100
        {
            wifiClienteSecure.setCACert(MQTT_CERTIFICADO_CA);
            debugInfo("Certificado CA do broker MQTT configurado.");
        }

        else
        {
            debugErro("Certificado CA do MQTT não configurado. Usando setInsecure apenas para teste");
            wifiClienteSecure.setInsecure();
        }

        mqttCliente.setClient(wifiClienteSecure);
        mqttCliente.setServer(MQTT_BROKER, MQTT_PORTA);

        debugInfo("Broker MQTT: " + String(MQTT_BROKER));
        debugInfo("Porta: " + String(MQTT_PORTA));
    }
    else // Conectar no broker(servidor) sem certificado
    {
        debugInfo("Modo selecionado: MQTT sem TLS.(certificado)");

        mqttCliente.setClient(wifiCliente);
        mqttCliente.setServer(MQTT_BROKER, MQTT_PORTA);

        debugInfo("Broker MQTT: " + String(MQTT_BROKER));
        debugInfo("Porta: " + String(MQTT_PORTA));
    }

    mqttCliente.setCallback(callbackInternoMQTT);
    debugInfo("Callback interno do MQTT configurado");
}

void conectarMQTT()
{
    if (!wifiEstaConectado())
    {
        debugErro("MQTT não pode conectar poque o WiFi esta desconectado");
    }
    debugInfo("=============");
    debugInfo("Iniciando conexão MQTT...");
    debugInfo("=============");

    int tentativasMQTT = 0;
    const int maxTentativasMQTT = 5;

    while (!mqttCliente.connected() && tentativasMQTT < maxTentativasMQTT)
    {
        debugInfo("Tentando conectar ao Broker MQTT. Tentativa: " + String(tentativasMQTT));

        bool conectado = false;

        if (USAR_AWS_IOT)
        {
            conectado = mqttCliente.connect(AWS_IOT_CLIENT_ID);
        }
        else
        {
            if (strlen(MQTT_USUARIO) > 0)
            {
                debugInfo("Conectando MQTT com usuário e senha");
                conectado = mqttCliente.connect(MQTT_CLIENTE_ID, MQTT_USUARIO, MQTT_SENHA);
            }

            else
            {
                debugInfo("Conectando MQTT sem usuário e senha");
                conectado = mqttCliente.connect(MQTT_CLIENTE_ID);
            }
        }
        if (conectado)
        {
            debugInfo("MQTT conectado com sucesso.");

            int totalTopicos = obterTotalTopicosRecebimento();

            debugInfo("Total de tópicos para inscrição: " + String(totalTopicos));

            for (int i = 0; i < totalTopicos; i++)
            {
                const char *topico = obterTopicoRecebimento(i);

                bool inscrito = mqttCliente.subscribe(topico);

                if (inscrito)
                {
                    debugInfo("Inscrito no tópico: " + String(topico));
                }
                else
                {
                    debugErro("Falha ao se inscrever no tópico: " + String(topico));
                }
            }
            // TODO: Publicar uma mensagem em um tópico informando que o esp32 foi conectado.
        }
        else
        {
            debugErro("Falha ao conectar no MQTT. Código de erro: " + String(mqttCliente.state()));

            tentativasMQTT++;
            delay(2000);
        }
    } //*Fim do While

    if (!mqttCliente.connected())
    {
        debugErro("Não foi possível conectar ao broker MQTT após " + String(maxTentativasMQTT) + "tentativas");
    }
}

void garantirMQTTConectado()
{
    if (!wifiEstaConectado())
    {
        debugErro("MQTT Não será reconectado porque o WiFi está desconectado.");
        return;
    }

    if (!mqttCliente.connected())
    {
        debugErro("MQTT desconectado, tentando reconectar...");
        conectarMQTT();
    }
}

void loopMQTT()
{
    mqttCliente.loop();
}

void publicarMensagem(const char *topico, const char *mensagem)
{
    if (!mqttCliente.connected())
    {
        debugErro("Não foi possível publicar. MQTT desconectado.");
        return;
    }
    bool publicado = mqttCliente.publish(topico, mensagem);

    if (publicado)
    {
        debugInfo("Mensagem publicada com sucesso via MQTT.");
        debugInfo("Topico: " + String(topico));
        debugInfo("Mensagem: " + String(mensagem));
    }
    else
    {
        debugErro("Falha ao publicar mensagem no tópico: " + String(topico));
    }
}

void publicarMensagemNoTopico(int indiceTopico, const char* mensagem)
{
    const char* topico = obterTopicoPublicacao(indiceTopico);

    if(strlen(topico) == 0)
    {
        debugErro("Não foi possível publicar, índice de tópico inválido: " + String(indiceTopico));
        return;
    }
    publicarMensagem(topico, mensagem);
}

bool mqttEstaConectado()
{
    return mqttCliente.connected();
}

int obterTotalTopicosRecebimento()
{
    return TOTAL_TOPICOS_RECEBER;
}
