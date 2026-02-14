#pragma once
#include <Arduino.h>

// Include WiFi libraries for ESP boards
#if defined(ESP32)
  #include <WiFi.h>
#elif defined(ESP8266)
  #include <ESP8266WiFi.h>
#else
  #warning "EasyConnectevity: WiFi functions will only work on ESP32 or ESP8266"
#endif

class EasyConnectevity {
  public:
    // ----------------------------
    // CONSTRUCTOR
    // ----------------------------
    /**
     * Initialize EasyConnectevity library
     */
    EasyConnectevity();

    // ----------------------------
    // NETWORK FUNCTIONS
    // ----------------------------
    /**
     * Connect the ESP board to a WiFi network
     * @param ssid - WiFi SSID
     * @param password - WiFi password
     * @return true if successfully connected, false if failed
     */
    bool connectNetwork(const char* ssid, const char* password);

    // ----------------------------
    // SENSOR FUNCTIONS
    // ----------------------------
    /**
     * Read a sensor value from a pin
     * Works for analog or digital pins
     * @param pin - Arduino pin number
     * @return int value (0-1023 for analog, 0/1 for digital)
     */
    int readSensor(uint8_t pin);

    // ----------------------------
    // ACTUATOR FUNCTIONS
    // ----------------------------
    /**
     * Control a digital pin (LED, relay, etc.)
     * @param pin - Arduino pin number
     * @param state - true/HIGH = ON, false/LOW = OFF
     */
    void controlPin(uint8_t pin, bool state);

    // ----------------------------
    // CLOUD FUNCTIONS
    // ----------------------------
    /**
     * Send a sensor value to a cloud service
     * Example: ThingSpeak, MQTT, etc.
     * @param value - integer value to send
     * @param service - service name string
     * @return true if successfully sent, false otherwise
     */
    bool sendToCloud(int value, const char* service);

  private:
    // ----------------------------
    // INTERNAL HELPER FUNCTIONS
    // ----------------------------
    /**
     * Smooth analog readings to reduce fluctuations
     * @param raw - raw analog reading
     * @param pin - pin number
     * @return smoothed value
     */
    int smoothValue(int raw, int pin);
};
