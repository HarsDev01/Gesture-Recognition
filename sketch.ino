#include <Wire.h>
#include <MPU6050.h>

MPU6050 mpu;
int16_t ax, ay, az;

const int FAN_LED = 2;
const int LIGHT_LED = 3;
const int DOOR_LED = 4;
const int BUZZER = 5;

unsigned long stillTime = 0;
bool doorUnlocked = false;
String motionPassword = "";
String correctPattern = "LUR"; // Left → Up → Right

void setup() {
  Serial.begin(9600);
  Wire.begin();
  mpu.initialize();

  pinMode(FAN_LED, OUTPUT);
  pinMode(LIGHT_LED, OUTPUT);
  pinMode(DOOR_LED, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  if (!mpu.testConnection()) {
    Serial.println("MPU6050 connection failed");
    while (1);
  }

  Serial.println("MPU6050 ready.");
}

void loop() {
  mpu.getAcceleration(&ax, &ay, &az);

  Serial.print("ax: "); Serial.print(ax);
  Serial.print(" ay: "); Serial.print(ay);
  Serial.print(" az: "); Serial.println(az);

  bool still = abs(ax) < 1000 && abs(ay) < 1000 && abs(az - 16384) < 2000;

  if (ax < -10000) { // Left
    Serial.println("Gesture: Left");
    digitalWrite(FAN_LED, HIGH);
    motionPassword += "L";
    delay(500);
  }
  else if (ax > 10000) { // Right
    Serial.println("Gesture: Right");
    digitalWrite(FAN_LED, LOW);
    motionPassword += "R";
    delay(500);
  }
  else if (ay > 12000) { // Up
    Serial.println("Gesture: Up");
    digitalWrite(LIGHT_LED, HIGH);
    motionPassword += "U";
    delay(500);
  }
  else if (ay < -12000) { // Down
    Serial.println("Gesture: Down");
    digitalWrite(LIGHT_LED, LOW);
    motionPassword += "D";
    delay(500);
  }

  // Shake detection (quick z-axis movement)
  if (abs(ax) > 15000 || abs(ay) > 15000 || abs(az - 16384) > 8000) {
    Serial.println("Shake Detected! Triggering Alarm");
    digitalWrite(BUZZER, HIGH);
    delay(300);
    digitalWrite(BUZZER, LOW);
  }

  // Check for still hold (unlock door)
  if (still) {
    if (stillTime == 0) stillTime = millis();
    else if (millis() - stillTime > 2000 && !doorUnlocked) {
      Serial.println("Holding still. Checking password...");
      if (motionPassword.endsWith(correctPattern)) {
        Serial.println("✅ Door Unlocked!");
        digitalWrite(DOOR_LED, HIGH);
        doorUnlocked = true;
      } else {
        Serial.println("❌ Incorrect motion pattern.");
      }
      motionPassword = "";
    }
  } else {
    stillTime = 0;
  }

  delay(200);
} 
