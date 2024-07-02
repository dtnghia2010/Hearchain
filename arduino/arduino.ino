#include <ESP8266WiFi.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

const char* ssid = "your_SSID";
const char* password = "your_PASSWORD";
const char* serverIP = "192.168.1.100"; // Raspberry Pi IP address
const int serverPort = 5000; // Port to communicate with Raspberry Pi

WiFiClient client;

void setup() {
  Serial.begin(115200);
  dht.begin();
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
}

void loop() {
  float humidity = dht.readHumidity();
  float temperature = dht.readTemperature();

  if (isnan(humidity) || isnan(temperature)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  if (client.connect(serverIP, serverPort)) {
    String data = "Temp=" + String(temperature) + "C Humidity=" + String(humidity) + "%";
    client.println(data);
    Serial.println("Data sent: " + data);
    client.stop();
  } else {
    Serial.println("Connection to server failed");
  }

  delay(2000); // Wait 2 seconds between readings
}
