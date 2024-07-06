#include <HardwareSerial.h>

// Sử dụng UART2 cho SIM800L (TX2 = GPIO17, RX2 = GPIO16)
HardwareSerial sim800l(2);

const int ecgPin = 36; // Pin ADC của ESP32 kết nối với OUTPUT của AD8232

void setup() {
  Serial.begin(115200);
  sim800l.begin(9600, SERIAL_8N1, 16, 17); // Khởi tạo UART2

  // Đợi SIM800L khởi động
  delay(1000);

  // Khởi động và kiểm tra kết nối với SIM800L
  sim800l.println("AT");
  delay(100);
  if (sim800l.available()) {
    Serial.println(sim800l.readString());
  }

  // Thiết lập kết nối mạng di động
  sim800l.println("AT+CSQ"); // Kiểm tra cường độ tín hiệu
  delay(100);
  Serial.println(sim800l.readString());

  sim800l.println("AT+CREG?"); // Kiểm tra đăng ký mạng
  delay(100);
  Serial.println(sim800l.readString());

  sim800l.println("AT+CGATT=1"); // Đính kèm GPRS
  delay(1000);
  Serial.println(sim800l.readString());

  sim800l.println("AT+CIPSHUT"); // Đảm bảo mọi kết nối trước đó đều đóng
  delay(1000);
  Serial.println(sim800l.readString());

  sim800l.println("AT+CIPMUX=0"); // Cài đặt chế độ kết nối đơn
  delay(1000);
  Serial.println(sim800l.readString());

  sim800l.println("AT+CSTT=\"your_apn\",\"your_user\",\"your_pass\""); // Thiết lập APN
  delay(1000);
  Serial.println(sim800l.readString());

  sim800l.println("AT+CIICR"); // Khởi tạo kết nối không dây
  delay(3000);
  Serial.println(sim800l.readString());

  sim800l.println("AT+CIFSR"); // Lấy địa chỉ IP
  delay(2000);
  Serial.println(sim800l.readString());
}

void loop() {
  int ecgValue = analogRead(ecgPin); // Đọc giá trị ECG từ AD8232

  // Gửi dữ liệu ECG đến server qua HTTP POST
  sendToServer(ecgValue);

  delay(10000); // Gửi dữ liệu mỗi 10 giây
}

void sendToServer(int ecgValue) {
  sim800l.println("AT+CIPSTART=\"TCP\",\"your_server\",\"your_port\""); // Kết nối đến server
  delay(2000);
  Serial.println(sim800l.readString());

  String postData = "data=" + String(ecgValue);

  sim800l.print("AT+CIPSEND="); // Gửi dữ liệu
  sim800l.println(postData.length());
  delay(100);
  if (sim800l.available()) {
    Serial.println(sim800l.readString());
  }

  sim800l.print(postData);
  delay(1000);
  if (sim800l.available()) {
    Serial.println(sim800l.readString());
  }

  sim800l.println("AT+CIPCLOSE"); // Đóng kết nối
  delay(1000);
  Serial.println(sim800l.readString());
}
