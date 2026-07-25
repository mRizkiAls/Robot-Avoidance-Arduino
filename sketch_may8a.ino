#define echoPin 7
#define trigPin 6

#define FwdRot_LeftMotor 2
#define BckRot_LeftMotor 3
#define FwdRot_RgtMotor 4
#define BckRot_RgtMotor 5

#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 8, 9, 10, 11);

long duration;
float distance;
float lastDistance = 0;

void setup() {

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);

  pinMode(FwdRot_LeftMotor, OUTPUT);
  pinMode(BckRot_LeftMotor, OUTPUT);
  pinMode(FwdRot_RgtMotor, OUTPUT);
  pinMode(BckRot_RgtMotor, OUTPUT);

  lcd.begin(16, 2);
}

void loop() {

  // =========================
  // Trigger Ultrasonic
  // =========================
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);

  // =========================
  // Read Echo
  // =========================
  duration = pulseIn(echoPin, HIGH, 30000);

  // Distance in CM
  distance = duration * 0.034 / 2;

  // Simpan pembacaan terakhir yang valid
  if (distance > 0) {
    lastDistance = distance;
  }
  else {
    distance = lastDistance;
  }

  // =========================
  // LCD DISPLAY
  // =========================
  lcd.clear();

  lcd.setCursor(0, 0);
  lcd.print("Jarak:");
  lcd.print(distance);
  lcd.print("cm");

  // =========================
  // JARAK 200 - 500 CM
  // Belok kiri lalu maju
  // =========================
  if (distance >= 200 && distance <= 500) {

    lcd.setCursor(0, 1);
    lcd.print("Belok Kiri");

    // kiri berhenti
    digitalWrite(FwdRot_LeftMotor, LOW);
    digitalWrite(BckRot_LeftMotor, LOW);

    // kanan maju
    digitalWrite(FwdRot_RgtMotor, HIGH);
    digitalWrite(BckRot_RgtMotor, LOW);

    delay(1000);

    // tampil maju
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Jarak:");
    lcd.print(distance);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("Maju");

    // maju
    digitalWrite(BckRot_LeftMotor, LOW);
    digitalWrite(BckRot_RgtMotor, LOW);

    digitalWrite(FwdRot_LeftMotor, HIGH);
    digitalWrite(FwdRot_RgtMotor, HIGH);

    delay(1000);
  }

  // =========================
  // JARAK > 500 CM
  // Belok kanan lalu mundur
  // =========================
  else if (distance > 500) {

    lcd.setCursor(0, 1);
    lcd.print("Belok Kanan");

    // kiri maju
    digitalWrite(FwdRot_LeftMotor, HIGH);
    digitalWrite(BckRot_LeftMotor, LOW);

    // kanan berhenti
    digitalWrite(FwdRot_RgtMotor, LOW);
    digitalWrite(BckRot_RgtMotor, LOW);

    delay(1000);

    // tampil mundur
    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Jarak:");
    lcd.print(distance);
    lcd.print("cm");

    lcd.setCursor(0, 1);
    lcd.print("Mundur");

    // mundur
    digitalWrite(FwdRot_LeftMotor, LOW);
    digitalWrite(FwdRot_RgtMotor, LOW);

    digitalWrite(BckRot_LeftMotor, HIGH);
    digitalWrite(BckRot_RgtMotor, HIGH);

    delay(1000);
  }

  // =========================
  // KONDISI NORMAL
  // =========================
  else {

    lcd.setCursor(0, 1);
    lcd.print("Maju");

    // maju normal
    digitalWrite(BckRot_LeftMotor, LOW);
    digitalWrite(BckRot_RgtMotor, LOW);

    digitalWrite(FwdRot_LeftMotor, HIGH);
    digitalWrite(FwdRot_RgtMotor, HIGH);

    delay(200);
  }

  delay(50);
}