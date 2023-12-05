#include <FastLED.h>

#define LED_PIN_1 12 // Define the LED data pin
#define LED_PIN_2 13 // Define the LED data pin
#define NUM_LEDS 1200 // Total number of LEDs in strip
#define BRIGHTNESS 100 // LED strip brightness (0-255)
#define FADE_AMOUNT 400 // Amount of fading for the raindrop effect
#define BLUR_AMOUNT 50 // Amount of blurring for the raindrop effect
// #define FADE_AMOUNT   50          // Amount of fading for the raindrop effect
// #define BLUR_AMOUNT   10          // Amount of blurring for the raindrop effect

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear(); // Initialize all LEDs to off
  FastLED.show();
}

void loop() {
    heavyRaindropEffect(leds_1, CRGB::Aqua);
    heavyRaindropEffect(leds_2, CRGB::Aqua);
    delay(2000); // Adjust the delay between iterations
}

// Function //
void heavyRaindropEffect(CRGB leds[], CRGB color) {
    fadeToBlackBy(leds, NUM_LEDS, FADE_AMOUNT); // Smoothly fade all LEDs for a trail effect

    int numDrops = 100 + random(300); // Vary the number of raindrops each iteration for a heavier effect
    // int numDrops = 60 + random(300); // Vary the number of raindrops each iteration for a heavier effect

    for (int i = 0; i < numDrops; i++) {
        int dropPos = random(NUM_LEDS);
        // int dropPos = (dropPos + 1) % NUM_LEDS;
        leds[dropPos] += color; // Add the water-like color to the raindrops
    }

    blur1d(leds, NUM_LEDS, BLUR_AMOUNT); // Blur the LEDs to create a smoother effect

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
