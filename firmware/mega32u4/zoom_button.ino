/*
 * Project End Zoom Meetings Button
 * Description: Smash the button to end your zoom meetings
 * Author: Alan Mond
 * Date: 21 December 2020
 * License: GNU GPLv3 
 */

#include<Keyboard.h>
#include "LowPassFilter.hpp"

int raw_value = 0;
int filtered_value = 0;
bool is_button_pressed = false;
bool keystroke_sent = false;
LowPassFilter lpf(1.0, 0.005);

void check_state_and_send_shortcut(){
  if (is_button_pressed && !keystroke_sent){
    //kill screenshare in case it was open
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.write('S');
    // send escape key to exit screenshare select window (if screenshare was off)
    Keyboard.write(KEY_ESC);
    // send leave meeting command
    Keyboard.press(KEY_LEFT_GUI);
    Keyboard.write('w');
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
  pinMode(13, OUTPUT);
  Keyboard.begin();
}

void loop() {

  raw_value = analogRead(A0);
  filtered_value = lpf.update(raw_value); 
  if ( filtered_value == 0) {
    is_button_pressed = true;
    turn_on_light();
  }
  else {
    is_button_pressed = false;
    keystroke_sent = false;
    turn_off_light();
  }
  check_state_and_send_shortcut();
}
