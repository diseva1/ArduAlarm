//Codigo parte del proyecto ArduAlarm V1.0 para el sensor de ultrasonidos HC-SR04
long dis;
long tiem;
int led1 = 11;
void setup( ){
Serial.begin(9600);
pinMode(10, OUTPUT); //salida del pulso generado por el sensor ultrasónico
pinMode(9, INPUT);//entrada del pulso generado por el sensor ultrasónico
pinMode(11, INPUT);//alarma de la distancia(encenderá el led)
}
void loop(){
digitalWrite;(10,LOW);//recibimiento del pulso.
delayMicroseconds(5);
digitalWrite(10, HIGH);//envió del pulso.
delayMicroseconds(10);
tiem=pulseIn(9, HIGH);//fórmula para medir el pulso entrante.
dis= long(0.017*tiem);//fórmula para calcular la distancia del sensor ultrasónico.
if(dis>10){ //comparativo para la alarma se ingresa la distancia en la que encenderá o apagara.
digitalWrite (11, HIGH);
}
else 
{
digitalWrite(11,LOW); 
}
}
