import cv2
import serial
import time
import argparse
import os
import numpy as np
from ultralytics import YOLO

# ===== ARGUMENT PARSER =====
parser = argparse.ArgumentParser()
parser.add_argument('--model', required=True, help='Path ke file YOLO .pt')
parser.add_argument('--source', required=True, help='Index kamera, contoh: 0')
args = parser.parse_args()

# ===== INISIALISASI SERIAL =====
try:
    ser = serial.Serial('COM3', 115200, timeout=1)
    time.sleep(2)
    print("[INFO] ESP32 terhubung.")
except Exception as e:
    print(f"[WARNING] ESP32 connection failed: {e}")
    ser = None

# ===== LOAD MODEL YOLO =====
model_path = args.model
print(f"[INFO] Loading YOLO model from: {model_path}")
model = YOLO(model_path)

# ===== INISIALISASI KAMERA =====
cap = cv2.VideoCapture(int(args.source))
if not cap.isOpened():
    print("[ERROR] Kamera tidak tersedia.")
    exit(1)

print("[INFO] Kamera aktif. Menjalankan deteksi...")

# ===== LOGIKA UTAMA =====
moving = False  # Status apakah robot sedang jalan

while True:
    ret, frame = cap.read()
    if not ret:
        print("[WARNING] Gagal membaca frame dari kamera.")
        continue

    results = model(frame, verbose=False)
    detections = results[0].boxes

    object_detected = len(detections) > 0

    # Cetak status deteksi
    if object_detected:
        print("[INFO] Objek terdeteksi. Mengirim perintah: 0 (STOP)")
        if ser: ser.write(b'0')
        moving = False
    else:
        if not moving:
            print("[INFO] Tidak ada objek. Mengirim perintah: 1 (MAJU)")
            if ser: ser.write(b'1')
            moving = True

    # Gambar hasil deteksi
    annotated_frame = results[0].plot()
    cv2.imshow("YOLO Detection", annotated_frame)

    key = cv2.waitKey(1) & 0xFF
    if key == ord('q'):
        print("[INFO] Keluar dari program.")
        break

# ===== CLEANUP =====
cap.release()
cv2.destroyAllWindows()
if ser:
    ser.close()