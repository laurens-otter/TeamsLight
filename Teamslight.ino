#include <FastLED.h>

#define LED_PIN     0
#define LED_COUNT   7
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[LED_COUNT];

bool rainbowRunning = false;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);
  FastLED.show(); // Initialize all LEDs to 'off'
  String lastcommand = "";
}

void loop() {
String lastcommand = "";
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    String lastcommand = command; 
    if (command.equalsIgnoreCase("red")) {
      setColor(CRGB::Red); // Red
    } else if (command.equalsIgnoreCase("yellow")) {
      setrgb(255,43,0); // orange
    } else if (command.equalsIgnoreCase("green")) {
      setColor(CRGB::Green); // Green
    } else if (command.equalsIgnoreCase("off")) {
      setColor(CRGB::Black); // Turn off
    } else if (command.equalsIgnoreCase("rgb")) {
    }
  }
while(lastcommand == "rgb") {
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CHSV((j + (i * 10)) % 256, 255, 255);
    }
    FastLED.show();
    delay(50);
  }
}    
Serial.print(lastcommand);   
}


void setColor(CRGB color) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i] = color;
  }
  FastLED.show();
}
void setrgb(int red,int green,int blue) {
  for (int i = 0; i < LED_COUNT; i++) {
    leds[i].setRGB(red,green,blue);
  }
  FastLED.show();
}



