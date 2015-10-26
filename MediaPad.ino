/* @file MediaPad.ino
|| @version 1.0
|| @author Eric Nelson
|| @contact nelseric.alt@gmail.com
||
|| @description
|| | Multi key Keypad that corresponds to media key presses, and sends multiple keys at once if pressed at once
|| #
*/

#include <Keypad.h>

// #define KEY_MEDIA_VOLUME_INC    0x01
// #define KEY_MEDIA_VOLUME_DEC    0x02
// #define KEY_MEDIA_MUTE          0x04
// #define KEY_MEDIA_PLAY_PAUSE    0x08
// #define KEY_MEDIA_NEXT_TRACK    0x10
// #define KEY_MEDIA_PREV_TRACK    0x20
// #define KEY_MEDIA_STOP          0x40
// #define KEY_MEDIA_EJECT         0x80


const byte ROWS = 3; //four rows
const byte COLS = 2; //three columns
char keys[ROWS][COLS] = {
  {KEY_MEDIA_PREV_TRACK, KEY_MEDIA_VOLUME_INC},
  {KEY_MEDIA_NEXT_TRACK, KEY_MEDIA_VOLUME_DEC},
  {KEY_MEDIA_PLAY_PAUSE, KEY_MEDIA_MUTE}
};
byte rowPins[ROWS] = {PIN_D0, PIN_D1, PIN_D2}; //connect to the row pinouts of the keypad
byte colPins[COLS] = {PIN_B0, PIN_B1}; //connect to the column pinouts of the keypad

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );



void setup() {
  Serial.begin(9600);
  kpd.setDebounceTime(1);
  Keyboard.begin();
  Serial.println(KEY_MEDIA_PREV_TRACK);
  Serial.println(KEY_MEDIA_PLAY_PAUSE);
  Serial.println(KEY_MEDIA_NEXT_TRACK);
  Serial.println(KEY_MEDIA_MUTE);
  Serial.println(KEY_MEDIA_VOLUME_DEC);
  Serial.println(KEY_MEDIA_VOLUME_INC);
}

unsigned long loopCount = 0;
unsigned long startTime = millis();
String msg = "";

void loop() {

  loopCount++;
  if ( (millis()-startTime)>1000 ) {
      startTime = millis();
      loopCount = 0;
  }

  int media = 0;

  // Fills kpd.key[ ] array with up-to 10 active keys.
  // Returns true if there are ANY active keys.
  if (kpd.getKeys())
  {
    for (int i=0; i<LIST_MAX; i++)   // Scan the whole key list.
    {
      if (kpd.key[i].kstate == PRESSED || kpd.key[i].kstate == HOLD){
        media |= kpd.key[i].kchar;
      }
    }
    Serial.println(media);
    Keyboard.set_media(media);
    Keyboard.send_now();
  }
}  // End loop
