#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>

// --- НАСТРОЙКИ ---
const char* ssid = "YOUR_WIFI_SSID";
const char* password = "YOUR_WIFI_PASSWORD";
const char* mqtt_server = "192.168.0.67"; // IP твоего Home Assistant
const int mqtt_port = 1883;
const char* mqtt_user = ""; // Если MQTT с паролем
const char* mqtt_pass = ""; // Пароль MQTT

// Уникальный ID для HA Auto Discovery
#define DEVICE_ID "aht10_esp12e"
#define DEVICE_NAME "AHT10 Sensor"

WiFiClient espClient;
PubSubClient client(espClient);
Adafruit_AHTX0 aht;

unsigned long lastMsg = 0;
#define MSG_BUFFER_SIZE (50)
char msg[MSG_BUFFER_SIZE];

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // Обработка входящих сообщений (пока пусто)
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect(DEVICE_ID, mqtt_user, mqtt_pass)) {
      Serial.println("connected");
      ha_autodiscovery();
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void ha_autodiscovery() {
  // Temperature Sensor Discovery
  String topic = "homeassistant/sensor/" + String(DEVICE_ID) + "/temperature/config";
  String payload = "{";
  payload += "\"name\":\"" + String(DEVICE_NAME) + " Temperature\",";
  payload += "\"state_topic\":\"home/" + String(DEVICE_ID) + "/state\",";
  payload += "\"unit_of_measurement\":\"°C\",";
  payload += "\"value_template\":\"{{ value_json.temperature }}\",";
  payload += "\"device\":{\"identifiers\":[\"" + String(DEVICE_ID) + "\"],\"name\":\"" + String(DEVICE_NAME) + " \"},";
  payload += "\"unique_id\":\"" + String(DEVICE_ID) + "_temp\"";
  payload += "}";
  
  client.publish(topic.c_str(), payload.c_str(), true);

  // Humidity Sensor Discovery
  topic = "homeassistant/sensor/" + String(DEVICE_ID) + "/humidity/config";
  payload = "{";
  payload += "\"name\":\"" + String(DEVICE_NAME) + " Humidity\",";
  payload += "\"state_topic\":\"home/" + String(DEVICE_ID) + "/state\",";
  payload += "\"unit_of_measurement\":\"%\",";
  payload += "\"value_template\":\"{{ value_json.humidity }}\",";
  payload += "\"device\":{\"identifiers\":[\"" + String(DEVICE_ID) + "\"],\"name\":\"" + String(DEVICE_NAME) + " \"},";
  payload += "\"unique_id\":\"" + String(DEVICE_ID) + "_hum\"";
  payload += "}";
  
  client.publish(topic.c_str(), payload.c_str(), true);
  Serial.println("HA Auto-Discovery sent.");
}

void setup() {
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, mqtt_port);
  client.setCallback(callback);

  if (!aht.begin()) {
    Serial.println("Could not find AHT10. Check wiring!");
    while (1) delay(10);
  }
  Serial.println("AHT10 found!");
  ha_autodiscovery();
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  unsigned long now = millis();
  if (now - lastMsg > 5000) {
    lastMsg = now;
    
    sensors_event_t humidity, temp;
    aht.getEvent(&humidity, &temp);

    StaticJsonDocument<200> doc;
    doc["temperature"] = temp.temperature;
    doc["humidity"] = humidity.relative_humidity;
    
    char jsonBuffer[512];
    serializeJson(doc, jsonBuffer);
    
    client.publish(("home/" + String(DEVICE_ID) + "/state").c_str(), jsonBuffer, true);
    
    Serial.print("Temperature: ");
    Serial.print(temp.temperature);
    Serial.print(" *C\t");
    Serial.print("Humidity: ");
    Serial.print(humidity.relative_humidity);
    Serial.println(" %");
  }
}
