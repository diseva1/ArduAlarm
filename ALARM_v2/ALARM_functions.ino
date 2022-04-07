
#define greenLed    7
#define redLed  6
#include "timer.h"

Timer timer;
int t;

//Countodown function is called when the alarm is triggred
void countdown() {
  t--;
  Serial.println(t);
  lcd.setCursor(0,1);
  lcd.print(t);
  lcd.print(" ");
  tone(buzzer, 700);
  delay(300);
  noTone(buzzer);
}

void setup_sensor ()
{
  pinMode(doorSensor, INPUT_PULLUP);
}
//This function ARMs the alarm when is called
void alarm_ARM ()
{
  digitalWrite(redLed, HIGH);
  digitalWrite(greenLed, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("THE ALARM IS:");
  lcd.setCursor(0,1);
  lcd.print("ARMED");
  tone(buzzer, 900);
  delay(200);
  noTone(buzzer); 
}

//This function DISARMs the alarm when is called
void alarm_DISARM () 
{
  digitalWrite(greenLed, HIGH);
  digitalWrite(redLed, LOW);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("THE ALARM IS:");
  lcd.setCursor(0,1);
  lcd.print("DISARMED");
  tone(buzzer, 900);
  delay(200);
  noTone(buzzer);  
}

//This function is called when the sensors are opened
void alarm_TRIGGER ()
{
  t = countdownTime;
  timer.setInterval(600);
  timer.setCallback(countdown);
         
  if(digitalRead(doorSensor) == HIGH){
    Serial.println("layer 1");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("INTRUSION!!!");    
      timer.start();
      while(t > 0) {
        timer.update();
      }
    if(t != countdownTime){
      t = countdownTime;
    }
    if(digitalRead(doorSensor) == HIGH){
      Serial.println("layer 2");
      setup_RFID();
      disable_Trigger();
      Serial.println("Abierto");
      switch(alarmStatus){
        case true:
          tone(buzzer, 900);
          for(int i=0;i<10;i++){
              digitalWrite(redLed, LOW);
              delay(500);
              digitalWrite(redLed, HIGH);
              delay(1000);
            }
          noTone(buzzer);
          break;

         case false:
          digitalWrite(redLed, LOW);
          LCDML.OTHER_jumpToFunc(mFunc_screensaver);
          break;
      }
      
    } else {
      Serial.println("layer 2");
      Serial.println("Cerrado");
      delay(1000);
      LCDML.MENU_goRoot();
    }
  }
}
