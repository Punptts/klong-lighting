// Make it blink //

#include <FastLED.h>

#define LED_PIN_1     12  // Pin for LED strip 1
#define LED_PIN_2     13  // Pin for LED strip 2
#define NUM_LEDS      1200 // Number of LEDs in each strip (adjustable)

CRGB leds_1[NUM_LEDS];  // Array for LED strip 1
CRGB leds_2[NUM_LEDS];  // Array for LED strip 2

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(leds_1, NUM_LEDS); // Initialize LED strip 1
  FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(leds_2, NUM_LEDS); // Initialize LED strip 2
  FastLED.setBrightness(100); // Set the brightness (adjustable)
}

void loop() {
  waterEffect();
  FastLED.show();
}

void waterGradientEffect() {
  static uint8_t hue_1 = 0; // Starting hue value for strip 1
  static uint8_t hue_2 = 128; // Starting hue value for strip 2

  for (int i = 0; i < NUM_LEDS; i++) {
    leds_1[i] = CHSV(hue_1 + (i * 3), 255, 255); // Adjust parameters for strip 1
    leds_2[i] = CHSV(hue_2 + (i * 3), 255, 255); // Adjust parameters for strip 2
  }

  FastLED.delay(100); // Adjust delay for the speed of the effect

  // Move the gradient effect along the strips by shifting the hue
  hue_1++; // Increment hue for strip 1
  hue_2++; // Increment hue for strip 2
}

void waterrainbowEffect() {
  static uint8_t offset = 0; // Offset for moving waves
  static uint8_t hue = 0; // Hue value for color (0-255)

  // Create a water-like effect using sin function for wave pattern
  for (int i = 0; i < NUM_LEDS; i++) {
    uint8_t wave = sin8(i * 10 + offset); // Adjust speed with multiplier (10)
    leds_1[i] = CHSV(hue + i * 2, 255, wave);  // Adjust parameters for strip 1
    leds_2[i] = CHSV(hue + i * 2, 255, wave);  // Adjust parameters for strip 2
  }

  fadeToBlackBy(leds_1, NUM_LEDS, 64); // Smoothly fade the LEDs for a water-like effect
  fadeToBlackBy(leds_2, NUM_LEDS, 64); // Smoothly fade the LEDs for a water-like effect

  FastLED.delay(20); // Adjust delay for speed of the effect

  offset++; // Increment the offset to move the waves
}

