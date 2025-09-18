#include <ArduinoIoTCloud.h>
#include "thingProperties.h"

const int sensor1Pin = A0;
const int sensor2Pin = A1;
const int pumpRelayPin = 4;

bool pumpActive = false;
int attempts = 0;
unsigned long pumpStartTime = 0;
unsigned long lastAttemptTime = 0;
unsigned long lastFullAttemptTime = 0;

void setup() {
  Serial.begin(9600);
  delay(1500);

  pinMode(pumpRelayPin, OUTPUT);
  digitalWrite(pumpRelayPin, HIGH); // OFF

  initProperties();
  ArduinoCloud.begin(ArduinoIoTPreferredConnection);

  setDebugMessageLevel(2);
  ArduinoCloud.printDebugInfo();
}

void loop() {
  ArduinoCloud.update();

  // 💡 Master switch control
  if (!button) {
    if (pumpActive) {
      digitalWrite(pumpRelayPin, HIGH);  // turn off pump
      pumpState = false;
      pumpActive = false;
      Serial.println("System paused. Pump OFF.");
    }
    attempts = 0;
    return;
  }

  // --- Read and map sensor values
  int raw1 = analogRead(sensor1Pin);
  int raw2 = analogRead(sensor2Pin);
  humiditySensor1 = constrain(map(raw1, 600, 350, 0, 100), 0, 100);
  humiditySensor2 = constrain(map(raw2, 600, 350, 0, 100), 0, 100);

  Serial.print("Humidity1: ");
  Serial.print(humiditySensor1);
  Serial.print(" | Humidity2: ");
  Serial.println(humiditySensor2);

  unsigned long currentMillis = millis();

  // --- Auto watering logic
  if ((humiditySensor1 < 30 || humiditySensor2 < 30) && !pumpActive) {
    if (attempts < 3 && currentMillis - lastAttemptTime > 10000) {
      pumpState = true;
      digitalWrite(pumpRelayPin, LOW); // ON
      pumpActive = true;
      pumpStartTime = currentMillis;
      activationCounter++; // Count this attempt
      Serial.println("Auto Pump ON (one or both sensors < 30)");
    } else if (attempts >= 3 && currentMillis - lastFullAttemptTime >= 3600000) {
      // ⏱ One hour has passed since last full try
      Serial.println("Resetting attempts after 1 hour wait");
      attempts = 0;
    }
  }

  if (pumpActive) {
    if (humiditySensor1 >= 70 && humiditySensor2 >= 70) {
      pumpState = false;
      digitalWrite(pumpRelayPin, HIGH); // OFF
      pumpActive = false;
      attempts = 0;
      Serial.println("Humidity OK (both sensors ≥ 70), Pump OFF");
    } else if (currentMillis - pumpStartTime >= 5000) {  // ⏱ 5 sec timeout
      pumpState = false;
      digitalWrite(pumpRelayPin, HIGH); // OFF
      pumpActive = false;
      attempts++;
      lastAttemptTime = currentMillis;
      if (attempts >= 3) {
        lastFullAttemptTime = currentMillis;
        Serial.println("Max attempts reached. Entering 1-hour cooldown.");
      } else {
        Serial.print("Pump 5s timeout, attempt #");
        Serial.println(attempts);
      }
    }
  }

  delay(1000);
}

// --- Triggered from dashboard switch
void onPumpStateChange() {
  if (!button) return;

  if (pumpState) {
    digitalWrite(pumpRelayPin, LOW);
    pumpActive = true;
    pumpStartTime = millis();
    activationCounter++;
    Serial.println("Manual Pump ON");
  } else {
    digitalWrite(pumpRelayPin, HIGH);
    pumpActive = false;
    Serial.println("Manual Pump OFF");
  }
}

// --- Triggered from dashboard master button
void onButtonChange() {
  if (!button) {
    digitalWrite(pumpRelayPin, HIGH);
    pumpActive = false;
    pumpState = false;
    attempts = 0;
    activationCounter = 0;  // 🔄 Reset counter on system OFF
    Serial.println("System paused by user");
  } else {
    Serial.println("System resumed by user");
  }
}