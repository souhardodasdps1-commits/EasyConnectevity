#include <EasyConnectevity.h>

EasyConnectevity ec;

void setup() {
  Serial.begin(115200);

  // Set pin 5 as output (LED or relay)
  pinMode(5, OUTPUT);
  Serial.println("LEDTrigger example started");
}

void loop() {
  // Read analog sensor value from A0
  int val = ec.readSensor(A0);
  Serial.print("Sensor value: ");
  Serial.println(val);

  // Control LED: turn ON if sensor value > 500, else OFF
  ec.controlPin(5, val > 500);

  delay(500); // Small delay for responsiveness
}
