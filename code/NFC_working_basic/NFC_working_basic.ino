/*
  Radio Game code testing NFC
  Nov 10, 2025
*/


#include <Wire.h>
#include <PN532_I2C.h>
#include <PN532.h>

#define SDA_PIN D4
#define SCL_PIN D5

PN532_I2C pn532_i2c(Wire);
PN532 nfc(pn532_i2c);

void setup(void) {
  Serial.begin(115200);
  // Disable I2C master error logging to clean serial output
  esp_log_level_set("i2c", ESP_LOG_NONE);
  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);

  Serial.println("🔸 Initializing PN532...");
  nfc.begin();

  uint32_t versiondata = nfc.getFirmwareVersion();
  if (!versiondata) {
    Serial.println("PN532 not found");
    while (1)
      ;
  }

  Serial.print("Found PN5");
  Serial.println((versiondata >> 24) & 0xFF, HEX);

  Serial.println("Configuring SAM (reader mode)...");
  nfc.SAMConfig();  // Switch PN532 to "reader" mode

  Serial.println("Ready to scan NFC cards...");
}

void loop(void) {
  uint8_t uid[7];
  uint8_t uidLength;

  Serial.println("📡 Waiting for a card...");
  if (nfc.readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {
    Serial.print("UID: ");
    for (uint8_t i = 0; i < uidLength; i++) {
      if (uid[i] < 0x10) Serial.print("0");
      Serial.print(uid[i], HEX);
      if (i < uidLength - 1) Serial.print(" ");
    }
    Serial.println();
    delay(2000);
  }

  delay(500);
}
