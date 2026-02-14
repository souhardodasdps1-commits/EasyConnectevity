#include <EasyConnectevity.h>

EasyConnectevity ec;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi (ESP32/ESP8266 only)
  if (ec.connectNetwork("YourSSID", "YourPassword")) {
    Serial.println("WiFi Connected!");
  } else {
    Serial.println("WiFi Failed!");
  }
}

void loop() {
  // Read sensor value from A0
  int sensorVal = ec.readSensor(A0);
  Serial.print("Sensor value: ");
  Serial.println(sensorVal);

  // Send sensor value to ThingSpeak
  bool sent = ec.sendToCloud(sensorVal, "ThingSpeak");
  if(sent){
    Serial.println("Value sent to ThingSpeak successfully!");
  } else {
    Serial.println("Failed to send value to ThingSpeak");
  }

  delay(5000); // Wait 5 seconds before reading again
}
