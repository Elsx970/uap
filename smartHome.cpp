#define BLYNK_TEMPLATE_ID ""
#define BLYNK_TEMPLATE_NAME ""
#define BLYNK_AUTH_TOKEN ""

#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Wokwi-GUEST";
char pass[] = "";

const int triggerUltrasonic = 16;
const int echoUltrasonic = 17;
const int buzzerPin = 4;

BlynkTimer timer;

int getDistance() {
  digitalWrite(triggerUltrasonic, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerUltrasonic, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerUltrasonic, LOW);

  int duration = pulseIn(echoUltrasonic, HIGH, 30000);
  if (duration == 0) return -1;

  int distance = duration * 0.03428 / 2;
  return distance;
}

void sendDistance() {
  int distance = getDistance();
  if (distance == -1) {
    Blynk.virtualWrite(V0, 0);
  } else {
    Blynk.virtualWrite(V0, distance);
  }
}

void setup() {
  pinMode(triggerUltrasonic, OUTPUT);
  pinMode(echoUltrasonic, INPUT);
  pinMode(buzzerPin, OUTPUT);
  digitalWrite(buzzerPin, LOW);

  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  timer.setInterval(500L, sendDistance);
}

void loop() {
  Blynk.run();
  timer.run();

  static unsigned long previousMillis = 0;
  static bool buzzOn = false;

  int distance = getDistance();
  if (distance == -1) {
    noTone(buzzerPin);
    Blynk.virtualWrite(V1, 0);

    lcd.setCursor(0, 0);
    lcd.print("Jarak : -- cm  ");
    lcd.setCursor(0, 1);
    lcd.print("Sensor error   ");

    delay(500);
    return;
  }

  lcd.setCursor(0, 0);
  lcd.print("Jarak : ");
  if (distance < 100) lcd.print(" ");
  if (distance < 10) lcd.print(" ");
  lcd.print(distance);
  lcd.print(" cm   ");

  unsigned int interval;
  if (distance < 10) {
    interval = 100;
  } else if (distance > 200) {
    interval = 2000;
  } else {
    interval = map(distance, 10, 200, 100, 2000);
  }

  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;

    if (!buzzOn) {
      tone(buzzerPin, 2000);
      buzzOn = true;
    } else {
      noTone(buzzerPin);
      buzzOn = false;
    }
    Blynk.virtualWrite(V1, buzzOn ? 255 : 0);
  }
}
