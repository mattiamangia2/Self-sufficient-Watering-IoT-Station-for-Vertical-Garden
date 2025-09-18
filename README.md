:Author: mattiamangia2
:Email: mattiamangia1995@gmail.com
:Date: 30/05/2025
:Revision: version#3
:License: Public Domain

= Project: {Self-sufficient Watering IoT Station for Vertical Garden}

Project Description:

== Step 1: Installation

What will you need to execute this project succesfully:
- Arduino Giga R1 wifi;
- 4-Relay Module HW-316;
- 2 (or 4 or more) Capacitive Sensors for Soil Moisture;
- 2 (or 4 or more) Mini immersive pumps 3V.


== Step 2: Assemble the circuit

You can Cable every element as per the following Diagram:


== Step 3: Load the code

Upload the code contained in this sketch on to your board

Consider the following elements:
- humiditySensor1 = constrain(map(raw1, 600, 350, 0, 100), 0, 100) 
Helps to map the humidity measured in percentage, based on the sensors I purchased. I encourage to build an easy sketch ad the beginning, to monitor the raw readings of the impedence, so that it's possible to understand what is the value on a dry soil, and what is the value on a saturated wet soil. After that, consider those 2 extremes as lower and upper constrains;

- if ((humiditySensor1 < 30 || humiditySensor2 < 30) && !pumpActive) {
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
This entire part is customized on a behavior I intentionally set up. The humidity level, the attempts and the wait time till last attempts, can be calibrated based on the plants, the ground and the dimention of the vases;




....

=== License
This project is released under a {Public Domain} License.

=== Contributing
To contribute to this project please contact: 
mattiamangiajobs@outlook.it

=== BOM
Total cost of the project: circa 90 euros