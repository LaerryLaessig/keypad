#include "Arduino.h"
#include "Keyboard.h"

// Key definitions
#define BUTTON_KEY1 KEY_F13
#define BUTTON_KEY2 KEY_F14
#define BUTTON_KEY3 KEY_F15
#define BUTTON_KEY4 KEY_F16
#define BUTTON_KEY5 KEY_F17
#define BUTTON_KEY6 KEY_F18

// Mode
#define BRIGHTNESS 1
#define LIGHT_STYLE 2

// Pin definitions
#define BUTTON_PIN1 2
#define BUTTON_PIN2 3
#define BUTTON_PIN3 4
#define BUTTON_PIN4 5
#define BUTTON_PIN5 6
#define BUTTON_PIN6 7

#define LED_BACKLIGHT 9

#define BUTTON_LIGHT_MODE 12
#define BUTTON_BRIGHTNESS 13

char number_steps_of_brightness = 8;
char brightness_step = 255 / number_steps_of_brightness;
char brightness = 125;
boolean permanent_light = 0;

void failsafe(){
  for(;;){} 
}

void light_background(boolean state) {
  if(!permanent_light) {
    state? analogWrite(LED_BACKLIGHT, brightness) : analogWrite(LED_BACKLIGHT, 0);
  } else {
    analogWrite(LED_BACKLIGHT, brightness);
  }
}

char change_brightness() {
    return brightness = brightness < brightness_step*number_steps_of_brightness ? brightness + brightness_step: 0;
}

boolean toggle_permanent_light() {
  return permanent_light = !permanent_light;
}

struct btn {
    const uint8_t pin;

    btn(uint8_t p) : pin(p) {}
    virtual ~btn() = default;

    virtual void press(boolean);

    void update(){
        press(!digitalRead(pin));
    }

};

// F-Button helper class for handling press/release and debouncing
class function_btn : public btn {
  public:
  const char key;

  function_btn(uint8_t k, uint8_t p) : btn(p), key(k){}
  virtual ~function_btn() = default;

  void press(boolean state) final {
    if(state == pressed || (millis() - lastPressed  <= debounceTime)){
      return;
    }

    lastPressed = millis();

    state ? Keyboard.press(key) : Keyboard.release(key);
    light_background(state);   
    pressed = state;
  }

  private:
  const unsigned long debounceTime = 30;
  unsigned long lastPressed = 0;
  boolean pressed = 0;
} ;

// Mode-Button helper class for handling press/release and debouncing
class mode_btn : public btn {
    public:
    const uint8_t mode;

    mode_btn(uint8_t m, uint8_t p): btn(p), mode(m) {}
    virtual ~mode_btn() = default;

  void press(boolean state) final {
    if(state == pressed || (millis() - lastPressed  <= debounceTime)){
      return;
    }

    lastPressed = millis();

    switch (mode) {
    case BRIGHTNESS:
      state ? change_brightness(): brightness; 
      break;
    
    case LIGHT_STYLE:
     state ? toggle_permanent_light(): permanent_light;
      break;

    default:
      break;
    }
    light_background(state);

    pressed = state;
  }

    private:
    const unsigned long debounceTime = 30;
    unsigned long lastPressed = 0;
    boolean pressed = 0;
};

function_btn func_btns[] = {
  {BUTTON_KEY1, BUTTON_PIN1},
  {BUTTON_KEY2, BUTTON_PIN2},
  {BUTTON_KEY3, BUTTON_PIN3},
  {BUTTON_KEY4, BUTTON_PIN4},
  {BUTTON_KEY5, BUTTON_PIN5},
  {BUTTON_KEY6, BUTTON_PIN6}
};

mode_btn mode_btns[] = {
  {BRIGHTNESS, BUTTON_BRIGHTNESS},
  {LIGHT_STYLE, BUTTON_LIGHT_MODE}
};



const uint8_t num_func_btns = sizeof(func_btns) / sizeof(function_btn);
const uint8_t num_mode_btns = sizeof(mode_btns) / sizeof(mode_btn);
const char ledPin = 17;

void setup() { 
  // fety check.Sa Ground pin #1 (RX) to cancel keyboard inputs.
  pinMode(1, INPUT_PULLUP);
  if(!digitalRead(1)){
    failsafe();
  }
  // Set LEDs Off. Active low.
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, HIGH);
  TXLED0;

  // Backlight
  pinMode(LED_BACKLIGHT, OUTPUT);

  for(int i = 0; i < num_func_btns; i++){
    pinMode(func_btns[i].pin, INPUT_PULLUP);
  }
  for(int i = 0; i < num_mode_btns; i++){
    pinMode(mode_btns[i].pin, INPUT_PULLUP);
  }
}


void loop() {
  for(int i = 0; i < num_func_btns; i++){
    func_btns[i].update();
  } 
    for(int i = 0; i < num_mode_btns; i++){
    mode_btns[i].update();
  } 
}