/*
   This is the code for controlling 4 appliances and 
   sending DHT11 sensor's data to Blynk App.

   After that, I made my own voice app using which, I
   can directly ask the status of appliances and value
   of Temeprature and Humidity directly to my Alexa
   smart speaker.

   You can visit the channel to see
   complete tutorial on making this project
   by yoursleves

   YouTube Channel :- https://www.youtube.com/techiesms


          techiesms
   explore | learn | share
*/

/* Comment this out to disable prints and save space */
#define BLYNK_PRINT Serial

#include "DHT.h"

#define DHTPIN D7  

#define DHTTYPE DHT11 

DHT dht(DHTPIN, DHTTYPE);
//#include <WiFi.h>
//#include <WiFiClient.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
BlynkTimer timer;

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "AUTH_TOKEN";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "SSID";
char pass[] = "PASS";
#define switchone D6
#define switchtwo D2
#define switchthree D1
#define switchfour D5

void sendSensor()
{
  float h = dht.readHumidity();
  float t = dht.readTemperature(); // or dht.readTemperature(true) for Fahrenheit

  if (isnan(h) || isnan(t)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  // You can send any value at any time.
  // Please don't send more that 10 values per second.
  Blynk.virtualWrite(V5, t);
  Blynk.virtualWrite(V6, h);
}

BLYNK_WRITE(V1)
{
  int pinValue = param.asInt();
  digitalWrite(switchone,pinValue);
  }

BLYNK_WRITE(V2)
{
  int pinValue = param.asInt();
  digitalWrite(switchtwo,pinValue);
  }

BLYNK_WRITE(V3)
{
  int pinValue = param.asInt();
  digitalWrite(switchthree,pinValue);
  }

BLYNK_WRITE(V4)
{
  int pinValue = param.asInt();
  digitalWrite(switchfour,pinValue);
  }

void setup()
{
  // Debug console
  Serial.begin(9600);
  pinMode(switchone,OUTPUT);
  pinMode(switchtwo,OUTPUT);
  pinMode(switchthree,OUTPUT);
  pinMode(switchfour,OUTPUT);
  digitalWrite(switchone,LOW);
  digitalWrite(switchtwo,LOW);
  digitalWrite(switchthree,LOW);
  digitalWrite(switchfour,LOW);
  Blynk.begin(auth, ssid, pass);
  dht.begin();
  // Setup a function to be called every second
  timer.setInterval(1000L, sendSensor);
  
}

void loop()
{
  Blynk.run();
  timer.run();
  
}
