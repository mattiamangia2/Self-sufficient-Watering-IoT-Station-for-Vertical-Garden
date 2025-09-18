+ Author: mattiamangia2
+ Email: mattiamangia1995@gmail.com
+ Date: 30/05/2025
+ Revision: version#3
+ License: Public Domain

# Project: {Self-sufficient Watering IoT Station for Vertical Garden}

## Project Description:
Having Vertical Gardens on balcony is cool but, how about taking a long and well deserved rest, taking a summer break away from home and then, what happens when you're back from paradise? You find hell in your garder: All the beautiful plants you've been caring of for the entire year, turns into a bunch of dry and dead tangles.
You decide that you need a solution, and since you're an engineer, you want to think big:

You want a self-sufficient solution, able to detect when the plants needs water, and provide it automatically. You also want to make sure you don't overflood the plant with unnecessary water, check for the performance of the entire system, and make sure to have an emergency exit button in case things turns problematic. You also want to keep yoursel updated from everywhere in the world, making sure you can monitor live the situation of the Vertical Garden.

## Step 1: Installation

What will you need to execute this project succesfully:
- Arduino Giga R1 wifi;
- 4-Relay Module HW-316;
- 2 (or 4 or more) Capacitive Sensors for Soil Moisture;
- 2 (or 4 or more) Mini immersive pumps 3V.
- Smartphone with Arduino IoT Remote APP.


## Step 2: Assemble the circuit

You can Cable every element as per the following Diagram:
![watering system](https://github.com/user-attachments/assets/d1fd3677-31e4-49bd-b19c-79e7c3bd7ca9)


## Step 3: Set up Cloud Variables
Before proceeding, you need to create cloud variables to make sure being able to monitor those values live, and build a nice Dashboard interface.
- activationCounter: int activationCounter | Integer number | Read Only | On Change
- button: bool button | Boolean | Read & Write | On Change
- humiditySensor1: int humiditySensor1 | Integer number | Read Only | On Change
- humiditySensor2: int humiditySensor2 | Integer number | Read Only | On Change
- ..you can add as many sensors as you need
- pumpState: bool pumpState | Boolean | Read & Write | On Change
- ..you can add as many pumps as you need


## Step 4: Load the code

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


## Step 5: Build a nice interface for the dashboard

Now that you have all set up, you can play with dashboard construction. Try to make elements fit the screen in a nice way, and make sure to play with some parts to make sure to have the right level of interaction:
![WhatsApp Image 2025-09-18 at 16 17 02](https://github.com/user-attachments/assets/4996012b-a369-4555-9eab-77dde445926d)


https://github.com/user-attachments/assets/082f8aba-0ab7-4331-8e21-dc6ac1badea5


![WhatsApp Image 2025-09-18 at 16 20 00](https://github.com/user-attachments/assets/f07de12b-5065-44f2-a69b-0734f2650941)
![WhatsApp Image 2025-09-18 at 16 19 59 (1)](https://github.com/user-attachments/assets/4a0e3468-6598-47ad-91cb-882ef29c64d6)
![WhatsApp Image 2025-09-18 at 16 19 59](https://github.com/user-attachments/assets/87339c35-96e7-4e0c-951a-e155908485b7)
![WhatsApp Image 2025-09-18 at 16 20 00 (1)](https://github.com/user-attachments/assets/c2ac098d-1278-465c-ba5c-ae4739612d34)




....

=== License
This project is released under a {Public Domain} License.

=== Contributing
To contribute to this project please contact: 
mattiamangiajobs@outlook.it

=== BOM
Total cost of the project: circa 90 euros
