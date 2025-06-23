# REPOSITORI ROBOTIKA
Nama: Ahmad Nadhif Fikri Syahbana
Npm: 22081010139  
Link Demo:   

# 🤖 AMBATRON - Automated Monitoring Bot for Anomalies

**AMBATRON** (Automated Monitoring Bot for Anomalies) is a surveillance robot built with an ESP32 microcontroller and computer vision system. The robot moves forward by default and automatically stops when it detects visual anomalies using a trained detection model (such as YOLO). This project explores the integration of robotics and machine learning to simulate anomaly detection in real-world environments.

---

## 📸 Core Features

- 🧠 Detects anomalies using image recognition (e.g., italian anomalies brainrot, unusual objects)
- 🤖 ESP32-controlled movement: forward, left, right, reverse, and stop
- 📷 Real-time detection using laptop webcam
- 🔌 Serial communication between Python (host) and ESP32 (robot)
- 🧪 Manual and automatic modes for testing and control

---

---

## 🚀 How It Works

1. **Default Behavior:** The robot moves forward continuously.
2. **Camera Input:** A webcam captures live frames.
3. **Detection Model:** Python processes frames using a trained model (YOLO/classifier).
4. **Anomaly Detected:** Python sends a stop signal (`b'0'`) to ESP32 over serial.
5. **Safe Again:** Python sends a go signal (`b'1'`) to resume movement.

---

## ⚙️ How to Run

### 1. Upload ESP32 Code

Open `esp32-code/ambatron.ino` in Arduino IDE, select your ESP32 board and upload.

### 2. Install Python Dependencies

```bash
pip install -r requirements.txt
```

### 3. Run the Python Program

```bash
cd python/
python ambatron_control.py
```

Choose between:
- **Manual Mode:** Control robot with keyboard
- **Automatic Mode:** Camera detects anomalies automatically

## 📷 Sample Use Cases

- Detecting visual anomalies
- Prototyping AI-powered patrol robots
- Integrating YOLO with robotics platforms

---
## ⚠️ Disclaimer

This project is intended for educational and experimental purposes only.
