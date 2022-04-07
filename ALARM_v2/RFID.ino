#include <MFRC522.h>

#include <SPI.h>

#define SAD 10
#define RST 5
MFRC522 nfc(SAD, RST);


#define greenLed    7
#define redLed  6

//When this function is called the RFID is ready to be used
void setup_RFID() {
 pinMode(greenLed  , OUTPUT);   
 pinMode(redLed, OUTPUT);   
 SPI.begin();
 Serial.begin(115200);
 Serial.println("Searching RC522");
 nfc.begin();
 byte version = nfc.getFirmwareVersion();
 if (! version) {//Enters if the module is not found
   Serial.print("RC522 not found");
   while(1); //stop
 }

 Serial.println("RC522 found");
 Serial.print("Firmware version 0x");
 Serial.print(version, HEX);
 Serial.println(".");
}

#define AUTHORIZED_COUNT 1 
byte Authorized[AUTHORIZED_COUNT][6] = {

{0xA0, 0x77, 0x32, 0x83, 0x66,} 

};
                         
void printSerial(byte *serial);
bool isSame(byte *key, byte *serial);
bool isAuthorized(byte *serial);

//This function checks if a card has been aproached to the sensor when the alarm is in the screensaver function
void check_RFID() {
 byte status;
 byte data[MAX_LEN];
 byte serial[5];
 status = nfc.requestTag(MF1_REQIDL, data);

 if (status == MI_OK) {
   status = nfc.antiCollision(data);
   memcpy(serial, data, 5);
   
   if(isAuthorized(serial)) //If the card is valid changes the alarm state
   { 
     Serial.println("Authorized");
     
     switch (alarmStatus) {
      case true:
        alarmStatus = false;
        alarm_DISARM();
        break;
      case false:
        alarmStatus = true;
        alarm_ARM();
        break;
     }
   }
   else //When the card is not authorized do the following
   { 
     printSerial(serial);
     Serial.println("Not Authorized");
     switch (alarmStatus) {
      case true:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("THE CARD IS NOT");
        lcd.setCursor(0,1);
        lcd.print("AUTHORIZED");
        digitalWrite(redLed, LOW);
        delay(500);
        digitalWrite(redLed, HIGH);
        tone(buzzer, 1200);
        delay(2000);
        noTone(buzzer);
        LCDML.FUNC_goBackToMenu();
        break;
        
      case false:
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("THE CARD IS NOT");
        lcd.setCursor(0,1);
        lcd.print("AUTHORIZED");
        digitalWrite(greenLed, LOW);
        delay(500);
        digitalWrite(redLed, HIGH);
        tone(buzzer, 1200);
        delay(2000);
        noTone(buzzer);
        digitalWrite(redLed, LOW);
        digitalWrite(greenLed, HIGH);
        LCDML.FUNC_goBackToMenu();
        break;
     }
     
   }
   
   nfc.haltTag();
   
   delay(2000);
 }//if (status == MI_OK)

 delay(500);

}

//This function is called when the countdown has stopped to check if there is a card trying to disable
void disable_Trigger() {
 byte status;
 byte data[MAX_LEN];
 byte serial[5];
 status = nfc.requestTag(MF1_REQIDL, data);

 if (status == MI_OK) {
   status = nfc.antiCollision(data);
   memcpy(serial, data, 5);
   
   if(isAuthorized(serial)) //Authorized card found, the alarm disarms
   { 
     Serial.println("Authorized");
     alarmStatus = false;
     Serial.println(alarmStatus);
   }else {  //Not authorized card found, an sms is send to alert the intrusion
     sendSMS_triggered();

   }
   
   nfc.haltTag();
   
   delay(2000);
 }else { //Card not found, an sms is send to alert the intrusion
    sendSMS_triggered();

  }

 delay(500);

}

//Functions to make work the RFID module
bool isSame(byte *key, byte *serial)
{
   for (int i = 0; i < 4; i++) {
     if (key[i] != serial[i])
     { 
       return false; 
     }
   }
   
   return true;

}

bool isAuthorized(byte *serial)
{
   for(int i = 0; i<AUTHORIZED_COUNT; i++)
   {
     if(isSame(serial, Authorized[i]))
       return true;
   }
  return false;
}

void printSerial(byte *serial)
{
       Serial.print("Serial:");
   for (int i = 0; i < 5; i++) {
     Serial.print(serial[i], HEX);
     Serial.print(" ");
   }
}
