#include <SoftwareSerial.h>

SoftwareSerial mySerial(1, 0); // RX, TX    usbserial uart 
const int ledPin = 13;    // pin de led 
int incomingByte;        // nit de entrada por serial   

void setup()
{
  mySerial.begin(9600);   //inicializo puerto myserial 
  pinMode(ledPin, OUTPUT); //inicializo pin salida led
}

void loop() 
{
  if (mySerial.available())
  {
    incomingByte = mySerial.read();   //lee bit por serial 
    if (incomingByte == 'a') {        // 'a' apagar led 
     digitalWrite(ledPin, LOW);       
    }
    if (incomingByte == 'e') {       // 'e' encender led 
     digitalWrite(ledPin, HIGH);
    }
  }
}