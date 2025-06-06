LINK DO PROJETO NO WOKWI: https://wokwi.com/projects/432739300429044737
# 🌦️ WeatherGuard

**WeatherGuard** é uma solução de monitoramento climático em tempo real, desenvolvida para enfrentar o aumento de desastres naturais no Brasil. Utilizando um sistema IoT baseado em ESP32 com sensor DHT22, protocolo MQTT e um aplicativo mobile em React Native, o projeto visa proteger comunidades vulneráveis por meio da emissão de alertas climáticos automáticos, acessíveis e escaláveis.

---

## 📍 Contexto e Problema

O Brasil tem enfrentado um crescimento alarmante de eventos climáticos extremos, como chuvas torrenciais e ventos intensos. Segundo o INPE, em 2024 houve um aumento de 15% nesses eventos em relação à média da última década. A ausência de sistemas acessíveis e eficazes de alerta agrava os riscos, especialmente em comunidades menos favorecidas.

---

## 🎯 Objetivo do Projeto

O **WeatherGuard** busca promover segurança e resiliência frente aos desastres climáticos, integrando dados de APIs meteorológicas públicas (OpenWeatherMap) com sensores IoT locais. Por meio de um backend inteligente, o sistema analisa essas informações e envia notificações personalizadas aos usuários, permitindo uma resposta rápida a situações de risco.

---

## 🛠️ Solução Proposta

O sistema é dividido em quatro pilares:

1. **Monitoramento em Tempo Real**
   - Coleta de dados via API OpenWeatherMap (chuva, vento, temperatura).
   - Medição local de temperatura e umidade com **ESP32 + DHT22**.

2. **Processamento Inteligente**
   - Backend em **Spring Boot** hospedado no **Render** analisa os dados e detecta padrões de risco.

3. **Alertas Automatizados**
   - Geração de alertas personalizados e envio ao aplicativo mobile em tempo real.

4. **Arquitetura Robusta**
   - Estrutura baseada no framework **TOGAF**, garantindo escalabilidade, confiabilidade e acessibilidade, com camadas bem definidas de negócio, aplicação (MQTT, HTTP/REST) e tecnologia (IoT, Render).

---

## 📡 Visão Geral do Projeto

- 📍 **ESP32** lê dados do sensor **DHT22** (temperatura e umidade).
- 🔁 Envia os dados via **MQTT** no tópico `weatherguard/monitoramento/clima`.
- 🌐 **Node-RED** escuta o tópico e processa os dados.
- 📱 Aplicativo mobile **React Native** se conecta ao broker MQTT para exibir os dados em tempo real.
- LINK DO PROJETO NO WOKWI: https://wokwi.com/projects/432739300429044737

---

## ⚙️ Tecnologias Utilizadas

| Componente         | Tecnologia               |
|--------------------|--------------------------|
| Microcontrolador   | ESP32                    |
| Sensor             | DHT22                    |
| Protocolo          | MQTT                     |
| Broker             | HiveMQ / Mosquitto       |
| Backend            | Spring boot java                 |
| App Mobile         | React Native + MQTT.js   |

---

## 🧾 Bibliotecas Arduino utilizadas

No código `.ino` do ESP32, utilize as seguintes bibliotecas:

- `DHT.h`
- `WiFi.h`
- `PubSubClient.h`
- `LiquidCrystal I2C`

Instale as bibliotecas via **Arduino Library Manager**.

---

## 🔌 Fluxo de Funcionamento

1. **ESP32** conecta ao Wi-Fi.
2. Lê os dados do **DHT22**.
3. Envia via MQTT para o tópico `weatherguard/monitoramento/clima`.
4. **Node-RED** recebe os dados e os encaminha para debug e/ou dashboard.
5. O **app React Native** também consome os dados em tempo real.

---

## 🧪 Testando o Sistema

### 1. Configurar Broker MQTT
- Use o [HiveMQ Broker público](https://www.hivemq.com/demos/websocket-client/) ou instale o Mosquitto localmente:
  ```bash
  sudo apt install mosquitto mosquitto-clients

## 🔁 Como Importar o Fluxo do Node-RED

Este repositório inclui um fluxo pronto do Node-RED para processar os dados do sensor e exibir informações de temperatura e umidade. Siga o passo a passo abaixo para importar o fluxo no seu ambiente local:

---

### 📥 Arquivo do Fluxo

O fluxo está localizado no arquivo Node-red weatherguard nesse repositório

---

### 🧭 Passo a Passo para Importar no Node-RED

1. **Abra o Node-RED** no seu navegador (geralmente em `http://localhost:1880`).
2. No canto superior direito, clique no botão de menu (☰) e selecione **"Import"**.
3. Clique em **"select a file to import"** ou cole o conteúdo do arquivo `flow.json`.
4. Escolha a opção **"Import to new flow"** ou **"Import to current flow"** conforme sua preferência.
5. Clique em **"Import"**.
6. Após a importação, clique em **Deploy** no canto superior direito para ativar o fluxo.

O nó `ui_gauge` pertence ao **Node-RED Dashboard**, que precisa ser instalado separadamente.

## 📦 Instalação do Node-RED Dashboard

### 1. Via terminal (recomendado)

Se você instalou o Node-RED via npm, abra o terminal e execute:

```bash
npm install node-red-dashboard
```

### 2. Via interface do Node-RED

1. Clique no botão ☰ no canto superior direito.
2. Vá em **Gerenciar paleta**.
3. Acesse a aba **Instalar**.
4. Busque por `node-red-dashboard`.
5. Clique em **Instalar**.

---

### 🚀 Acessando o Dashboard

Após instalar, os nós `ui_gauge`, `ui_chart`, `ui_text`, entre outros, estarão disponíveis na barra lateral esquerda.

Você poderá visualizar o dashboard acessando: http://localhost:1880/ui

---

### ⚠️ Observações Importantes

- Verifique se o **broker MQTT** está corretamente configurado no nó MQTT do fluxo.
- O fluxo espera receber dados no tópico: `weatherguard/monitoramento/clima`.


