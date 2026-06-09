#include <esp_now.h>
#include <WiFi.h>

const int potPin = 34;
const int ledPin = 2; // Most ESP32 boards use GPIO2 for the onboard LED

// Your exact receiver MAC address
uint8_t receiverAddress[] = {0x14, 0x33, 0x5C, 0x2F, 0x28, 0x40};

typedef struct struct_message {
  int throttle;
} struct_message;

struct_message myData;
esp_now_peer_info_t peerInfo;

// Callback updated for ESP32 Arduino Core v3.0+
void OnDataSent(const wifi_tx_info_t *tx_info, esp_now_send_status_t status) {
  if (status == ESP_NOW_SEND_SUCCESS) {
    digitalWrite(ledPin, HIGH); // Solid light means connected and transmitting
  } else {
    digitalWrite(ledPin, !digitalRead(ledPin)); // Blinking means connection lost
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(potPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Init ESP-NOW
  if (esp_now_init() != ESP_OK) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }

  // Register send callback
  esp_now_register_send_cb(OnDataSent);
  
  // Register peer
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;  
  peerInfo.encrypt = false;
  
  if (esp_now_add_peer(&peerInfo) != ESP_OK){
    Serial.println("Failed to add peer");
    return;
  }
}

void loop() {
  // Read the thumbwheel
  int rawValue = analogRead(potPin);
  
  // Map 12-bit ADC (0-4095) to a standard 0-180 degree range for the servo
  // Replace 1200 and 2800 with the actual min/max numbers from your Serial Monitor 
  myData.throttle = map(rawValue, 0, 4095, 0, 180); 
  myData.throttle = constrain(myData.throttle, 0, 180);

  // Send message via ESP-NOW
  esp_err_t result = esp_now_send(receiverAddress, (uint8_t *) &myData, sizeof(myData));
  
  // Print values to Serial Monitor
  Serial.print("Potentiometer Value: ");
  Serial.print(rawValue);
  Serial.print(" | Sent Angle: ");
  Serial.println(myData.throttle);
  
  delay(50); // 20Hz update frequency for responsive servo control
}