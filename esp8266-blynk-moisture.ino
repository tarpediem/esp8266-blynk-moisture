#define BLYNK_PRINT 



#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "authentication token";
const int sensorPin = 4; 
int sensorState = 0;
int lastState = 0;


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "SSID", "Password");
  pinMode(sensorPin, INPUT);
}

void loop()
{ 
  Blynk.run();

  sensorState = digitalRead(sensorPin);
Serial.println(sensorState);

if (sensorState == 1 && lastState == 0) {
  Serial.println("needs water, send notification");
  Blynk.notify("Water your plants");
  lastState = 1;
  delay(1000);
//send notification
    
  } 
  else if (sensorState == 1 && lastState == 1) {
    //do nothing, has not been watered yet
  Serial.println("has not been watered yet");
  delay(1000);
  }
  else {
    //st
    Serial.println("does not need water");
    lastState = 0;
    delay(1000);
  }
  
  delay(100);
}
