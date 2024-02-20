#include <FastLED.h>

#define LED_PIN     0
#define NUM_LEDS    7

CRGB leds[NUM_LEDS];

void setup() {
  // Initialize serial communication
  Serial.begin(9600);

  // Initialize FastLED library
  FastLED.addLeds<WS2812B, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.clear();
  FastLED.show();
}

void loop() {
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    if (command.equals("red")) {
      setColor(CRGB::Red);
    } else if (command.equals("yellow")) {
      setColor(CRGB::Orange);
    } else if (command.equals("green")) {
      setColor(CRGB::Green);
    } else if (command.equals("off")) {
      FastLED.clear();
      FastLED.show();
    } else if (command.equals("off")) {
      FastLED.clear();
      FastLED.show();
    }
  }
}



void setColor(CRGB color) {
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = color;
  }
  FastLED.show();
}
