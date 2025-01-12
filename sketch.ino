#include <Wire.h>
#include <MPU6050.h>
#include "model.h"  // Include the model header file generated from Python

MPU6050 mpu;

void setup() {
  Serial.begin(115200);
  Wire.begin();
  mpu.initialize();

  if (mpu.testConnection()) {
    Serial.println("MPU6050 connected successfully!");
  } else {
    Serial.println("MPU6050 connection failed!");
  }

  delay(1000);  // Give time for sensor to stabilize
}

void loop() {
  int16_t ax, ay, az, gx, gy, gz;
  mpu.getAcceleration(&ax, &ay, &az);  // Get accelerometer data
  mpu.getRotation(&gx, &gy, &gz);  // Get gyroscope data

  // Prepare the feature vector
  float features[6] = {ax, ay, az, gx, gy, gz};

  // Predict the gesture using the model
  int gesture_index = GestureRecognizer::predict(features);  // Use the 'predict' method
  const char* gesture = GestureRecognizer::idx2label(gesture_index);  // Map index to label

  // Print the predicted gesture
  Serial.print("Predicted Gesture: ");
  Serial.println(gesture);

  delay(500);  // Wait for 500 ms before next prediction
}
