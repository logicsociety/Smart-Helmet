#define TRIG_PIN 18
#define ECHO_PIN 4
#define PIR_PIN 16

void setup() {
  Serial.begin(115200);
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);
  Serial.println("System Initialized...");
}

void loop() {
  // --- Ultrasonic Sensor ---
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2000);  // settle the sensor
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);    // 10us pulse
  digitalWrite(TRIG_PIN, LOW);

  // Measure echo duration with timeout (60 ms = 10 m range)
  long duration = pulseIn(ECHO_PIN, HIGH, 60000);

  if (duration == 0) {
    Serial.println(" No echo detected (Check wiring or object too far)");
  } else {
    // Convert to cm
    float distanceCm = (duration * 0.0343) / 2.0;

    // Filter invalid readings
    if (distanceCm > 2 && distanceCm < 400) {
      Serial.printf("Distance: %.2f cm\n", distanceCm);
      if (distanceCm < 5) {
        Serial.println("Crash Detected!");
      }
    } else {
      Serial.println("Out of range reading (Invalid echo)");
    }
  }

  // --- PIR Motion Sensor ---
  int motionState = digitalRead(PIR_PIN);
  if (motionState == HIGH) {
    Serial.println("Motion Detected!");
  } else {
    Serial.println("No Motion.");
  }

  Serial.println("-----------------------");
  delay(1000);
}