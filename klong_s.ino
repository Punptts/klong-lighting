#include <FastLED.h>

#define LED_PIN_1 12    // Define the LED data pin
#define LED_PIN_2 13    // Define the LED data pin
#define NUM_LEDS 1200   // Total number of LEDs in strip
#define PIR_PIN_1 2     // Define the PIR data pin
#define PIR_PIN_2 3     // Define the PIR data pin
#define BRIGHTNESS 100  // LED strip brightness (0-255)
#define FADE_AMOUNT 400 // Amount of fading for the raindrop effect
#define BLUR_AMOUNT 50  // Amount of blurring for the raindrop effect

CRGB leds_1[NUM_LEDS];
CRGB leds_2[NUM_LEDS];

void setup()
{
  FastLED.addLeds<WS2812B, LED_PIN_1, GRB>(leds_1, NUM_LEDS);
  FastLED.addLeds<WS2812B, LED_PIN_2, GRB>(leds_2, NUM_LEDS);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.show();

  // Initialize all LEDs raindropEffect
  raindropEffect(leds_1, CRGB::Aqua);
  raindropEffect(leds_2, CRGB::Aqua);

  pinMode(PIR_PIN_1, INPUT); // Set PIR sensor 1 as input
  pinMode(PIR_PIN_2, INPUT); // Set PIR sensor 2 as input
}

void loop()
{
  int pirState_1 = digitalRead(PIR_PIN_1);
  int pirState_2 = digitalRead(PIR_PIN_2);

  if (pirState_1 == HIGH || pirState_2 == HIGH)
  {
    for (int i = 0; i < 4; i++)
    { // Execute rainbow effect with blinking 3 times
      rainbowEffectWithBlink();
    }

    delay(2000);

    turnOffLEDs();
    FastLED.show(); // Show the LEDs
  }
  else
  {
    raindropEffect(leds_1, CRGB::Aqua);
    raindropEffect(leds_2, CRGB::Aqua);
    FastLED.show(); // Show the LEDs
    delay(50);      // Add a delay as needed for the effect
  }
}

// FUNCTION // ----------------------------------------------------------------------------------------------------------------------------------------------------------------- //

// turnoffleds //
void turnOffLEDs()
{
  fill_solid(leds_1, NUM_LEDS, CRGB::Black); // Turn off LEDs in strip 1
  fill_solid(leds_2, NUM_LEDS, CRGB::Black); // Turn off LEDs in strip 2
  FastLED.show();
  delay(2); // Set a delay of 10 milliseconds
}

// NO MOTION DETECTED //

void raindropEffect(CRGB leds[], CRGB color)
{
  fadeToBlackBy(leds, NUM_LEDS, FADE_AMOUNT); // Smoothly fade all LEDs for a trail effect

  int numDrops = 100 + random(300); // Vary the number of raindrops each iteration for a heavier effect
  // int numDrops = 60 + random(300); // Vary the number of raindrops each iteration for a heavier effect

  for (int i = 0; i < numDrops; i++)
  {
    int dropPos = random(NUM_LEDS);
    // int dropPos = (dropPos + 1) % NUM_LEDS;
    leds[dropPos] += color; // Add the water-like color to the raindrops
  }

  blur1d(leds, NUM_LEDS, BLUR_AMOUNT); // Blur the LEDs to create a smoother effect
  delay(1000);
  FastLED.show();
}

// MOTION DETECTED //

void rainbowEffect()
{
  static uint8_t hue = 0; // Hue value for color (0-255)

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds_1[i] = CHSV(hue + i * 2, 255, 192); // Adjust parameters to suit the desired effect
    leds_2[i] = CHSV(hue + i * 2, 255, 192); // Adjust parameters to suit the desired effect
  }

  FastLED.show();
  hue++; // Increment the hue value for color variation
}

void fadeToBlack(CRGB leds[], int numLeds, uint8_t fadeValue)
{
  for (int i = 0; i < numLeds; i++)
  {
    leds[i].fadeToBlackBy(fadeValue);
  }
}

void blurEffect(CRGB leds[], int numLeds, uint8_t blurAmount)
{
  uint8_t blurSamples = 10; // Number of times to apply the blur effect
  for (int i = 0; i < blurSamples; i++)
  {
    blur1d(leds, numLeds, blurAmount);
  }
}

void rainbowEffectWithBlink()
{
  static uint8_t hue = 0; // Hue value for color (0-255)

  for (int i = 0; i < NUM_LEDS; i++)
  {
    leds_1[i] = CHSV(hue + i * 2, 255, 192); // Adjust parameters to suit the desired effect
    leds_2[i] = CHSV(hue + i * 2, 255, 192); // Adjust parameters to suit the desired effect
  }

  FastLED.show();
  delay(50); // Display the rainbow effect for 500 milliseconds

  turnOffLEDsFade(); // Turn off the LEDs for a shorter duration
  turnOnLEDsFade();  // Turn on the LEDs for a shorter duration

  hue++; // Increment the hue value for color variation
}

// Function to turn off LEDs for 150 milliseconds
void turnOffLEDsFade()
{
  // fadeToBlack(leds_1, NUM_LEDS, 2); // Fade out LEDs in strip 1
  // fadeToBlack(leds_2, NUM_LEDS, 2); // Fade out LEDs in strip 2
  // FastLED.show();
  // delay(2); // Short delay before turning off

  // blurEffect(leds_1, NUM_LEDS, 5); // Apply blur effect to strip 1
  // blurEffect(leds_2, NUM_LEDS, 5); // Apply blur effect to strip 2
  // FastLED.show();
  // delay(2); // Short delay before turning on

  fill_solid(leds_1, NUM_LEDS, CRGB::Black); // Turn off LEDs in strip 1
  fill_solid(leds_2, NUM_LEDS, CRGB::Black); // Turn off LEDs in strip 2
  FastLED.show();
  delay(2); // Short delay before next rainbow effect
}

// Function to turn on LEDs for 150 milliseconds
void turnOnLEDsFade()
{

  fadeToBlack(leds_1, NUM_LEDS, 5); // Fade out LEDs in strip 1
  fadeToBlack(leds_2, NUM_LEDS, 5); // Fade out LEDs in strip 2
  FastLED.show();
  delay(2); // Short delay before turning off

  blurEffect(leds_1, NUM_LEDS, 5); // Apply blur effect to strip 1
  blurEffect(leds_2, NUM_LEDS, 5); // Apply blur effect to strip 2
  FastLED.show();
  delay(2); // Short delay before turning on

  rainbowEffect(); // Resume the rainbow effect
  FastLED.show();
  delay(2);
}
