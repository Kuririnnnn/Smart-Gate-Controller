#include <ESP32Servo.h>

const int trigPin  = 5;
const int echoPin  = 18;
const int servoPin = 13;
const int ledPin   = 4;

const int threshold = 100;

Servo gateServo;

long  duration;
float distance;

bool vehiclePresent = false;
bool waiting        = false;
bool gateOpen       = false;

unsigned long timer = 0;

unsigned long lastLedToggle = 0;
bool          ledState      = false;
const int     LED_BLINK_MS  = 300;

const int SERVO_STEP_MS = 12;

float getDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  return duration * 0.034 / 2;
}

void blinkLed() {
  unsigned long now = millis();
  if (now - lastLedToggle >= LED_BLINK_MS) {
    lastLedToggle = now;
    ledState = !ledState;
    digitalWrite(ledPin, ledState ? HIGH : LOW);
  }
}

void ledOff() {
  ledState = false;
  digitalWrite(ledPin, LOW);
}

void sweepServo(int from, int to) {
  int step = (to > from) ? 1 : -1;
  for (int angle = from; angle != to + step; angle += step) {
    gateServo.write(angle);
    unsigned long stepStart = millis();
    while (millis() - stepStart < SERVO_STEP_MS) {
      blinkLed();
    }
  }
}

void setup() {
  Serial.begin(115200);

  pinMode(trigPin,  OUTPUT);
  pinMode(echoPin,  INPUT);
  pinMode(ledPin,   OUTPUT);

  gateServo.attach(servoPin);
  gateServo.write(0);

  ledOff();
}

void loop() {

  distance       = getDistance();
  vehiclePresent = (distance > 0 && distance <= threshold);

  Serial.print("Distance: ");
  Serial.println(distance);

  if (vehiclePresent) {

    waiting = false;

    if (gateOpen) {
      Serial.println("Closing Gate");
      sweepServo(90, 0);
      ledOff();
      gateOpen = false;
    }
  }

  else {

    if (!gateOpen && !waiting) {
      waiting = true;
      timer   = millis();
      Serial.println("Waiting 5 seconds...");
    }

    if (waiting && millis() - timer >= 5000) {
      Serial.println("Opening Gate");
      sweepServo(0, 90);
      ledOff();
      gateOpen = true;
      waiting  = false;
    }
  }

  delay(100);
}
