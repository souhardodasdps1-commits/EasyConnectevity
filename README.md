# EasyConnectevity

**EasyConnectevity** is a beginner-friendly Arduino/ESP library that makes it super easy to:

- Connect ESP32/ESP8266 boards to WiFi  
- Read analog or digital sensors with smoothing  
- Control LEDs, relays, and other actuators  
- Send sensor data to cloud services like ThingSpeak  

It works with **all Arduino boards** (Uno, Mega, Nano) and **all ESP boards** (ESP32, ESP8266, Wemos, NodeMCU).

---

## Features

- Plug-and-play library for Arduino IDE  
- Supports **WiFi-enabled ESP boards** for IoT projects  
- Smooth analog sensor readings to reduce noise  
- Simple digital pin control for actuators  
- Cloud integration with ThingSpeak (fully functional example included)  
- Beginner-friendly API with minimal code  

---

## Supported Boards

| Board type | Features supported |
|------------|------------------|
| ESP32 / ESP8266 / Wemos / NodeMCU | WiFi, sensor reading, pin control, cloud integration |
| Arduino Uno / Mega / Nano / Leonardo | Sensor reading, pin control (WiFi functions show warning) |

---

## Installation

1. Download the repository as a ZIP file from GitHub  
2. Open Arduino IDE → **Sketch → Include Library → Add .ZIP Library**  
3. Select the ZIP file and click **Open**  
4. Done! `EasyConnectevity` is ready to use  

---

## Usage Example

```cpp
#include <EasyConnectevity.h>

EasyConnectevity ec;

void setup() {
  Serial.begin(115200);

  // Connect to WiFi (ESP only)
  if(ec.connectNetwork("YourSSID", "YourPassword")) {
    Serial.println("WiFi Connected!");
  } else {
    Serial.println("WiFi Failed!");
  }
}

void loop() {
  // Read sensor from A0
  int sensorVal = ec.readSensor(A0);
  Serial.print("Sensor value: ");
  Serial.println(sensorVal);

  // Control LED on pin 5 based on sensor value
  ec.controlPin(5, sensorVal > 500);

  // Send sensor value to ThingSpeak
  ec.sendToCloud(sensorVal, "ThingSpeak");

  delay(5000);
}
Note: Replace "YourSSID" and "YourPassword" with your WiFi credentials and "YOUR_API_KEY" in EasyConnectevity.cpp with your ThingSpeak channel key.

Example Sketches
examples/TemperatureMonitor/TemperatureMonitor.ino → Reads sensor values and sends to ThingSpeak

examples/LEDTrigger/LEDTrigger.ino → Controls LED based on sensor reading

Cloud Integration
ThingSpeak:

ThingSpeak is a free IoT cloud platform to store and visualize sensor data

Create a free account on ThingSpeak

Create a channel → get your API key

Replace "YOUR_API_KEY" in the .cpp file

Sensor data from ESP boards will appear as live graphs online

License
This library is released under the MIT License.
See LICENSE file for details.

Author
Souhardo Das
Email: souhardodasdps1@gmail.com
GitHub:Souhardo Das
GitHub: YOUR_GITHUB_USERNAME

