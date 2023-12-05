#include <FastLED.h>

#define LED_PIN_1 12   // Define the LED data pin for strip 1
#define LED_PIN_2 13   // Define the LED data pin for strip 2
#define NUM_LEDS 1200  // Total number of LEDs in each strip
#define BRIGHTNESS 50  // LED strip brightness (0-255)

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  movingEffect(leds_1);
  movingEffect(leds_2);
  FastLED.show();
}

void movingEffect(CRGB leds[]) {
  EVERY_N_MILLISECONDS(100) {
    // Create a new HSV color for leds[0]
    leds_1[0] = CHSV(86, random8(), random8(96, 99));
    leds_2[0] = CHSV(86, random8(), random8(96, 99));

    // Copy each pixel to the next one, starting at the far end
    // thereby 'moving' the pattern along the strip
    for (int i = NUM_LEDS - 1; i > 0; i--) {
      leds_1[i] = leds_1[i - 1];
    }
    for (int i = NUM_LEDS - 1; i > 0; i--) {
      leds_2[i] = leds_2[i - 1];
    }
  }
}
