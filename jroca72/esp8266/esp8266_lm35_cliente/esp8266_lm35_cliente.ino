#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

ESP8266WebServer server(80);
const int sensorPin= A0;  //pin de sensor de temperatura LM35 
IPAddress ip(192,168,0,212);
IPAddress gateway(192,168,0,1);
IPAddress subnet(255,255,255,0);

void handlePath() 
{
  int value = analogRead(sensorPin);
  float millivolts = (value / 1023.0) * 3300; //3300 minivoltios por alimentación de esp8266
  float celsius = millivolts / 10; 
  String numero = String(celsius,2);  //convierto la temperatura a string para pasarlo por web
  server.send(200, "text/plain", numero);
}

void setup()
{
    Serial.begin(115200);
    WiFi.config(ip,gateway,subnet); // ponemos ip fija 
    WiFi.begin("senfios", "password"); 

    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.println("Waiting to connect…");
    }
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());    // mando por serial la ip del ESP8266 para conectarse 

    server.on("/Python", handlePath);   // asigno la funcion handlePath a los requests a la carpeta Python
    server.begin();        
    
    Serial.println("Server listening");
}

void loop() 
{
    server.handleClient(); 
}


