// #include <FastLED.h>

#define LED_PIN_1 12   // Define the LED data pin
#define LED_PIN_2 13   // Define the LED data pin
#define NUM_LEDS 1200  // Total number of LEDs in strip
#define BRIGHTNESS 100 // LED strip brightness (0-255)

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
}

void loop()
{
  cometEffect(0xFF0000, 600, 50); // Red comet effect with 5 pixels tail, 50ms delay per step
}

void cometEffect(uint32_t color, uint8_t tailLength, uint16_t delayTime)
{
  for (int i = 0; i < NUM_LEDS + tailLength; i++)
  {
    for (int j = 0; j < tailLength; j++)
    {
      if ((i - j >= 0) && (i - j < NUM_LEDS))
      {
        leds_1[i - j] = color % (255 / (j + 1)); // Adjust brightness for tail on strip 1
        leds_2[i - j] = color % (255 / (j + 1)); // Adjust brightness for tail on strip 2
      }
    }
    FastLED.show();
    leds_1[i] = CRGB::Black; // Clear led at position i on strip 1
    leds_2[i] = CRGB::Black; // Clear led at position i on strip 2
  }
}
