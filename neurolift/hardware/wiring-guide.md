# Wiring Guide - Neurolift System

## Overview
This document provides detailed instructions for connecting all hardware components to the Arduino Uno for the Neurolift foot drop rehabilitation system.

---

## Connection Diagram Summary

```
┌─────────────────────────────────────────────┐
│         Arduino Uno Pinout                  │
│                                             │
│  Digital Pins: 0-13                        │
│  Analog Pins: A0-A5                        │
│  Power: 5V, GND                            │
└─────────────────────────────────────────────┘
```

---

## 1. MPU6050 (Accelerometer + Gyroscope) Connections

**Purpose:** Detects foot movement and orientation through acceleration and rotation measurements.

### Pin Connections:

| MPU6050 Pin | Arduino Pin | Description |
|------------|-----------|-------------|
| VCC | 5V | Power supply (5V) |
| GND | GND | Ground |
| SDA | A4 | I2C Data line |
| SCL | A5 | I2C Clock line |
| INT | - | Interrupt pin (optional, not used in basic setup) |

### Wiring Steps:

1. Connect MPU6050 **VCC** to Arduino **5V**
2. Connect MPU6050 **GND** to Arduino **GND**
3. Connect MPU6050 **SDA** to Arduino **A4** (I2C Data)
4. Connect MPU6050 **SCL** to Arduino **A5** (I2C Clock)

### Verification:

- Upload the code and check Serial Monitor
- You should see: `"MPU6050 connected successfully!"`
- If connection fails, verify I2C connections and sensor power supply

---

## 2. EMG Muscle Sensor Connections

**Purpose:** Detects muscle electrical activity to determine muscle engagement during walking.

### Pin Connections:

| EMG Sensor Pin | Arduino Pin | Description |
|----------------|-----------|-------------|
| VCC | 5V | Power supply (5V) |
| GND | GND | Ground |
| OUT | A0 | Analog signal output |
| Shield/Shield | GND | Ground (optional shielding) |

### Wiring Steps:

1. Connect EMG Sensor **VCC** to Arduino **5V**
2. Connect EMG Sensor **GND** to Arduino **GND**
3. Connect EMG Sensor **OUT** to Arduino **A0** (Analog Input)
4. If EMG sensor has shielding, connect it to **GND**

### Signal Calibration:

- Open Serial Monitor and observe EMG values with no muscle activity
- Baseline reading should be in range: **0-100**
- When muscles are engaged, reading should jump to **200+**
- Adjust `EMG_THRESHOLD` in code if needed (default: 200)

### Typical EMG Readings:

- **Resting state:** 0-50
- **Light muscle activity:** 50-150
- **Moderate activity:** 150-300
- **Strong activity:** 300-1023

---

## 3. SG90 Servo Motor Connections

**Purpose:** Provides mechanical assistance for foot lifting when foot drop is detected.

### Pin Connections:

| Servo Motor Pin | Arduino Pin | Description |
|----------------|-----------|-------------|
| Power (Red) | 5V | Power supply (5V) |
| Ground (Black/Brown) | GND | Ground |
| Signal (Yellow/White) | Pin 9 | PWM control signal |

### Wiring Steps:

1. Connect servo **Power (Red)** to Arduino **5V**
2. Connect servo **Ground (Black/Brown)** to Arduino **GND**
3. Connect servo **Signal (Yellow/White)** to Arduino **Pin 9**

### Servo Position Reference:

```
Angle    Description        Foot Position
──────────────────────────────────────────
0°       Maximum lift       Full dorsiflexion
45°      Medium lift        Moderate assistance
60°      Low lift          Slight assistance
90°      Rest position     Neutral/relaxed
```

### Testing Servo:

1. Upload code and open Serial Monitor
2. Observe servo movement when system is active
3. Servo should move smoothly between positions
4. If servo jitters or doesn't respond, check power supply

---

## 4. Arduino Uno Power Connections

### Main Power Supply:

| Connection | Cable | Source |
|-----------|--------|--------|
| USB Power | USB-B Cable | Computer or USB Power Bank |
| 5V Rail | Red wire | Arduino 5V output |
| GND Rail | Black wire | Arduino GND |

### Power Distribution:

```
┌─────────────────────┐
│   USB Power Supply  │
│    (5V, ~500mA)    │
└──────────┬──────────┘
           │
      ┌────▼────┐
      │ Arduino │
      │   Uno   │
      └────┬────┘
           │
     ┌─────┴─────┬──────────┬──────────┐
     │           │          │          │
    5V          GND      MPU6050     Servo
   ─┬─          ─┬─      (Power)    (Power)
    │            │          │          │
   EMG         All        VCC         Red
  (Power)      GND        GND        Black
```

### Important Power Notes:

- Use a stable 5V power supply for reliable servo operation

---

## 5. Complete Connection Checklist

### Before Powering On:

- [ ] MPU6050 SDA connected to A4
- [ ] MPU6050 SCL connected to A5
- [ ] MPU6050 VCC connected to 5V
- [ ] MPU6050 GND connected to GND
- [ ] EMG Sensor OUT connected to A0
- [ ] EMG Sensor VCC connected to 5V
- [ ] EMG Sensor GND connected to GND
- [ ] Servo Signal wire connected to Pin 9
- [ ] Servo Power (Red) connected to 5V
- [ ] Servo Ground (Black/Brown) connected to GND
- [ ] No loose wires or short circuits visible
- [ ] All connections are secure

### After Powering On:

- [ ] Serial Monitor shows initialization messages
- [ ] MPU6050 connection confirmed
- [ ] Servo moves to rest position (90°)
- [ ] EMG values visible in Serial Monitor
- [ ] All components receive steady power

---

## 6. Troubleshooting

- **Check wiring connections** - Verify all connections match the pin diagrams
- **Verify power supply** - Ensure 5V power is reaching all components
- **Monitor Serial Output** - Check Arduino IDE Serial Monitor for error messages
- **Test connections** - Use I2C scanner sketch to verify MPU6050 address (0x68)

---

## 7. Safety Precautions

- Always disconnect USB before modifying connections
- Do not exceed 5V on any component
- Servo motor can pinch fingers - keep away during testing
- This is a prototype system - Not for medical use

---

*Last Updated: 2025*
*For troubleshooting, check error messages in Arduino IDE Serial Monitor*