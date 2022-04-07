/* ===================================================================== *
 *                                                                       *
 * Menu Callback Function                                                *
 *                                                                       *
 * ===================================================================== *
 */



// *********************************************************************
void mFunc_screensaver(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    
    setup_RFID();
    setup_readSMS();
    setup_sensor();
    
    // update LCD content
    lcd.clear();
    lcd.setCursor(0, 0); // set cursor
    lcd.print("THE ALARM IS:"); // print change content
    lcd.setCursor(0, 1); // set cursor
     if(alarmStatus) {
      lcd.print("ARMED");
      pinMode(redLed, OUTPUT);
      digitalWrite(redLed, HIGH);
    } else if(!alarmStatus) {
      lcd.print("DISARMED");
      pinMode(greenLed, OUTPUT);
      digitalWrite(greenLed, HIGH);
    }
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())
  {
        
    check_RFID();
    func_readSMS();
    if(alarmStatus){
      alarm_TRIGGER();
    }
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }  
  }

  if(LCDML.FUNC_close())
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}



// *********************************************************************
void mFunc_back(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // end function and go an layer back
    LCDML.FUNC_goBackToMenu(1);      // leave this function and go a layer back
  }
}


// *********************************************************************
void mFunc_goToRootMenu(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    // go to root and display menu
    LCDML.MENU_goRoot();
  }
}




// *********************************************************************
void alarm_status(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
    
    lcd.init();
    lcd.backlight();
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("ALARM STATUS:");
    lcd.setCursor(0,1);

    if(alarmStatus) {
      lcd.print("ARMED");
    } else if(!alarmStatus) {
      lcd.print("DISARMED");
    }
    delay(2000);
    LCDML.FUNC_setLoopInterval(100);  // starts a trigger event for the loop function every 100 milliseconds
  }

  if(LCDML.FUNC_loop())
  {      
    if (LCDML.BT_checkAny()) // check if any button is pressed (enter, up, down, left, right)
    {
      LCDML.FUNC_goBackToMenu();  // leave this function
    }
  }

  if(LCDML.FUNC_close())
  {
    // The screensaver go to the root menu
    LCDML.MENU_goRoot();
  }
}


// *********************************************************************
void mFunc_silentMode_on(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("SILENT MODE IS");
     lcd.setCursor(0,1);
     lcd.print("ACTIVATED");

     delay(3000);
    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
      LCDML.MENU_goRoot();
    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    buzzer = 0;
  }
}

// *********************************************************************
void mFunc_silentMode_off(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("SILENT MODE IS");
     lcd.setCursor(0,1);
     lcd.print("DESACTIVATED");

     delay(3000);
    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
      LCDML.MENU_goRoot();
    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    buzzer = 8;
  }
}

// *********************************************************************
void mFunc_countdown_5s(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("COUNTDOWN SET TO");
     lcd.setCursor(0,1);
     lcd.print("5 SECONDS");

     delay(3000);
    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
      LCDML.MENU_goRoot();
    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    countdownTime = 6;
  }
}

// *********************************************************************
void mFunc_countdown_10s(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("COUNTDOWN SET TO");
     lcd.setCursor(0,1);
     lcd.print("10 SECONDS");

     delay(3000);
    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
      LCDML.MENU_goRoot();
    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    countdownTime = 11;
  }
}

// *********************************************************************
void mFunc_countdown_15s(uint8_t param)
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("COUNTDOWN SET TO");
     lcd.setCursor(0,1);
     lcd.print("15 SECONDS");

     delay(3000);
    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
      LCDML.MENU_goRoot();
    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    countdownTime = 16;
  }
}

// *********************************************************************
void mFunc_countdown_20s(uint8_t param) 
// *********************************************************************
{
  if(LCDML.FUNC_setup())          // ****** SETUP *********
  {
     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("COUNTDOWN SET TO");
     lcd.setCursor(0,1);
     lcd.print("20 SECONDS");

     delay(3000);
    // starts a trigger event for the loop function every 100 milliseconds
    LCDML.FUNC_setLoopInterval(100);
  }

  if(LCDML.FUNC_loop())           // ****** LOOP *********
  {
     LCDML.MENU_goRoot();
    
  }

  if(LCDML.FUNC_close())      // ****** STABLE END *********
  {
    countdownTime = 21;
  }
}
