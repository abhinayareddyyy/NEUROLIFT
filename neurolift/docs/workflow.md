# System Workflow - Neurolift

## How It Works

1. **Sensor Detection** - MPU6050 detects foot angle and movement; EMG sensor detects muscle activity
2. **Real-Time Processing** - Arduino reads sensor data every 100ms and calculates foot angle
3. **Decision Making** - If foot angle exceeds 45°, servo motor activates
4. **Mechanical Assistance** - Servo motor lifts the foot via mechanical linkage
5. **Continuous Monitoring** - System loops through this cycle during walking

## Servo Control Rules

- Foot angle > 45° → Foot drop detected → Servo activates
- High muscle activity (EMG > 200) → Maximum support (0°)
- Normal walking speed → Medium support (45°)
- Slow walking → Light support (60°)
- Normal rest state → No assistance (90°)

---

*Last Updated: 2025*
*For implementation code, see firmware/neurolift.ino*
*For detailed architecture, see architecture.md*
