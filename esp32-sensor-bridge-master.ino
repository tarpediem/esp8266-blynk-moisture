#define BLYNK_PRINT Serial


#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <SimpleTimer.h>

char auth[] = "your-auth-token";
const int sensorPin = 4; 
int sensorState = 0;
int lastState = 0;


void setup()
{
  Serial.begin(9600);
  Blynk.begin(auth, "SSID", "PASSWORD");
  pinMode(sensorPin, INPUT);
}

SimpleTimer timer;
WidgetBridge bridge1(V1);

BLYNK_CONNECTED() {
  // Place the AuthToken of the second hardware here
  bridge1.setAuthToken("8bcc18fe51894120b9d303884bcb58f6"); 
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
     bridge1.digitalWrite(2, 1000);
     bridge1.virtualWrite(V5, 1000);
     //update virtual port 5 on second esp
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
    bridge1.digitalWrite(2, 0);
    bridge1.virtualWrite(V5, 0);
    //update virtual port 5 on second esp
    
  }
  
  delay(100);
}
