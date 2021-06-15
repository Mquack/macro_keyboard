#include <FastLED.h>
#include "Keyboard.h"

#define LED_PIN     14
#define NUM_LEDS    4

// Keys, F13 to F21
#define BTN_KEY1 KEY_F13
#define BTN_KEY2 KEY_F14
#define BTN_KEY3 KEY_F15
#define BTN_KEY4 KEY_F16
#define BTN_KEY5 KEY_F17
#define BTN_KEY6 KEY_F18
#define BTN_KEY7 KEY_F19
#define BTN_KEY8 KEY_F20
#define BTN_KEY9 KEY_F21

// Pin definitions
#define BTN_PIN1 2
#define BTN_PIN2 3
#define BTN_PIN3 4
#define BTN_PIN4 5
#define BTN_PIN5 6
#define BTN_PIN6 7
#define BTN_PIN7 8
#define BTN_PIN8 9
#define BTN_PIN9 10

CRGB leds[NUM_LEDS];

//list of colors that you switch between. last one is just off.
int ledList[][3] = {{255, 0, 0},{0, 255, 0},{0, 0, 255},{255, 0, 255},{0, 255, 255},{255, 255, 0},{145, 30, 180},{128, 0, 0},{255, 20, 147},{0, 0, 0}};

const int colorSwitchBtn = 15;
int ledCount = -1;// -1 to not skipp the first color in the list since the starting color is a rainbow pattern not included in the list
int buttonState = 0;

void failsafe(){
  for(;;){}
}

// Handle button presses and debouncing
class button {
  public:
  const uint8_t pin;
  const char key;
  const long debounceTime = 30;
  unsigned long lastPressed;
  boolean pressed = 0;

  button(uint8_t k, uint8_t p) : key(k), pin(p){}
  //If total runtime - lastpressed is less than or equal to debouncetime, return.
  void press(boolean state){
    if((millis() - lastPressed  <= debounceTime)){
      return; //disregard button press
    }

    lastPressed = millis();

    if(state){
      Keyboard.press(key);
    }else{
      Keyboard.release(key);
    }
    pressed = state;
  }

  void btnCheck(){
    press(!digitalRead(pin));
  }
};

button buttons[] = {
  {BTN_KEY1, BTN_PIN1},
  {BTN_KEY2, BTN_PIN2},
  {BTN_KEY3, BTN_PIN3},
  {BTN_KEY4, BTN_PIN4},
  {BTN_KEY5, BTN_PIN5},
  {BTN_KEY6, BTN_PIN6},
  {BTN_KEY7, BTN_PIN7},
  {BTN_KEY8, BTN_PIN8},
  {BTN_KEY9, BTN_PIN9},
};

const uint8_t NumButtons = sizeof(buttons) / sizeof(button);

void startColor(){
  leds[0] = CRGB(255, 0, 0);
  leds[1] = CRGB(0, 255, 0);
  leds[2] = CRGB(0, 0, 255);
  leds[3] = CRGB(150, 0, 255);
  FastLED.show();
}

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2812, LED_PIN, GRB>(leds, NUM_LEDS);

  for(int i = 0; i < NumButtons; i++){
    pinMode(buttons[i].pin, INPUT_PULLUP);
  }
  pinMode(colorSwitchBtn, INPUT_PULLUP);
  //initial color animation.
  leds[0] = CRGB(255, 0, 0);
  FastLED.show();
  delay(300);
  leds[1] = CRGB(0, 255, 0);
  FastLED.show();
  delay(300);
  leds[2] = CRGB(0, 0, 255);
  FastLED.show();
  delay(300);
  leds[3] = CRGB(150, 0, 255);
  FastLED.show();
  delay(300);
}

void loop() {
  for(int i = 0; i < NumButtons; i++){
    buttons[i].btnCheck();
  }

  buttonState = digitalRead(colorSwitchBtn);
  if (buttonState == LOW){
    delay(300);
    if (ledCount >= 10){
      ledCount = 0;
    }else{
      ledCount++;
    }
    if(ledCount == 10){
      startColor();
    }else{
      for(int i = 0; i<=3; i++){
      leds[i] = CRGB(ledList[ledCount][0], ledList[ledCount][1], ledList[ledCount][2]);
      FastLED.show();
      }
    }
  }
}
