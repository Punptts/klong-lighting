#include <FastLED.h>

#define LED_PIN_1 12 // Define the LED data pin
#define LED_PIN_2 13 // Define the LED data pin
#define NUM_LEDS 1200 // Total number of LEDs in strip
#define BRIGHTNESS 100 // LED strip brightness (0-255)

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop() {
  shootingStarEffect(0xFFCC00, 50, 10, 5); // Orange shooting star effect with 50ms delay per step, 10 steps, and 5ms fade delay
}

void shootingStarEffect(uint32_t color, uint16_t delayTime, uint8_t steps, uint8_t fadeDelay) {
  for (int j = 0; j < steps; j++) {
    for (int i = NUM_LEDS - 1; i >= 0; i--) {
      leds_1[i] = color;
      leds_2[i] = color;
      FastLED.show();
      delay(fadeDelay);
      leds_1[i] = CRGB::Black; // Turn off LED at position i on strip 1
      leds_2[i] = CRGB::Black; // Turn off LED at position i on strip 2
      delay(delayTime);
    }
  }
}
