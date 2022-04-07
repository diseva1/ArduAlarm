// *********************************************************************
// includes
// *********************************************************************
  #include <Wire.h>
  #include <LiquidCrystal_I2C.h>
  #include <LCDMenuLib2.h>

// *********************************************************************
// LCDML display settings
// *********************************************************************
  // settings for LCD
  #define _LCDML_DISP_cols  16
  #define _LCDML_DISP_rows  2

  #define _LCDML_DISP_cfg_cursor                     0x7E   // cursor Symbol
  #define _LCDML_DISP_cfg_scrollbar                  1      // enable a scrollbar

  // LCD object
  LiquidCrystal_I2C lcd(0x3f,_LCDML_DISP_cols,_LCDML_DISP_rows);

  const uint8_t scroll_bar[5][8] = {
    {B10001, B10001, B10001, B10001, B10001, B10001, B10001, B10001}, // scrollbar top
    {B11111, B11111, B10001, B10001, B10001, B10001, B10001, B10001}, // scroll state 1
    {B10001, B10001, B11111, B11111, B10001, B10001, B10001, B10001}, // scroll state 2
    {B10001, B10001, B10001, B10001, B11111, B11111, B10001, B10001}, // scroll state 3
    {B10001, B10001, B10001, B10001, B10001, B10001, B11111, B11111}  // scrollbar bottom
  };

// *********************************************************************
// Prototypes
// *********************************************************************
  void lcdml_menu_display();
  void lcdml_menu_clear();
  void lcdml_menu_control();

// *********************************************************************
// Global variables
// *********************************************************************
  bool alarmStatus;
  bool silentMode = false;
  int countdownTime = 11;
  int doorSensor = 4;
  int buzzer = 8;
// *********************************************************************
// Objects
// *********************************************************************
  LCDMenuLib2_menu LCDML_0 (255, 0, 0, NULL, NULL); // root menu element (do not change)
  LCDMenuLib2 LCDML(LCDML_0, _LCDML_DISP_rows, _LCDML_DISP_cols, lcdml_menu_display, lcdml_menu_clear, lcdml_menu_control);

// *********************************************************************
// LCDML MENU/DISP
// *********************************************************************
  // LCDML_0        => layer 0
  // LCDML_0_X      => layer 1
  // LCDML_0_X_X    => layer 2
  // LCDML_0_X_X_X  => layer 3
  // LCDML_0_...      => layer ...

  // LCDML_add(id, prev_layer, new_num, lang_char_array, callback_function)
  
    LCDML_add(0, LCDML_0, 1, "STATUS", alarm_status);
    LCDML_add(1, LCDML_0, 2, "SETTINGS", NULL);
      LCDML_add(2, LCDML_0_2, 1, "SILENT MODE", NULL);
        LCDML_add(3, LCDML_0_2_1, 1, "ON", mFunc_silentMode_on);
        LCDML_add(4, LCDML_0_2_1, 2, "OFF", mFunc_silentMode_off);
        LCDML_add(5, LCDML_0_2_1, 3, "BACK", mFunc_back);
      LCDML_add(6, LCDML_0_2, 2, "COUNTDOWN", NULL);
        LCDML_add(7, LCDML_0_2_2, 1, "5s", mFunc_countdown_5s);
        LCDML_add(8, LCDML_0_2_2, 2, "10s", mFunc_countdown_10s);
        LCDML_add(9, LCDML_0_2_2, 3, "15s", mFunc_countdown_15s);
        LCDML_add(10, LCDML_0_2_2, 4, "20s", mFunc_countdown_20s);
        LCDML_add(11, LCDML_0_2_2, 5, "BACK", mFunc_back);
      LCDML_add(12, LCDML_0_2, 4, "BACK", mFunc_back);
    LCDML_add(13, LCDML_0, 3, "SCREENSAVER", mFunc_screensaver);
        
  
  // menu element count - last element id
  // this value must be the same as the last menu element
  #define _LCDML_DISP_cnt    13 

  // create menu
  LCDML_createMenu(_LCDML_DISP_cnt);

// *********************************************************************
// SETUP
// *********************************************************************
  void setup()
  {
    // serial init; only be needed if serial control is used
    Serial.begin(9600);                // start serial
    Serial.println(F(_LCDML_VERSION)); // only for examples

    // LCD Begin
    lcd.init();
    lcd.backlight();
    //lcd.begin(_LCDML_DISP_cols,_LCDML_DISP_rows);  // some display types needs here the initialization


    // set special chars for scrollbar
    lcd.createChar(0, (uint8_t*)scroll_bar[0]);
    lcd.createChar(1, (uint8_t*)scroll_bar[1]);
    lcd.createChar(2, (uint8_t*)scroll_bar[2]);
    lcd.createChar(3, (uint8_t*)scroll_bar[3]);
    lcd.createChar(4, (uint8_t*)scroll_bar[4]);

    // LCDMenuLib Setup
    LCDML_setup(_LCDML_DISP_cnt);

    // Some settings which can be used

    // Enable Menu Rollover
    LCDML.MENU_enRollover();

    // Enable Screensaver (screensaver menu function, time to activate in ms)
    LCDML.SCREEN_enable(mFunc_screensaver, 10000); // set to 10 seconds
    //LCDML.SCREEN_disable();

    // Some needful methods

    // You can jump to a menu function from anywhere with
    //LCDML.OTHER_jumpToFunc(mFunc_p2); // the parameter is the function name
  }

// *********************************************************************
// LOOP
// *********************************************************************
  void loop()
  {
    LCDML.loop();
  }
