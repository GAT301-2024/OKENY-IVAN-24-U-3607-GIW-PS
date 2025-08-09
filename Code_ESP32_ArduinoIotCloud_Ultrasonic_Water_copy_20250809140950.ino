#include "DHT.h"

// Define the pin connected to the sensor
#define DHTPIN 4

// Define sensor type (DHT11 or DHT22)
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(115200);
  Serial.println("DHT Sensor Reading - Offline Example");
  dht.begin();
}

void loop() {
  delay(2000);  // Wait 2 seconds between readings

  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%  ");

  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" °C");
}
