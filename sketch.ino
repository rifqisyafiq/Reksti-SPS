#define trigPin1 6
#define echoPin1 7
#define trigPin2 8
#define echoPin2 9
#define trigPin3 10
#define echoPin3 11
#define buzzer1 12
#define buzzer2 13
#define buzzer3 A0

bool bool1 = false;
bool bool2 = false;
bool bool3 = false;

long readUltrasonicDistance(int triggerPin, int echoPin) {
  digitalWrite(triggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(triggerPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(triggerPin, LOW);
  pinMode(echoPin, INPUT);
  long duration = pulseIn(echoPin, HIGH, 10000);  // Timeout after 10 ms
  if (duration == 0) {
    return -1;  // No pulse received within timeout
  }
  return duration;
}

void firstsensor() {
  float distance1 = (readUltrasonicDistance(trigPin1, echoPin1) * 0.034) / 2;
  Serial.print("Distance 1: ");
  Serial.println(distance1);
  if (distance1 == -1) {
    Serial.println("Sensor 1 timeout");
  }
  if (distance1 >= 32 || distance1 <= 0.2 || distance1 == -1) {
    bool1 = false;
    digitalWrite(buzzer1, LOW);
  } else {
    bool1 = true;
    digitalWrite(buzzer1, LOW);
    if (distance1 <= 40) {
      digitalWrite(buzzer1, HIGH);
    }
  }
}

void secondsensor() {
  float distance2 = (readUltrasonicDistance(trigPin2, echoPin2) * 0.034) / 2;
  Serial.print("Distance 2: ");
  Serial.println(distance2);
  if (distance2 == -1) {
    Serial.println("Sensor 2 timeout");
  }
  if (distance2 >= 32 || distance2 <= 0.2 || distance2 == -1) {
    bool2 = false;
    digitalWrite(buzzer2, LOW);
  } else {
    bool2 = true;
    digitalWrite(buzzer2, LOW);
    if (distance2 <= 40) {
      digitalWrite(buzzer2, HIGH);
    }
  }
}

void thirdsensor() {
  float distance3 = (readUltrasonicDistance(trigPin3, echoPin3) * 0.034) / 2;
  Serial.print("Distance 3: ");
  Serial.println(distance3);
  if (distance3 == -1) {
    Serial.println("Sensor 3 timeout");
  }
  if (distance3 >= 32 || distance3 <= 0.2 || distance3 == -1) {
    bool3 = false;
    digitalWrite(buzzer3, LOW);
  } else {
    bool3 = true;
    digitalWrite(buzzer3, LOW);
    if (distance3 <= 40) {
      digitalWrite(buzzer3, HIGH);
    }
  }
}

void setup() {
  Serial.begin(9600);
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);
  pinMode(trigPin3, OUTPUT);
  pinMode(echoPin3, INPUT);
  pinMode(buzzer1, OUTPUT);
  pinMode(buzzer2, OUTPUT);
  pinMode(buzzer3, OUTPUT);
  digitalWrite(buzzer1, LOW);
  digitalWrite(buzzer2, LOW);
  digitalWrite(buzzer3, LOW);
}

void loop() {
  firstsensor();
  delay(200);
  secondsensor();
  delay(200);
  thirdsensor();
  delay(200);

  if (!bool1 && !bool2 && !bool3) {
    Serial.println("All slots empty");
  } else if (bool1 && !bool2 && !bool3) {
    Serial.println("Slot 1 filled, Slots 2 and 3 empty");
  } else if (!bool1 && bool2 && !bool3) {
    Serial.println("Slot 2 filled, Slots 1 and 3 empty");
  } else if (bool1 && bool2 && !bool3) {
    Serial.println("Slots 1 and 2 filled, Slot 3 empty");
  } else if (!bool1 && !bool2 && bool3) {
    Serial.println("Slot 3 filled, Slots 1 and 2 empty");
  } else if (bool1 && !bool2 && bool3) {
    Serial.println("Slots 1 and 3 filled, Slot 2 empty");
  } else if (!bool1 && bool2 && bool3) {
    Serial.println("Slots 2 and 3 filled, Slot 1 empty");
  } else {
    Serial.println("All slots filled");
  }

  delay(200);
}
