//Añadimos las librerias para el codigo
#include <Password.h>
#include <Keypad.h>
#include <HologramSIMCOM.h>
#include <SoftwareSerial.h>

//Configuracion del keypad
const byte ROWS = 4;
const byte COLS = 4;
char hexaKeys [ROWS] [COLS] = {
  {'D','#','0','*'},
  {'C','9','8','7'},
  {'B','6','5','4'},
  {'A','3','2','1'}
  };
  
byte rowPins[ROWS] = {2,3,4,5}; 
byte colPins[COLS] = {6,7,8,9}; 
Keypad customKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS); 

//Configuracion de la contraseña
String newPasswordString; //hold the new password
char newPassword[6]; //charater string of newPasswordString
Password password = Password( "1234" ); 
byte maxPasswordLength = 6; 
byte currentPasswordLength = 0;

//Configuracion de Hologram
#define RX_PIN 0
#define TX_PIN 1
#define RESET_PIN 13
#define HOLO_KEY "********"

HologramSIMCOM Hologram(TX_PIN, RX_PIN, RESET_PIN, HOLO_KEY);

void setup() {
  Serial.begin(9600);
  }

void loop(){
   char key = customKeypad.getKey();
   if (key != NO_KEY){
      delay(60); 
      switch (key){
      case 'A': break; 
      case 'B': break; 
      case 'C': break; 
      case 'D': changePassword(); break; 
      case '#': checkPassword(); break;
      case '*': resetPassword(); break;
      default: processNumberKey(key);
      }
   }
}
 
void processNumberKey(char key) {
   Serial.print(key);
   currentPasswordLength++;
   password.append(key);
   if (currentPasswordLength == maxPasswordLength) {
      checkPassword();
   } 
}

void checkPassword() {
   if (password.evaluate()){
      Serial.println(" OK.");
   } else {
      Serial.println(" ¡Contrasena Incorrecta!");
   } 
   resetPassword();
}

void resetPassword() {
   password.reset(); 
   currentPasswordLength = 0; 
}

void changePassword() {
   newPasswordString = "123";
   newPasswordString.toCharArray(newPassword, newPasswordString.length()+1); //convert string to char array
password.set(newPassword);
   resetPassword();
   Serial.print("Contrasena cambiada a ");
   Serial.println(newPasswordString);
}
