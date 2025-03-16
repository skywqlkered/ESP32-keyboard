#include <Arduino.h>
#include <BleKeyboard.h>
#include <Keypad.h>

// put function declarations here:#include <Keypad.h>

BleKeyboard bleKeyboard;


const int ROW_NUM = 4;     //four rows
const int COLUMN_NUM = 4;  //four columns
char keys[ROW_NUM][COLUMN_NUM] = {
  { '1', '2', '3', 'A' },
  { '4', '5', '6', 'B' },
  { '7', '8', '9', 'C' },
  { '*', '0', '#', 'D' }
};
byte colPins[ROW_NUM] = { 26, 25, 33, 32 };
// byte colPins[ROW_NUM] = {32, 33, 25, 26}; // Safer column pins
byte rowPins[COLUMN_NUM] = { 27, 14, 12, 13 };  // Safer row pins

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROW_NUM, COLUMN_NUM);

void setup() {
  Serial.begin(115200);
  Serial.println("Starting BLE work!");
  bleKeyboard.begin();

  // Enable internal pull-up resistors on column pins
  for (int i = 0; i < COLUMN_NUM; i++) {
    pinMode(colPins[i], INPUT_PULLUP);
  }
}

void loop() {
  char key = keypad.getKey();
  if (key)  //press a key on the 4x4 matrix keypad
  {
    Serial.println(key);
    delay(10);

    if (bleKeyboard.isConnected()) {
      Serial.println("Sending 'Hello world'...");
      bleKeyboard.print("Hello world");

      // Serial.println("Sending Play/Pause media key...");
      // bleKeyboard.write(KEY_MEDIA_PLAY_PAUSE);


      //
      // Below is an example of pressing multiple keyboard modifiers
      // which by default is commented out.
      //
      /* Serial.println("Sending Ctrl+Alt+Delete...");
    bleKeyboard.press(KEY_LEFT_CTRL);
    bleKeyboard.press(KEY_LEFT_ALT);
    bleKeyboard.press(KEY_DELETE);
    delay(100);
    bleKeyboard.releaseAll();
    */
    }
    
  }
}