const int relayPin = 13;                      // Relay/PowerSwitchTail pin
const int runTimeMs = 300000;                 // Total Run time (300000ms = 5m)
const int waitTimeMs = 86400000 - runTimeMs;  // Total Wait time (86400000ms = 1d)

void setup() {
  pinMode(relayPin, OUTPUT);
}

void loop() {
  // runs relay for set amount of time once a day
  digitalWrite(relayPin, HIGH);  // Turn on the relay
  delay(runTimeMs);
  digitalWrite(relayPin, LOW);   // Turn off the relay
  delay(waitTimeMs);
}
