
#define BLYNK_TEMPLATE_ID "TMPL3uK0d3QEd"
#define BLYNK_TEMPLATE_NAME "Smart Dustin"
#define BLYNK_AUTH_TOKEN "wXnm1-bT3GLriBHkuBv8TgyVXLf6fMmT"

#define BLYNK_PRINT Serial

#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <ESP32Servo.h>

char auth[] = "wXnm1-bT3GLriBHkuBv8TgyVXLf6fMmT";
char ssid[] = "Jay Hanuman";
char pass[] = "Jayshreekrishna@";

BlynkTimer timer;

#define echoPin 32
#define trigPin 33
#include<Servo.h>
Servo servo;
long duration;
int distance; 
int binLevel=0;

void SMESensor()
{
  int ir=digitalRead(34);
  if(ir==HIGH)
  {    
    servo.write(90);
    for(int i=0; i<50; i++)
    {
      Blynk.virtualWrite(V2, 90);
      ultrasonic(); 
      delay(100);
    }
    servo.write(0);
    Blynk.virtualWrite(V2, 0);
  }
  if(ir==LOW)
  {
    
    ultrasonic();
    delay(200);
  }
}
void ultrasonic()
{
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    duration = pulseIn(echoPin, HIGH);
    distance = duration * 0.034 / 2; //formula to calculate the distance for ultrasonic sensor
    binLevel=map(distance, 21, 0, 0,100); // ADJUST BIN HEIGHT HERE
    Blynk.virtualWrite(V0, distance);
    Blynk.virtualWrite(V1, binLevel);
}
void setup()
{
  Serial.begin(9600);
  servo.attach(13);
  pinMode(34, INPUT);
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 
   Blynk.begin(auth, ssid, pass);
  delay(2000);
  timer.setInterval(1000L, SMESensor);
}

void loop() 
{
  Blynk.run();
  timer.run();
}