#define SENSOR_PIN 33 // Use the appropriate analog pin (GPIO36 is A0 on some ESP32 boards)

void setup() {
  Serial.begin(115200); // Initialize serial communication at 115200 baud rate
  pinMode(SENSOR_PIN, INPUT); // Set the analog pin as INPUT
}

void loop() {
  int rawValue = analogRead(SENSOR_PIN); // Read the analog value from the sensor
  float voltage = (rawValue / 4095.0) * 3.3; // Convert the raw value to voltage
  Serial.print("Raw ECG Sensor Value: ");
  Serial.print(rawValue);
  Serial.print(" | Voltage: ");
  Serial.println(voltage, 4); // Print the voltage with 4 decimal places
  delay(500); // Delay to avoid spamming the Serial Monitor
}
