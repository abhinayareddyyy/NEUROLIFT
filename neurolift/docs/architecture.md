# System Architecture - Neurolift

## Components

- **Arduino Uno** - Main microcontroller for sensor processing and servo control
- **MPU6050** - Detects foot angle and movement
- **EMG Sensor** - Detects muscle electrical activity
- **SG90 Servo Motor** - Provides mechanical foot lift assistance
- **Mechanical Linkage** - String/fishing line connects servo to ankle brace

---

## Pin Connections

| Component | Arduino Pin |
|-----------|------------|
| MPU6050 SDA | A4 |
| MPU6050 SCL | A5 |
| EMG Sensor | A0 |
| Servo Motor | Pin 9 |
| Power | 5V |
| Ground | GND |

---

## How It Works

1. **Walking starts:** User begins walking normally
2. **Swing phase begins:** Foot needs to lift
3. **Sensors detect:** MPU6050 measures foot angle, EMG measures muscle activity
4. **Arduino calculates:** Determines if foot drop is occurring
5. **Decision made:** Based on angle, speed, and muscle activity
6. **Servo activates:** Motor rotates to lift the foot
7. **Foot lifts:** Mechanical linkage pulls foot upward
8. **Toe clears ground:** Prevents tripping and toe dragging
9. **Walking continues:** Process repeats for each step

---

## System Flow

1. **Sensors read data** - MPU6050 detects foot angle; EMG detects muscle activity
2. **Arduino processes** - Compares values against thresholds
3. **Decision made** - If foot angle > 45°, servo activates
4. **Servo moves** - Motor rotates based on walking speed and muscle activity
5. **Foot lifts** - Mechanical linkage prevents toe dragging

---

*Last Updated: 2025*
*For firmware, see firmware/neurolift.ino*
*For wiring details, see hardware/wiring-guide.md*
