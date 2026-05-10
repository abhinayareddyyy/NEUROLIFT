# Problem Statement - Neurolift

## What is Foot Drop?

Foot drop is a condition where a person cannot lift the front part of their foot while walking, causing the toes to drag on the ground. This can result from:

- Muscle weakness in the anterior tibialis muscle
- Nerve damage affecting motor control
- Neurological disorders (stroke, MS, Parkinson's, etc.)
- Spinal cord injury
- Brain injury or trauma

People with foot drop experience:
- Toe dragging during walking
- Increased tripping and fall risk
- Altered walking patterns
- Reduced mobility and confidence

---

## Current Treatment Options

Existing rehabilitation solutions include:
- **Physical therapy:** Non-invasive but time-consuming
- **Ankle-Foot Orthosis (AFO):** Passive support device, often bulky
- **Electrical stimulation (FES):** Active muscle engagement, expensive
- **Surgery:** Invasive, long recovery time
- **Botulinum injection:** Temporary, requires repeated treatments

These solutions have limitations:
- High cost (medical devices are expensive)
- Bulky or uncomfortable for daily wear
- Limited accessibility and availability
- Difficult to customize for individual needs
- No real-time feedback or monitoring

---

## The Solution

Neurolift is an affordable, student-built prototype that demonstrates foot drop detection and mechanical assistance using:

- **MPU6050 sensor:** Detects foot angle during walking
- **EMG sensor:** Detects muscle activity
- **Arduino microcontroller:** Processes sensor data and makes decisions
- **SG90 servo motor:** Provides mechanical foot lift assistance

The system detects when the foot droops (angle > 45°) and automatically activates the servo motor to lift the foot, preventing toe dragging and reducing trip risk.

---

## Learning Outcomes

Building Neurolift teaches:

**Technical Skills:**
- Embedded systems programming (Arduino)
- Sensor integration and signal processing
- Real-time decision-making logic
- Wearable electronics design
- I2C communication protocol

**Domain Knowledge:**
- Gait biomechanics basics
- Assistive technology principles
- Rehabilitation engineering concepts
- IoT applications in healthcare

---

## Project Scope

### What This System Does
- Detects abnormal foot movement patterns
- Demonstrates mechanical assistance mechanism
- Serves as an educational IoT prototype
- Provides hands-on learning platform

### What This System Does NOT Do
- Provide medical-grade rehabilitation (educational only)
- Replace professional medical devices
- Treat neurological conditions
- Provide sufficient force for independent walking without assistance

### Target Users
- BTech students (1st-2nd year)
- Electronics and embedded systems enthusiasts
- Rehabilitation engineering learners
- Hackathon participants

---

*Last Updated: 2025*
*For implementation details, see architecture.md and workflow.md*
