#define BLYNK_TEMPLATE_ID "TMPL6o63fRCHF"
#define BLYNK_TEMPLATE_NAME "Smartfarming"
#define BLYNK_AUTH_TOKEN "hAS7d2RuB5JLrvbXqM7ReuLhptmh3-oo"

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>

#define LDR 34
#define LED 21

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT);
  Blynk.begin(auth, ssid, pass);
}

void loop(){
  int nilaiLDR = analogRead(LDR);
  delay(10);
  Blynk.virtualWrite(V0, nilaiLDR);
  if (nilaiLDR > 800){
    digitalWrite(LED, HIGH);
    Blynk.virtualWrite(V1, 1);
  } else {
    digitalWrite(LED, LOW);
    Blynk.virtualWrite(V1, 0);
  }
}
