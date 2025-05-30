#define BLYNK_TEMPLATE_ID "TMPL6e-qQOC6U"
#define BLYNK_TEMPLATE_NAME "Smarthome"
#define BLYNK_AUTH_TOKEN "0uu1LzFzbMsOl8nIwQ_FwyUbjjscLz6r"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define trig 18
#define echo 19
#define buzzer 17

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

void setup(){
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);
  //Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

}

int getDistance() {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  int duration = pulseIn(echo, HIGH);

  int distance = duration * 0.03428 / 2;
  return distance;
}

void loop(){
  int jarak = getDistance();
  Blynk.virtualWrite(V0, jarak);
  
  if (jarak < 100){
    tone(buzzer, 2000);
    Blynk.virtualWrite(V1, 1);
  }
  else {
    noTone(buzzer);
    Blynk.virtualWrite(V1, 0);
  }
}
