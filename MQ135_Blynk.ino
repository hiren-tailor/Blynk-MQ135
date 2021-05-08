#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

BlynkTimer timer;

char auth[] = "vEwEpjq0Iox17eMpYYOdfXJvdMl2vyEO";   //enter your token from email
char ssid[] = "Hiren";                              //enter your wifi username
char pass[] = "123456789";                          //enter your wifi password

const int BUZ = 5;  //buzzer to nodemcu D1 (GPIO-5)
const int LED = 4;  //LED to nodemcu D2 (GPIO-4)
int mq135 = A0;     //smoke sensor is connected with the analog pin A0
int data = 0;

void sensorData()
{
  data = analogRead(mq135);           //read A0 pin of NodeMCU
  Blynk.virtualWrite(V2,data);        //virtual pin V2
  
  if (data > 200)                     //trigger buzzer if if smoke sensor value is greate than 400
  {
      tone(BUZ,1000);                   // Send 1KHz sound signal…
      delay(1000);
      digitalWrite(LED,HIGH);
      delay(1000);                      // …for 1 sec
  }
  else
  {
    digitalWrite(LED,LOW);
    digitalWrite(BUZ,LOW);
  }
}

void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass,"188.166.206.43");  //PING blynk-cloud.com
  timer.setInterval(1000L, sensorData);
  pinMode(BUZ, OUTPUT); // Set BUZ 
  pinMode(LED, OUTPUT); // Set LED 
}

void loop() {
  Blynk.run();
  timer.run();
}
