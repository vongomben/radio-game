#include <FastLED.h>


/*
  Radio Game code testing LED
  based on Fastled Library
  Nov 10, 2025
*/

// -------------------------------------------------------
#define LED_DATA_PIN  D0         // Data pin connected to the LED strip
#define NUM_LEDS      16         // Total number of LEDs in the strip
#define LED_TYPE      WS2812     // Type of LED strip (WS2812 / WS2812B / NeoPixel)
#define COLOR_ORDER   GRB        // Most WS2812 strips use GRB order
#define BRIGHTNESS    120        // Global brightness (0 - 255)

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(115200);
  delay(500);

  // Initialize the LED strip
  FastLED.addLeds<LED_TYPE, LED_DATA_PIN, COLOR_ORDER>(leds, NUM_LEDS)
         .setCorrection(TypicalLEDStrip);

  FastLED.setBrightness(BRIGHTNESS);

  Serial.println("FastLED LED Test");
}

void loop() {
  // Test 1: Fill the strip with red
  fill_solid(leds, NUM_LEDS, CRGB::Red);
  FastLED.show();
  delay(1000);

  // Test 2: Fill the strip with green
  fill_solid(leds, NUM_LEDS, CRGB::Green);
  FastLED.show();
  delay(1000);

  // Test 3: Fill the strip with blue
  fill_solid(leds, NUM_LEDS, CRGB::Blue);
  FastLED.show();
  delay(1000);

  // Test 4: Rainbow animation sweep
  static uint8_t hue = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue + (i * 4), 255, 255);
  }
  FastLED.show();
  hue++;
  delay(30);
}
