/*
 * Project End Zoom Meetings Button
 * Description: Smash the button to end your zoom meetings
 * Author: Alan Mond
 * Date: 21 December 2020
 * License: GNU GPLv3 
 */

#include<Keyboard.h>
#include "LowPassFilter.hpp"

#define OSX // LINUX, OSX or WINDOWS
#define NORMAL // define DEBUG for development or NORMAL for production

constexpr int threshold = 1023 / 2; // set threshold as a constant expression, calculated at compile time.
int raw_value = 0;
int filtered_value = 0;
bool is_button_pressed = false;
bool keystroke_sent = false;
LowPassFilter lpf(1, 0.007);

void check_state_and_send_shortcut(){
  if (is_button_pressed && !keystroke_sent){
    //kill screenshare in case it was open
    #ifdef OSX
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.write('S');
    #endif
    #ifdef WINDOWS
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('s');
    #endif
    Keyboard.releaseAll();
    // send escape key to exit screenshare select window (if screenshare was off)
    Keyboard.write(KEY_ESC);
    // send leave meeting command
    #ifdef OSX
      Keyboard.press(KEY_LEFT_GUI);
      Keyboard.write('w');
    #endif
    #ifdef WINDOWS
      Keyboard.press(KEY_LEFT_ALT);
      Keyboard.write('q');
    #endif
    Keyboard.releaseAll();
    // press and release enter key to confirm we want to exit 
    Keyboard.write(KEY_RETURN);
    keystroke_sent = true;
  }
  Keyboard.end();
}
 
void turn_on_light(){
  digitalWrite(13, HIGH);
}

void turn_off_light(){
  digitalWrite(13, LOW);
}

void setup() { 
  #ifdef DEBUG
    Serial.begin(115200);
  #endif
  pinMode(13, OUTPUT);
  pinMode(A0, INPUT_PULLUP);
  Keyboard.begin();
}

void loop() {
  raw_value = analogRead(A0);
  filtered_value = lpf.update(raw_value);
  #ifdef DEBUG
    Serial.print("raw value is: ");
    Serial.print(raw_value);
    Serial.print(" | filtered value is: ");
    Serial.print(filtered_value);
    Serial.println();
  #endif
  if ( filtered_value < threshold) {
    is_button_pressed = true;
    turn_on_light();
  }
  else {
    is_button_pressed = false;
    keystroke_sent = false;
    turn_off_light();
  }
  #ifdef NORMAL
    check_state_and_send_shortcut();
  #endif
}
