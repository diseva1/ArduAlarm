#include <SoftwareSerial.h>
#include <Separador.h>

//Create software serial object to communicate with SIM800L
SoftwareSerial mySerial(3, 2); //SIM800L Tx & Rx is connected to Arduino #3 & #2

char incomingByte; 
String inputString;

String response_final;
Separador s;

//This function updates the data in the serial and it's called after sending a command to the module
void updateSerial()
{
  delay(500);
  while (Serial.available()) 
  {
    mySerial.write(Serial.read());//Forward what Serial received to Software Serial Port
  }
  while(mySerial.available()) 
  {
    Serial.write(mySerial.read());//Forward what Software Serial received to Serial Port
  }
}

//Prepares the module to read SMS
void setup_readSMS () 
{
  mySerial.begin(9600); 

    while(!mySerial.available()){
       mySerial.println("AT");
       delay(1000); 
       Serial.println("Connecting...");
      }
     Serial.println("Connected!");  
     mySerial.println("AT+CMGF=1");  //Set SMS to Text Mode 
     delay(1000);  
     mySerial.println("AT+CNMI=1,2,0,0,0");  //Procedure to handle newly arrived messages(command name in text: new message indications to TE) 
     delay(1000);
     mySerial.println("AT+CMGL=\"REC UNREAD\""); // Read Unread Messages  
}

/*When the function is called checks if there is a new sms 
and it's content, if matches with one of the conditions makes
a call to its respective function*/
void func_readSMS ()
{
  if(mySerial.available()){
      delay(100);

      // Serial Buffer
      while(mySerial.available()){
        incomingByte = mySerial.read();
        inputString += incomingByte; 
        }

        delay(10);      

        Serial.println(inputString);
        inputString.toUpperCase(); // Uppercase the Received Message

        if (inputString.indexOf("ARM") > -1){
            alarmStatus = true;
            alarm_ARM();
            sendSMS_status();
          }
         if (inputString.indexOf("DISARM") > -1){
            alarmStatus = false;
            alarm_DISARM();
            sendSMS_status();
          }  
         if (inputString.indexOf("STATUS") > -1){
            sendSMS_status();
          }
         if (inputString.indexOf("BATTERY") > -1){
            sendSMS_BATTstatus();
          }          
          
        delay(50);

        //Delete Messages & Save Memory
        if (inputString.indexOf("OK") == -1){
        mySerial.println("AT+CMGDA=\"DEL ALL\"");

        delay(1000);}

        inputString = "";
  }  
}

//This function send the sms when the alarm has detected an intrusion 
void sendSMS_triggered () {
  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+CCXXXXXXXXX\"");//CC is the country code (Spain is 34) and xxxxxxxxxxx the phone number to sms
  updateSerial();
  mySerial.print("Intrusion detected"); //text content
  updateSerial();
  mySerial.write(26);

  delay(500);
  LCDML.FUNC_goBackToMenu();
}

//When the user sends the command asking for the status this function returns the answer
void sendSMS_status ()
{

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+CCXXXXXXXXX\"");//CC is the country code (Spain is 34) and xxxxxxxxxxx the phone number to sms
  updateSerial();
  switch (alarmStatus){
    case 1:
      mySerial.print("The alarm is armed"); //text content
      break;
    case 0:
      mySerial.print("The alarm is disarmed"); //text content
      break;
  }
  updateSerial();
  mySerial.write(26);
}

//When the user sends the command asking for the remaining battery this function returns the answer
void sendSMS_BATTstatus ()
{

  //Begin serial communication with Arduino and SIM800L
  mySerial.begin(9600);

  Serial.println("Initializing..."); 
  delay(1000);

  sendCommand("AT+CBC", "OK", 1000);
  
  mySerial.println("AT"); //Once the handshake test is successful, it will back to OK
  updateSerial();

  mySerial.println("AT+CMGF=1"); // Configuring TEXT mode
  updateSerial();
  mySerial.println("AT+CMGS=\"+CCXXXXXXXXX\"");//CC is the country code (Spain is 34) and xxxxxxxxxxx the phone number to sms
  updateSerial();
  mySerial.println("Battery: "+response_final+"%");
  updateSerial();
  mySerial.write(26);
}

//This command parse the response of the module when asked for the battery and prepares the data to be sent
/*** sendCommand() *********************************************************************
  Send and AT command to the SMS module
  Arguments: AT command, expected answer, timeout
  Returns: 1=Expected answer received, 0=Expected answer not received
  ***********************************************************************************/
  int sendCommand(char* ATcommand, char* expected_answer, unsigned int timeout){
    int answer=0;                                                         //The expected answer has not been received (answer = 0) else (answer = 1)
    int responsePos=0;                                                    //position in the response array
    char response[161];                                                   //Array to store the response from the module
    unsigned long previous;                                               //store the previous millis() for the timeout
  
    memset(response, '\0', 161);                                          // Clears array
    delay(100);
    while( mySerial.available() > 0) mySerial.read();                         // Clean the input buffer
    mySerial.println(ATcommand);                                            // Send the AT command to the SMS module
    Serial.print(F("Sending command = "));
  //  Serial.println(ATcommand);
    responsePos = 0;
    previous = millis();                                                  // the current time to measure timeout
  
    do{                                                                   // this loop waits for the answer until the timeout expires
      // if there is data in the UART input buffer, read it and check for the answer                                                                   
      if(mySerial.available() != 0){                                        //if data is available     
        response[responsePos] = mySerial.read();                            //read the character[in array position responsePos] from the serial port
        Serial.print(response[responsePos]);
        responsePos++;                                                    //move to the next character
        if (strstr(response, expected_answer) != NULL)                    //check if the desired answer is in the response of the module
        {
          String response_raw = response;
          response_raw.replace("\n", "");
          response_raw.replace(" ", "");
          
          response_final = s.separa(response_raw, ',', 1);
          answer = 1;                                                     //there was an answer and it matches the expected answer
        }
      }
    }while((answer == 0) && ((millis() - previous) < timeout));           //Waits for the answer with time out
    Serial.println();
    Serial.println();
    return answer;
  }
