/*
 * Project Quit VIM
 * Description: Smash the button to quit VIM
 * Author: Alan Mond
 * Date: 3 July 2021
 * License: GNU GPLv3 
 */

#include <Keyboard.h>
#include "LowPassFilter.hpp"

#define NORMAL // define DEBUG for development or NORMAL for production

constexpr int threshold = 1023 / 2; // set threshold as a constant expression, calculated at compile time.
int raw_value = 0;
int filtered_value = 0;
bool is_button_pressed = false;
bool keystroke_sent = false;
LowPassFilter lpf(1, 0.007);

void check_state_and_send_shortcut(){
  if (is_button_pressed && !keystroke_sent){
    // send escape key to access VIM command line
    Keyboard.write(KEY_ESC);
    // send quit VIM keystroke sequence
    Keyboard.write(':');
    Keyboard.write('q');
    Keyboard.write('!');
    Keyboard.releaseAll();
    // press and release enter key to execute VIM command
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