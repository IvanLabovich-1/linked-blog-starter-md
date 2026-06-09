#include <esp_now.h>
#include <WiFi.h>
#include <ESP32Servo.h>

const int servoPin = 25; 
Servo myServo;

typedef struct struct_message {
  int throttle;
} struct_message;

struct_message incomingData;
a
// Callback updated for ESP32 Arduino Core v3.0+
void OnDataRecv(const esp_now_recv_info *info, const uint8_t *incomingDataPtr, int len) {
  memcpy(&incomingData, incomingDataPtr, sizeof(incomingData));
  
  // Move the micro servo to the received 0-180 angle
  myServo.write(incomingData.throttle);
}

void setup() {
  // Allow allocation of all hardware timers for servo control
  ESP32PWM::allocateTimer(0);
  ESP32PWM::allocateTimer(1);
  ESP32PWM::allocateTimer(2);
  ESP32PWM::allocateTimer(3);
  
  myServo.setPeriodHertz(50); // Standard 50Hz servo frequency
  myServo.attach(servoPin, 500, 2400); 
  myServo.write(0); // Start at 0 degrees safely for system initialization

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    return;
  }
  
  // Register receive callback
  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // Driven entirely by the wireless interrupt callback
}