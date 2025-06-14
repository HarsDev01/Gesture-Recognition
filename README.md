# 🤖 Gesture-Based Smart Dashboard (Arduino + MPU6050 + Wokwi)

An advanced gesture recognition project using the MPU6050 accelerometer to control multiple virtual devices like fans, lights, alarms, and doors — all simulated entirely on [Wokwi](https://wokwi.com).

## 🚀 Features

- 🧭 Detect Left, Right, Up, Down, and Shake gestures
- 💡 Turn fan/light ON/OFF with specific tilt directions
- 🚪 Unlock door by holding device still + password gesture pattern (e.g., Left → Up → Right)
- 🔔 Trigger emergency alarm on shake (buzzer)
- 🧪 Fully testable in the Wokwi simulator (no hardware required)

## 🛠 Tech Stack

- Arduino UNO
- MPU6050 (Accelerometer + Gyroscope)
- Wokwi Online Simulator
- LEDs + Buzzer
- Embedded C (Arduino IDE)

## 🎮 Gesture Mapping

| Gesture       | Action Triggered         |
|---------------|--------------------------|
| Tilt Left     | Fan ON (Red LED)         |
| Tilt Right    | Fan OFF                  |
| Tilt Up       | Room Light ON (Yellow)   |
| Tilt Down     | Room Light OFF           |
| Shake         | Emergency Alarm (Buzzer) |
| Hold still 2s | Check password pattern   |
| Pattern: LUR  | Unlock Door (Green LED)  |

## 🧠 Smart Motion Pattern

> A predefined motion pattern like `LUR` (Left → Up → Right) unlocks the door after 2s of no motion.

## 🧪 How to Run in Wokwi

1. Visit: [https://wokwi.com](https://wokwi.com)
2. Create new Arduino project
3. Replace code with `main.ino`
4. Paste `wokwi.json` into the project
5. Click **Start Simulation**
6. Use MPU6050 controls to simulate gestures

## 🖼 Circuit Preview

Wokwi circuit includes:
- Arduino UNO
- MPU6050 via I2C
- 3 LEDs (Fan, Light, Door)
- 1 Buzzer (Alarm)

<img width="713" alt="Screenshot 2025-06-14 at 4 07 24 PM" src="https://github.com/user-attachments/assets/d52f8e27-7f92-4293-9372-a95fc1ad21ca" />


