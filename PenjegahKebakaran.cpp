#define BLYNK_TEMPLATE_ID "TMPL6e-qQOC6U"
#define BLYNK_TEMPLATE_NAME "Smarthome"
#define BLYNK_AUTH_TOKEN "0uu1LzFzbMsOl8nIwQ_FwyUbjjscLz6r"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define mq2 34
#define buzzer 17

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";
int nilaiAwal = 0;

void setup(){
  pinMode(mq2, INPUT);
  pinMode(buzzer, OUTPUT);
  noTone(buzzer);
  //Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  delay(10000);
  nilaiAwal = analogRead(mq2);

}

void loop(){
  int realTime = analogRead(mq2);
  Blynk.virtualWrite(V0, realTime);
  
  if (realTime - nilaiAwal > 100){
    tone(buzzer, 2000);
    Blynk.virtualWrite(V1, 1);
  }
  else {
    noTone(buzzer);
    Blynk.virtualWrite(V1, 0);
  }
}
