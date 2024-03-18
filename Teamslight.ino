#include <FastLED.h>

#define LED_PIN     0
#define LED_COUNT   7
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB

CRGB leds[LED_COUNT];

bool rainbowRunning = false;
int commandnumber;
int prevcommandnumber;
int hue;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT);
  FastLED.show(); // Initialize all LEDs to 'off'
  String lastcommand = "";
  int commandnumber = 0;
  int hue = 0;
}

void loop() {
String lastcommand = "";
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');
    command.trim();
    String lastcommand = command; 
    if (command.equalsIgnoreCase("red")) {
      commandnumber = 1;
    } else if (command.equalsIgnoreCase("yellow")) {
      commandnumber = 2;
    } else if (command.equalsIgnoreCase("green")) {
      commandnumber = 3;
    } else if (command.equalsIgnoreCase("off")) {
      commandnumber = 4;
    } else if (command.equalsIgnoreCase("rgb")) {
      commandnumber = 5;
    }
  }
  if((commandnumber != prevcommandnumber && commandnumber == 1)){
    setColor(CRGB::Red);
  }
  if(commandnumber != prevcommandnumber && commandnumber == 2){
    setrgb(255,43,0);
  }
  if(commandnumber != prevcommandnumber && commandnumber == 3){
    setColor(CRGB::Green);
  }
  if(commandnumber != prevcommandnumber && commandnumber == 4){
    setColor(CRGB::Black);
  }
  if(commandnumber == 5){
    hue++;
    if(hue > 255){hue = 0;}
    setchsv(hue,255,255);
    delay(50);
  }
  prevcommandnumber = commandnumber;
  //Serial.print(commandnumber);
  //Serial.print('\n');
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
void setchsv(int hue,int sat,int val) {
  for (int i = 0; i < LED_COUNT; i++) {
      leds[i] = CHSV(hue, sat, val);
  }
  FastLED.show();
}






