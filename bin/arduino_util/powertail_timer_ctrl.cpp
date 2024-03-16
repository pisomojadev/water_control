// This code will turn on the relay for 16 hours and then turn it off for 8 hours repeatedly. 
// Note: Adjust the relayPin variable to match the pin you've connected your relay to.

const int relayPin = 2; // Pin connected to the relay

unsigned long previousMillis = 0; // Variable to store the last time the relay was toggled
const long onInterval = 16 * 60 * 60 * 1000; // 16 hours in milliseconds
const long offInterval = 8 * 60 * 60 * 1000; // 8 hours in milliseconds

boolean relayState = false; // Initial state of the relay

void setup() {
  pinMode(relayPin, OUTPUT); // Set the relay pin as an output
  digitalWrite(relayPin, LOW); // Initially turn off the relay
}

void loop() {
  unsigned long currentMillis = millis(); // Get the current time

  // Check if it's time to turn the relay on
  if (!relayState && currentMillis - previousMillis >= offInterval) {
    relayState = true; // Set relay state to on
    digitalWrite(relayPin, HIGH); // Turn on the relay
    previousMillis = currentMillis; // Save the last time the relay was toggled
  }
  // Check if it's time to turn the relay off
  else if (relayState && currentMillis - previousMillis >= onInterval) {
    relayState = false; // Set relay state to off
    digitalWrite(relayPin, LOW); // Turn off the relay
    previousMillis = currentMillis; // Save the last time the relay was toggled
  }
}
