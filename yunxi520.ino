#include <SoftwareSerial.h>
#include "DFRobotDFPlayerMini.h"
#include <pitches.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <NewPing.h>

SoftwareSerial mySoftwareSerial(10, 11);
DFRobotDFPlayerMini myDFPlayer;

#define Vibration1 5
#define Vibration2 6
#define TRIGGER_PIN 2 // Arduino pin tied to triggerpin on the ultrasonic sensor.
#define ECHO_PIN 3 // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 400 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
int state0=0;
int state=0;
unsigned long last_time = 0;
int i=0;
int distance0=0;

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

void setup() {
  mySoftwareSerial.begin(9600);
  myDFPlayer.begin(mySoftwareSerial);
  Serial.begin(9600);
  myDFPlayer.volume(0);
  myDFPlayer.loop(1); 
  
  pinMode(Vibration1, OUTPUT);
  pinMode(Vibration2, OUTPUT);
  analogWrite(Vibration1,0);
  analogWrite(Vibration2,0);
}

void loop() {
  int uS = sonar.ping(); // Send ping, get ping time in microseconds (uS).
  int distance = uS / US_ROUNDTRIP_CM;// Convert ping time to distance in cm and print result (0 = outside set distance range)
  float vib0=map(distance,0,300,16,0);
  int vib=vib0*vib0-1;
  int sound=map(distance,0,300,30,0);
  analogWrite(Vibration1,vib);
  analogWrite(Vibration2,vib);
  myDFPlayer.volume(sound);

  Serial.print("DIS:");
  Serial.print(distance); 
  Serial.print(", VIB:"); 
  Serial.print(vib); 
  Serial.print(", SOUND:"); 
  Serial.println(sound); 

  delay(100);
}