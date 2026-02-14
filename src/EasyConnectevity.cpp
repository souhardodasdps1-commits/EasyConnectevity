#include "EasyConnectevity.h"

// ----------------------------
// CONSTRUCTOR
// ----------------------------
EasyConnectevity::EasyConnectevity() {
  // Nothing to initialize yet
}

// ----------------------------
// NETWORK FUNCTIONS
// ----------------------------
bool EasyConnectevity::connectNetwork(const char* ssid, const char* password) {
#if defined(ESP32) || defined(ESP8266)
  Serial.print("Connecting to WiFi: ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  int retry = 0;
  while (WiFi.status() != WL_CONNECTED && retry < 30) { // Retry ~15 seconds
    delay(500);
    Serial.print(".");
    retry++;
  }

  if(WiFi.status() == WL_CONNECTED) {
    Serial.println();
    Serial.print("Connected! IP Address: ");
    Serial.println(WiFi.localIP());
    return true;
  } else {
    Serial.println();
    Serial.println("Failed to connect to WiFi");
    return false;
  }
#else
  Serial.println("WiFi functions only available on ESP32/ESP8266 boards");
  return false;
#endif
}

// ----------------------------
// SENSOR FUNCTIONS
// ----------------------------
int EasyConnectevity::smoothValue(int raw, int pin) {
  static int last[20];  // 20-sample smoothing
  static int idx = 0;
  last[idx++] = raw;
  if(idx >= 20) idx = 0;

  long sum = 0;
  for(int i = 0; i < 20; i++) sum += last[i];
  return sum / 20;
}

int EasyConnectevity::readSensor(uint8_t pin) {
  int raw = analogRead(pin);
  return smoothValue(raw, pin);
}

// ----------------------------
// ACTUATOR FUNCTIONS
// ----------------------------
void EasyConnectevity::controlPin(uint8_t pin, bool state) {
  pinMode(pin, OUTPUT);
  digitalWrite(pin, state ? HIGH : LOW);
}

// ----------------------------
// CLOUD FUNCTIONS
// ----------------------------
bool EasyConnectevity::sendToCloud(int value, const char* service) {
#if defined(ESP32) || defined(ESP8266)
  if(WiFi.status() != WL_CONNECTED) {
    Serial.println("WiFi not connected, cannot send data to cloud");
    return false;
  }

  Serial.print("Sending value ");
  Serial.print(value);
  Serial.print(" to cloud service: ");
  Serial.println(service);

  // ThingSpeak example
  if(String(service) == "ThingSpeak") {
    WiFiClient client;
    const char* host = "api.thingspeak.com";
    const char* apiKey = "YOUR_API_KEY"; // Replace with your ThingSpeak channel write API key
    String url = "/update?api_key=" + String(apiKey) + "&field1=" + String(value);

    if(client.connect(host, 80)) {
      client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                   "Host: " + host + "\r\n" +
                   "Connection: close\r\n\r\n");
      client.stop();
      Serial.println("Value sent to ThingSpeak");
      return true;
    } else {
      Serial.println("Failed to connect to ThingSpeak");
      return false;
    }
  }

  Serial.println("Service not implemented");
  return false;
#else
  Serial.println("Cloud functions only available on ESP32/ESP8266 boards");
  return false;
#endif
}
