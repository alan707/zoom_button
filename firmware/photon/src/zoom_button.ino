/*
 * Project End Zoom Meetings Button
 * Description: Smash the button to end your zoom meetings
 * Author: Alan Mond
 * Date: 21 December 2020
 * License: GNU GPLv3 
 */

int raw_value = 0;
bool is_button_pressed = false;
bool keystroke_sent = false;
SerialLogHandler logHandler;

SYSTEM_THREAD(ENABLED);

// Initialize device as a Hardware Input Device (basically a keyboard)
STARTUP(Keyboard.begin());

void check_state_and_send_shortcut(){
  if (is_button_pressed && !keystroke_sent){
    // sending Alt + q shortcut
    Keyboard.press(KEY_LALT);
    Keyboard.press(KEY_Q);
    Keyboard.releaseAll();
    // press and release enter key to confirm we want to exit 
    Keyboard.click(KEY_ENTER);
    keystroke_sent = true;
  }
}

void loop() {
  raw_value = analogRead(A0);
  if ( raw_value > 2500 ) {
    is_button_pressed = true;
  }
  else {
    is_button_pressed = false;
    keystroke_sent = false;
  }
  check_state_and_send_shortcut();
}
