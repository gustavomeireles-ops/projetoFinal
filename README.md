📺 ClassControl – Módulo de Controle de Televisão

Controle de Televisão via ESP32, MQTT e Infravermelho

Sistema responsável por receber comandos através da rede e convertê-los em sinais infravermelhos para controle remoto da televisão.

---

🎯 Objetivo

Este módulo integra o projeto ClassControl e tem como finalidade controlar uma televisão utilizando um ESP32 conectado à rede Wi-Fi.

Os comandos são recebidos por meio do protocolo MQTT, processados em formato JSON e transmitidos para a televisão através de um LED infravermelho (IR).

Após a execução de cada comando, o módulo publica uma resposta informando o status da operação.

---

⚙️ Funcionalidades Implementadas

📺 Controle da Televisão

| Comando | Ação                |
| ------- | ------------------- |
| 1       | Ligar / Desligar TV |
| 2       | Aumentar Volume     |
| 3       | Diminuir Volume     |
| 4       | Navegação Direita   |
| 5       | Navegação Esquerda  |
| 6       | Navegação Cima      |
| 7       | Navegação Baixo     |
| 8       | Selecionar          |
| 9       | Voltar              |

---

🛰️ Comunicação MQTT

📥 Tópico de Recebimento

```text
senai134/shared/projeto/TV
```

Responsável por receber os comandos destinados ao módulo da televisão.

📤 Tópico de Publicação

```text
senai134/shared/projeto/status
```

Responsável por publicar o resultado da execução dos comandos.

---

📝 Estrutura da Mensagem Recebida

```json
{
  
  "comando": 2,
  "hora": 1747000000
}
```

Campos

| Campo   | Descrição                             |
| ------- | ------------------------------------- |
| comando | Número correspondente à ação desejada |
| hora    | Timestamp enviado pelo sistema        |

---

📨 Estrutura da Resposta

Comando Executado com Sucesso

```json
{
  "modulo": "tv ok",
  "hora": 1747000000
}
```

Comando Inválido

```json
{
  "modulo": "tv nao ok",
  "hora": 1747000000
}
```

---

📡 Conectividade

O módulo possui mecanismos automáticos para garantir a comunicação com o sistema:

✅ Conexão Wi-Fi automática

✅ Reconexão Wi-Fi em caso de falha

✅ Conexão MQTT automática

✅ Reconexão MQTT em caso de desconexão

✅ Sincronização de horário via NTP

---

🔴 Controle Infravermelho

Os comandos são transmitidos utilizando a biblioteca **IRremoteESP8266** através do protocolo **NEC**.

Hardware Utilizado

| Componente        | Função                      |
| ----------------- | --------------------------- |
| ESP32             | Processamento e comunicação |
| LED Infravermelho | Envio dos comandos IR       |
| Televisão         | Dispositivo controlado      |

---

📚 Bibliotecas Utilizadas

```cpp
ArduinoJson
PubSubClient
WiFi
WiFiClientSecure
IRremoteESP8266
ezTime
```

---

🛠️ Sistema de Debug

O projeto possui um módulo dedicado para monitoramento e diagnóstico via Serial.

Informações Registradas

* Inicialização do ESP32
* Estado da conexão Wi-Fi
* Estado da conexão MQTT
* Recebimento de mensagens
* Publicação de respostas
* Erros de comunicação

---

🔄 Fluxo de Funcionamento

```text
Sistema Externo
        │
        ▼
    MQTT Broker
        │
        ▼
      ESP32
        │
        ▼
 Interpretação JSON
        │
        ▼
 Comando Infravermelho
        │
        ▼
     Televisão
        │
        ▼
 Publicação de Status
```

---

📺 ClassControl – Módulo de Controle de Televisão

Desenvolvido utilizando ESP32, MQTT e comunicação infravermelha para integração com sistemas de automação em sala de aula.

</div>
