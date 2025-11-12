#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

/*
  Radio Game code testing OLED Screen
  I2C pin mapping (edit these if different on your board)
  Nov 10, 2025


*/


// -------------------------------------------------------
// I2C pin mapping (edit these if different on your board)
// -------------------------------------------------------
#define OLED_SDA_PIN  D4
#define OLED_SCL_PIN  D5

// Display configuration
#define SCREEN_WIDTH   128
#define SCREEN_HEIGHT  32
#define OLED_RESET     -1        // Some modules do not use reset pin
#define OLED_ADDRESS   0x3C      // Most 128x32 displays use 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("OLED SSD1306 Test");

  // Initialize I2C bus
  Wire.begin(OLED_SDA_PIN, OLED_SCL_PIN);
  Wire.setClock(100000);

  // Initialize display
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS)) {
    Serial.println("SSD1306 not detected on I2C address 0x3C");
    while (true) {
      // Stop execution here if display is not found
    }
  }

  Serial.println("OLED initialized successfully");

  // Clear buffer
  display.clearDisplay();

  // Draw test text
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("SSD1306 Test");
  display.println("128 x 32 I2C Display");
  display.println("Interface OK");

  // Send to display
  display.display();
}

void loop() {
  // Simple blinking cursor to show that the program is running

  display.setCursor(0, 24);
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.print("ON ");
  display.display();
  delay(500);

  display.setCursor(0, 24);
  display.setTextColor(SSD1306_BLACK);
  display.print("ON ");
  display.display();
  delay(500);
}
