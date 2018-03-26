#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX    usbserial uart 
const int relePin = 2;    // pin del disparador del rele
int incomingByte;        // bit de entrada por serial   

void setup()
{
  mySerial.begin(9600);   //inicializo puerto myserial 
  pinMode(relePin, OUTPUT); //inicializo pin salida rele
}

void loop() 
{
  if (mySerial.available())
  {
    incomingByte = mySerial.read();   //lee bit por serial 
    if (incomingByte == 'a') {        // 'a' apagar rele
     digitalWrite(relePin, LOW);       
    }
    if (incomingByte == 'e') {       // 'e' encender rele 
     digitalWrite(relePin, HIGH);
    }
  }
}