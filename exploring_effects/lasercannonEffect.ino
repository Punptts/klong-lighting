#include <FastLED.h>

#define LED_PIN_1 12 // Define the LED data pin
#define LED_PIN_2 13 // Define the LED data pin
#define NUM_LEDS 1200 // Total number of LEDs in strip
#define BRIGHTNESS 100 // LED strip brightness (0-255)
#define COLOR_ORDER RBG

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN_1, RBG>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_2, RBG>(leds_2, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  laserCannonEffect(0xFF0000, 50); // Red laser cannon effect with 50ms delay per step
}

void laserCannonEffect(uint32_t color, uint16_t delayTime) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_1[i] = color;
    leds_2[i] = color;
    FastLED.show();
    delay(delayTime);
    leds_1[i] = CRGB::Black; // Turn off LED at position i on strip 1
    leds_2[i] = CRGB::Black; // Turn off LED at position i on strip 2
  }
}
