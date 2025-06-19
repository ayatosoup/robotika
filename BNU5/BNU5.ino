char myData = 0;

// Motor Kiri
int motor1Pin1 = 22;
int motor1Pin2 = 23;
int enable1Pin = 21;

// Motor Kanan
int motor2Pin1 = 17;
int motor2Pin2 = 18;
int enable2Pin = 16;

// LED bawaan ESP32
const int ledPin = 2;

// PWM
const int freq = 30000;
const int pwmChannel1 = 0;
const int pwmChannel2 = 1;
const int resolution = 8;
const int dutyCycle = 255;

void setup() {
  Serial.begin(115200);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);
  pinMode(enable2Pin, OUTPUT);
  pinMode(ledPin, OUTPUT);

  ledcSetup(pwmChannel1, freq, resolution);
  ledcSetup(pwmChannel2, freq, resolution);

  ledcAttachPin(enable1Pin, pwmChannel1);
  ledcAttachPin(enable2Pin, pwmChannel2);

  ledcWrite(pwmChannel1, 0);
  ledcWrite(pwmChannel2, 0);
}

void loop() {
  if (Serial.available() > 0) {
    myData = Serial.read();

    // Reset LED (matikan terlebih dahulu)
    digitalWrite(ledPin, LOW);

    if (myData == '1') {  // Maju
      Serial.println("Robot Maju");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      digitalWrite(ledPin, HIGH); // LED nyala terus

    } else if (myData == '2') {  // Belok kanan → pola 1,0,1,1
      Serial.println("Belok Kanan");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, HIGH);
      digitalWrite(ledPin, HIGH);

    } else if (myData == '3') {  // Belok kiri → pola 1,1,0,1
      Serial.println("Belok Kiri");
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
      digitalWrite(ledPin, HIGH);

    } else if (myData == '4') {  // Mundur → blink cepat
      Serial.println("Mundur");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);

      // Blink cepat 3x
      for (int i = 0; i < 6; i++) {
        digitalWrite(ledPin, i % 2);
        delay(100);
      }

    } else if (myData == '0') {  // Berhenti
      Serial.println("Berhenti");
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
      digitalWrite(ledPin, LOW); // LED mati
    }

    // Aktifkan motor
    ledcWrite(pwmChannel1, dutyCycle);
    ledcWrite(pwmChannel2, dutyCycle);
  }
}
