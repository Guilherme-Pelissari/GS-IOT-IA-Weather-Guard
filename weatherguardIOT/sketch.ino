#include <WiFi.h>
#include <PubSubClient.h>
#include <DHTesp.h>
#include <LiquidCrystal_I2C.h>
// Definição dos pinos para o sensor DHT22 e sliders
#define DHTPIN 18 
#define TEMP_SLIDER_PIN 34 
#define HUMIDITY_SLIDER_PIN 35 
DHTesp dht;
// Configurações de rede WiFi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
// Configurações do servidor MQTT
const char* mqtt_server = "broker.hivemq.com";
const char* mqtt_topic = "weatherguard/monitoramento/clima";
// Objetos para conexão WiFi e MQTT
WiFiClient espClient;
PubSubClient client(espClient);
// Definição dos pinos para LEDs
const int LED_RED = 27;  
const int LED_BLUE = 26; 
// Inicialização do display LCD I2C
LiquidCrystal_I2C lcd(0x27, 20, 4); 
// Função para conectar à rede WiFi
void setup_wifi() {
  delay(10);
  Serial.println("Conectando ao WiFi...");
  WiFi.begin(ssid, password);
  int attempts = 0;
  while (WiFi.status() != WL_CONNECTED && attempts < 20) {
    delay(500);
    Serial.print(".");
    attempts++;
  }
  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nConectado ao WiFi");
    Serial.print("Endereço IP: ");
    Serial.println(WiFi.localIP());
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    Serial.println("\nFalha ao conectar ao WiFi.");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
}
// Função para reconectar ao broker MQTT
void reconnect() {
  int attempts = 0;
  while (!client.connected() && attempts < 3) {
    Serial.print("Tentando conectar ao MQTT...");
    String clientId = "ESP32Client-" + String(random(0xffff), HEX);
    if (client.connect(clientId.c_str())) {
      Serial.println("conectado");
      digitalWrite(LED_BLUE, HIGH);
      digitalWrite(LED_RED, LOW);
    } else {
      Serial.print("falhou, rc=");
      Serial.print(client.state());
      Serial.println(" tentando novamente em 5 segundos");
      delay(5000);
      attempts++;
    }
  }
  if (!client.connected()) {
    Serial.println("Falha ao conectar ao MQTT.");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }
}
// Função de inicialização
void setup() {
  pinMode(LED_RED, OUTPUT);
  pinMode(LED_BLUE, OUTPUT);
  digitalWrite(LED_RED, LOW);
  digitalWrite(LED_BLUE, LOW);

  pinMode(TEMP_SLIDER_PIN, INPUT);
  pinMode(HUMIDITY_SLIDER_PIN, INPUT);

  Serial.begin(115200);
  Serial.println("Inicializando sistema...");

  Serial.println("Inicializando sensor DHT22...");
  dht.setup(DHTPIN, DHTesp::DHT22);
  delay(8000);

  TempAndHumidity test = dht.getTempAndHumidity();
  Serial.print("Teste inicial - Temp: ");
  Serial.println(test.temperature);
  Serial.print("Teste inicial - Umidade: ");
  Serial.println(test.humidity);

  setup_wifi();
  client.setServer(mqtt_server, 1883);

  lcd.init();
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");
}
// Loop principal
void loop() {
  if (WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi desconectado. Tentando reconectar...");
    setup_wifi();
  }

  if (WiFi.status() == WL_CONNECTED && !client.connected()) {
    reconnect();
  }

  client.loop();

  
  int tempRaw = analogRead(TEMP_SLIDER_PIN);
  int humidityRaw = analogRead(HUMIDITY_SLIDER_PIN);

  
  float t = map(tempRaw, 0, 4095, 0, 50);
  float h = map(humidityRaw, 0, 4095, 0, 100);

  
  TempAndHumidity data = dht.getTempAndHumidity();
  if (isnan(data.temperature) || isnan(data.humidity)) {
    Serial.println("Usando valores dos sliders...");
  } else {
    
    if (tempRaw < 50) t = data.temperature;
    if (humidityRaw < 50) h = data.humidity;
  }
  // Verifica se os valores são válidos
  if (isnan(t) || isnan(h)) {
    Serial.println("Falha ao ler valores: valor NaN detectado.");
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Erro na leitura");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
    delay(2000);
    return;
  }
  // Exibe valores no monitor serial
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println(" °C");
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.println(" %");
  // Atualiza o display LCD
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temperatura: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Umidade: ");
  lcd.print(h);
  lcd.print(" %");
  lcd.setCursor(0, 2);
  lcd.print("WiFi: ");
  lcd.print(WiFi.status() == WL_CONNECTED ? "Conectado" : "Desconectado");
  lcd.setCursor(0, 3);
  lcd.print("MQTT: ");
  lcd.print(client.connected() ? "Conectado" : "Desconectado");
  // Cria a mensagem JSON para o MQTT
  String payload = "{";
  payload += "\"temperatura\":";
  payload += t;
  payload += ",\"umidade\":";
  payload += h;
  payload += "}";
  // Exibe a mensagem no monitor serial
  Serial.print("Publicando no tópico MQTT: ");
  Serial.println(payload);
  // Publica a mensagem no MQTT, se conectado
  if (client.connected()) {
    client.publish(mqtt_topic, payload.c_str());
    Serial.println("Mensagem publicada com sucesso!");
    digitalWrite(LED_BLUE, HIGH);
    digitalWrite(LED_RED, LOW);
  } else {
    Serial.println("MQTT não conectado. Mensagem não publicada.");
    digitalWrite(LED_RED, HIGH);
    digitalWrite(LED_BLUE, LOW);
  }

  delay(5000);
}
