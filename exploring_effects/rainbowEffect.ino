#include <FastLED.h>

#define LED_PIN_1     12  // Pin for LED strip 1
#define LED_PIN_2     13  // Pin for LED strip 2
#define NUM_LEDS      1200 // Number of LEDs in each strip

CRGB leds_1[NUM_LEDS];  // Array for LED strip 1
CRGB leds_2[NUM_LEDS];  // Array for LED strip 2

void setup() {
  FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(leds_1, NUM_LEDS); // Initialize LED strip 1
  FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(leds_2, NUM_LEDS); // Initialize LED strip 2

}

void loop() {
waterMoodEffect();
}

void waterMoodEffect() {
  // Code for water-like mood effect (e.g., flowing colors, gentle transitions)
  // You can create custom functions to manipulate the LEDs and create the desired water-like effect
  // Experiment with color palettes, brightness, fading, and movement across the LED strips
  // Here is an example of a simple flowing effect:
  
  static uint8_t hue = 0; // Hue value for color (0-255)
  
  for (int i = 0; i < NUM_LEDS; i++) {
    leds_1[i] = CHSV(hue + i * 2, 255, 192); // Adjust parameters to suit the desired effect
    leds_2[i] = CHSV(hue + i * 2, 255, 192); // Adjust parameters to suit the desired effect
  }

  FastLED.show();
  // delay(500); // Display the water mood effect for 500 milliseconds

  // turnOffLEDs(); // Turn off the LEDs for the same duration

  // hue++; // Increment the hue value for color variation
}

void turnOffLEDs() {
  fill_solid(leds_1, NUM_LEDS, CRGB::Black);
  fill_solid(leds_2, NUM_LEDS, CRGB::Black);
  FastLED.show();
  delay(300); // Delay for the same duration as the effect to create the blink
}