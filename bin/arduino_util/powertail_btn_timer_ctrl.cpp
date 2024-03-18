//  This code does the following:
//  1. Monitors the state of a button connected to buttonPin.
//  2. Toggles the state of a relay connected to relayPin when the button is pressed.
//  3. Keeps track of the last time the relay was turned on/off using previousMillis.
//  4. Turns on the relay for 30 minutes every 24 hours once the button is pressed.

const int buttonPin = 2;   // the pin number of the button
const int relayPin = 3;    // the pin number of the relay

bool buttonState = false;  // current state of the button
bool lastButtonState = false;  // previous state of the button
bool relayState = false;   // current state of the relay
unsigned long lastDebounceTime = 0;  // last time the button was pressed
unsigned long debounceDelay = 50;    // debounce time; increase if the output flickers

unsigned long previousMillis = 0;  // stores the last time the relay was toggled
const long interval = 24 * 60 * 60 * 1000;  // interval for turning on the relay (24 hours)

void setup() {
  pinMode(buttonPin, INPUT_PULLUP);  // set button pin as input with internal pull-up resistor
  pinMode(relayPin, OUTPUT);         // set relay pin as output
}

void loop() {
  unsigned long currentMillis = millis();  // current time

  // Read the state of the button
  bool reading = digitalRead(buttonPin);

  // Check if the button state has changed
  if (reading != lastButtonState) {
    lastDebounceTime = currentMillis;  // reset debounce time
  }

  // Check if the button state has remained stable for the debounce delay
  if ((currentMillis - lastDebounceTime) > debounceDelay) {
    // If the button state has changed, update the button state
    if (reading != buttonState) {
      buttonState = reading;

      // If the button is pressed
      if (buttonState == LOW) {
        // Toggle the relay state
        relayState = !relayState;
        digitalWrite(relayPin, relayState ? HIGH : LOW);
      }
    }
  }

  // If the relay is turned on, check if it's time to turn it off
  if (relayState) {
    if (currentMillis - previousMillis >= 30 * 60 * 1000) {
      // 30 minutes have passed, turn off the relay
      digitalWrite(relayPin, LOW);
      relayState = false;
      previousMillis = currentMillis;
    }
  } else {
    // If the relay is turned off, check if it's time to turn it on
    if (currentMillis - previousMillis >= interval) {
      // 24 hours have passed, turn on the relay
      digitalWrite(relayPin, HIGH);
      relayState = true;
      previousMillis = currentMillis;
    }
  }

  // Save the current button state for comparison in the next iteration
  lastButtonState = reading;
}
