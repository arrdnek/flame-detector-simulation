// Include libraries
#include <MQ135.h>

// Define pins
#define PIN_MQ135 A0 // Pin untuk sensor MQ135
#define FLAME_SENSOR_PIN 7 // Pin untuk sensor api
#define LED_PIN 13 // Pin LED untuk menunjukkan keberadaan api atau CO2 yang tinggi

// Create instances
MQ135 gasSensor = MQ135(PIN_MQ135);

void setup() {
  pinMode(LED_PIN, OUTPUT); // Set pin LED sebagai output
  pinMode(FLAME_SENSOR_PIN, INPUT); // Set pin sensor api sebagai input
  Serial.begin(9600); // Inisialisasi komunikasi serial
}

void loop() {
  // Membaca nilai CO2 dari sensor MQ135
  float ppm = gasSensor.getPPM();

  // Membaca nilai dari sensor api
  int flameState = digitalRead(FLAME_SENSOR_PIN);

  // Pemeriksaan skenario yang dijelaskan
  if (flameState == LOW && ppm > 400) {
    Serial.println("PERINGATAN: Ada api dan CO2 tinggi! (CO2 lebih dari 400 ppm)");
    digitalWrite(LED_PIN, HIGH); // Nyalakan LED jika ada api dan CO2 tinggi
  } else if (flameState == LOW && ppm <= 400) {
    Serial.println("Ada api, tapi CO2 rendah. (CO2 kurang dari atau sama dengan 400 ppm)");
    digitalWrite(LED_PIN, HIGH); // Nyalakan LED jika ada api saja
  } else if (flameState == HIGH && ppm > 400) {
    Serial.println("Tidak ada api, tapi CO2 tinggi. (CO2 lebih dari 400 ppm)");
    digitalWrite(LED_PIN, HIGH); // Nyalakan LED jika hanya CO2 tinggi
  } else {
    Serial.println("Aman: Tidak ada api atau CO2 tinggi. (CO2 kurang dari atau sama dengan 400 ppm)");
    digitalWrite(LED_PIN, LOW); // Matikan LED jika tidak ada api atau CO2 tinggi
  }

  delay(1000); // Delay 1 detik antara setiap pembacaan
}
