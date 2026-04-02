/*******************************************************
 * Automatic Fan Control using ESP32 + DHT11
 * (Standalone - No WiFi or Blynk)
 * (Modified for Active-HIGH Relay)
 *******************************************************/

// Include necessary libraries
#include <DHT.h>

// --- Pin Definitions ---
#define DHT_PIN 4      // GPIO4 → DHT11 data pin
#define RELAY_PIN 5    // GPIO5 → Relay input pin
#define DHT_TYPE DHT11   // Sensor type

// --- Temperature threshold (°C) ---
const float TEMPERATURE_THRESHOLD = 28.0;

// Initialize DHT sensor
DHT dht(DHT_PIN, DHT_TYPE);

// --- Setup Function ---
void setup() {
  Serial.begin(115200);
  Serial.println("\n--- 🌡 Automatic Fan Control System ---");

  dht.begin();                   // Start DHT sensor
  pinMode(RELAY_PIN, OUTPUT);
  digitalWrite(RELAY_PIN, LOW);    // Ensure fan is OFF initially (for active-high relay)
}

// --- Main Loop ---
void loop() {
  // Wait for 2 seconds between readings
  delay(2000);

  // Read sensor values
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // Read temperature in Celsius

  // Check if any reads failed and exit early to try again.
  if (isnan(h) || isnan(t)) {
    Serial.println("❌ Failed to read from DHT sensor!");
    return;
  }

  // Print sensor data to the Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(t);
  Serial.print(" °C  |  Humidity: ");
  Serial.print(h);
  Serial.print(" %  |  ");

  // --- Fan Control Logic (Active HIGH) ---
  if (t > TEMPERATURE_THRESHOLD) {
    Serial.println("Fan Status: ON");
    digitalWrite(RELAY_PIN, HIGH);  // Turn ON fan
  } else {
    Serial.println("Fan Status: OFF");
    digitalWrite(RELAY_PIN, LOW);   // Turn OFF fan
  }
}
