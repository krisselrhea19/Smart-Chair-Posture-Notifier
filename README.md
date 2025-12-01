🪑 Smart Chair Posture Notifier

An IoT + Android system that detects incorrect sitting posture using Force Sensitive Resistors (FSR) mounted on a chair and alerts the user through a buzzer and a mobile application.
Designed to encourage healthy posture habits and reduce long-term back strain.

📌 Project Overview

This project monitors the user’s sitting posture in real time.
When the pressure distribution on the chair indicates slouching or leaning, the system:

Activates a buzzer alert

Sends the posture status to the Android app

Displays “Correct” or “Incorrect” posture on the phone

🔧 Hardware Components

ESP32 Development Board

Force Sensitive Resistors (FSR)

Buzzer

Jumper Wires

Power Supply

Chair Base (for sensor placement)

💻 Software & Technologies

Arduino IDE (for ESP32 programming)

Android Studio (Java/Kotlin)

Bluetooth / WiFi for communication

GitHub for version control

⚙️ System Workflow

User sits on the chair → FSRs detect pressure.

ESP32 reads sensor data.

If posture is incorrect:

Buzzer turns ON

Mobile app receives “Incorrect posture”

If posture is correct:

Buzzer remains OFF

App displays “Correct posture”

🔍 Posture Detection Logic

FSRs measure pressure at multiple points on the chair.

ESP32 compares values to preset thresholds.

Uneven pressure = slouching/leaning → alert triggered.

Balanced pressure = correct posture.

🚀 Features

Real-time posture detection

Immediate buzzer alert

Mobile notifications

Simple hardware setup

User-friendly Android interface

📌 Future Enhancements

Add vibration motor instead of buzzer

Store posture history in cloud

Add calorie & sitting-time tracking

Integrate with smartwatch

ML-based posture analysis

👥 Team

Krissel Rhea

Teammate 1

Teammate 2

📄 License

This project is for educational use only.
