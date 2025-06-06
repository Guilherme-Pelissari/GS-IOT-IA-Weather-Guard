# 🌦️ WeatherGuard

WeatherGuard é um sistema de monitoramento de temperatura e umidade usando ESP32, sensor DHT22, MQTT, Node-RED e um aplicativo mobile feito em React Native. Ideal para aplicações de IoT e automação residencial.

---

## 📡 Visão Geral do Projeto

- 📍 **ESP32** lê dados do sensor **DHT22** (temperatura e umidade).
- 🔁 Envia os dados via **MQTT** no tópico `sensor/dht`.
- 🌐 **Node-RED** escuta o tópico e processa os dados.
- 📱 Aplicativo mobile **React Native** se conecta ao broker MQTT para exibir os dados em tempo real.

---

## 📷 Screenshot do Fluxo no Node-RED

![Node-RED Flow](./print-node-red.png)

> ⚠️ Nomeie o print da tela como `print-node-red.png` e coloque-o na raiz do repositório.

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

Instale as bibliotecas via **Arduino Library Manager**.

---

## 🔌 Fluxo de Funcionamento

1. **ESP32** conecta ao Wi-Fi.
2. Lê os dados do **DHT22**.
3. Envia via MQTT para o tópico `sensor/dht`.
4. **Node-RED** recebe os dados e os encaminha para debug e/ou dashboard.
5. O **app React Native** também consome os dados em tempo real.

---

## 🧪 Testando o Sistema

### 1. Configurar Broker MQTT
- Use o [HiveMQ Broker público](https://www.hivemq.com/demos/websocket-client/) ou instale o Mosquitto localmente:
  ```bash
  sudo apt install mosquitto mosquitto-clients
