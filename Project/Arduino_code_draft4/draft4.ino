#include <Servo.h>

Servo myservo;

const int Lin = 5, Rin = 12, Lout = 6, Rout = 13; 
const int serv = 9; 
long Rduration, Lduration, Rinches, Linches;
int threshold = 10;
int angle = 80;
boolean debug = true;  // Set to true to enable debugging
unsigned long previousMillis = 0;  
const long interval = 100;  

int stepSize = 5;  

void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);

  myservo.attach(serv);
  myservo.write(angle);
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    readUltrasonics();
    follow();
    if (Linches <= threshold || Rinches <= threshold) {
      Serial1.println("find a movement around the gate");
      if (debug) {
        Serial.println("Message sent: find a movement around the gate");
      }
    }
  }
}

void readUltrasonics() {
  pinMode(Rout, OUTPUT);
  digitalWrite(Rout, LOW);
  delayMicroseconds(2);
  digitalWrite(Rout, HIGH);
  delayMicroseconds(5);
  digitalWrite(Rout, LOW);
  Rduration = pulseIn(Rin, HIGH);

  pinMode(Lout, OUTPUT);
  digitalWrite(Lout, LOW);
  delayMicroseconds(2);
  digitalWrite(Lout, HIGH);
  delayMicroseconds(5);
  digitalWrite(Lout, LOW);
  Lduration = pulseIn(Lin, HIGH);

  Rinches = microsecondsToInches(Rduration);
  Linches = microsecondsToInches(Lduration);

  if (debug) {
    Serial.print("Left: ");
    Serial.print(Linches);
    Serial.print(" in, Right: ");
    Serial.print(Rinches);
    Serial.println(" in");
  }
}

long microsecondsToInches(long microseconds) {
  return microseconds / 74 / 2;
}

void follow() {
  if (Linches <= threshold || Rinches <= threshold) {
    if (Linches + 2 < Rinches) {
      angle = angle - stepSize;  // Move left faster
    }
    if (Rinches + 2 < Linches) {
      angle = angle + stepSize;  // Move right faster
    }
  }

  // Limit servo angle between 0 and 160 degrees
  if (angle > 160) {
    angle = 160;
  }
  if (angle < 0) {
    angle = 0;
  }

  myservo.write(angle);  // Update servo position
}
