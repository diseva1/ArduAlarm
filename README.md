# ArduAlarm

> ⚠️**Disclaimer!** This was made as a class assignment thus its operation in the real life has not been tested.

This project was made during the lockdown we had in Spain in 2020 as my final assignment in TIC in my last high school year.

## Objectives
The main goal of this project was to create an alarm which should be able to notify us via SMS if any intrusion was detected as well as giving us the chance of arm/disarm the device also by sending an SMS.


## Components

 - Arduino Uno R3
 - Joystick
 - GSM Module SIM800L
 - LIPO Battery Charger
 - I2C LCD 16x2
 - Magnetic Door Sensor
 - 2 x LEDs
 - RFID RC522 Module
 - Power Switch
 - Buzzer
 - 2 x 220Ω Resistor
 - 10kΩ Resistor
 - 20kΩ Resistor
 - LIPO Battery
 - Lots of cables

## Wiring
![Connection_diagram](https://raw.githubusercontent.com/diseva1/ArduAlarm/master/connections_diagram.jpg)

## Video
[![Watch the video](https://img.youtube.com/vi/J2ibthyDfs0/maxresdefault.jpg)](https://www.youtube.com/watch?v=J2ibthyDfs0)

## Project Description
The idea of this project was to build an alarm that could alert the owner via SMS, so it does not have to depend on a Wi-Fi network to work, when an intrusion is detected. 
In the final version of the project the user is able to access a main menu where there are three sections, STATUS, SETTINGS and SCREENSAVER. When the STATUS section is accessed the LCD displays the current state of the alarm. The SETTINGS section has a submenu with the options SILENT MODE and COUNTDOWN, in the first one we can turn on or off the SILENT MODE which is an option that mutes all the sounds made by the alarm; in the COUNTDOWN menu the user is able to change the time of the countdown that the alarm starts when the sensors are triggered before sending the alert. And finally, the SCREENSAVER, when the user enters in this section the alarm enters in its “main screen” where we can see the current status in the LCD and arm or disarm it using an authorized card.
When the alarm is in the screensaver mode is when it is listening to the incoming SMS and checking if the sensor has been opened or not. Also, as I have said earlier, the user can arm or disarm it using in authorized card, otherwise the display will show that the card is not valid, the red led will blink and the buzzer will sound.
There are four different possibilities when the alarm is armed and detects that the sensor has been opened and the countdown is started.
1. After the countdown the sensors are closed again so nothing happens, and the alarm returns to be armed.
2. After the countdown the sensors are still opened but the user has used an authorized card, in this case the alarm state will change to disarm.
3. After the countdown the sensors are still open, and any card has been passed through the lector. In this case the alarm will show in the display a message alerting of the intrusion and emit a light and sonorous alert. Moreover, will send an SMS alerting of the intrusion.
4. After the countdown the user uses a not authorized card and depending on how the sensors are, the alarm does what I have explained above.
As this is a GSM alarm that works with a phone number there are four different commands that we can send.
• Arm: Change the status of the alarm to armed and returns a message with the status to check if has changed correctly.
• Disarm: Change the status of the alarm to disarmed and returns a message with the status to check if has changed correctly.
• Status: Sends a message to the user with the status of the alarm.
• Battery: Sends a message to the user with the remaining charge of the battery.

The alarm can be moved anywhere once that the code has been uploaded in the Arduino because in one side there is a dc power jack for the board and a micro usb charging port for the batteries connected to the SIM800L module.

## Information Sources
Most of the information I have had to look for was related with the SIM800L GSM module that I have used, the wiring and the code to send and receive SMS, I have taken them from the website Last Minute Engineers, also I have used this page to look for more general information about the module. 
For the part of sending the battery of the SIM800L I have used the function sendCommand that was in this github page, and then I have modified with the library of this video.
Finally, in order to save time and have an accurate menu I decided to use the Arduino LCDMenuLib2 which is posted on github.
