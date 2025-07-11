#include <Arduino.h>
#include <Wiegand.h> 

// Wiegand okuyucunun D0 ve D1 pinlerinin bağlı olduğu ESP32 pinleri
#define PIN_D0 14 
#define PIN_D1 16

WIEGAND wiegand;

void setup() {
    Serial.begin(115200);
    Serial.println("Wiegand RFID Okuyucu Testi Başladı.");
    Serial.println("D0 -> GPIO 14, D1 -> GPIO 16");
    Serial.println("Lütfen bir kart okutun...");

    wiegand.begin(PIN_D0, PIN_D1);
}

void loop() {
    
    if (wiegand.available()) {
        Serial.print("Wiegand Kodu Alındı: ");
  
        Serial.print(wiegand.getCode()); 
        
        Serial.print(" - Bit Sayısı: ");
        Serial.println(wiegand.getWiegandType());
    }
    
    delay(50);
}