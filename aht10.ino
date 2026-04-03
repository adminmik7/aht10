#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_AHTX0.h>

Adafruit_AHTX0 aht;

void setup() {
  Serial.begin(9600); // Changed to 9600 for better stability (like nano1602)
  delay(1000); // Wait for ESP to stabilize
  
  Serial.println("AHT10 Sensor Start");

  if (!aht.begin()) {
    Serial.println("Could not find AHT10. Check wiring!");
    while (1) delay(10);
  }
  Serial.println("AHT10 found!");
}

void loop() {
  sensors_event_t humidity, temp;
  aht.getEvent(&humidity, &temp);

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.print(" *C\t");
  
  Serial.print("Humidity: ");
  Serial.print(humidity.relative_humidity);
  Serial.println(" %");

  delay(2000);
}
