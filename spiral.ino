#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>
#include <Servo.h>  
// Set these to run example.

#define FIREBASE_HOST "spiral-6f434.firebaseio.com"
#define FIREBASE_AUTH "uZJcSMbA8q3vb2pWPN1ROqEKvqGeP4Bho37WGeh8"

#define WIFI_SSID "Markiv"
#define WIFI_PASSWORD "87654321"

#define M1 12
#define M2 11
int servoPin = 3; 
int st,temp,a,b,c;
// Create a servo object 
Servo spiral; 
void setup() {

//  Servo1.attach(servoPin); 
  Serial.begin(9600);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println("Connected!!");
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
}

void loop() {

  temp=1;
  st=Firebase.getInt("/Path/status");
  if(temp == 1 && st!=0 && st>=1 && st<=4)
  {
     temp=0;
     String path = "/Path/var/";
     path = path + st;
     String pathA = path + "/a";
     String pathB = path + "/b";
     String pathC = path + "/c";
     a=Firebase.getInt(pathA);
     b=Firebase.getInt(pathB);
     c=Firebase.getInt(pathC);

     Firebase.setBool("/Path/available",false);
     
  
digitalWrite(M1,HIGH);
digitalWrite(M2,HIGH);
delay(a*1000);
digitalWrite(M1,LOW);
digitalWrite(M2,LOW);
spiral.write(b);
digitalWrite(M1,HIGH);
digitalWrite(M2,HIGH); 
delay(c*1000);
digitalWrite(M1,LOW);
digitalWrite(M2,LOW);  
     delay(10000);
     Serial.println(st);
     Serial.println(a);
     Serial.println(b);
     Serial.println(c);
     Firebase.setBool("/Path/available",true);
     Firebase.setInt("/Path/status",0);
     
}
}