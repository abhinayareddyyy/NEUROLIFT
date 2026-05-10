/*
 * Neurolift - IoT-Based Smart Foot Drop Rehabilitation System
 * Arduino Uno Implementation
 * 
 * Description:
 * This firmware detects foot drop using MPU6050 accelerometer/gyroscope and EMG sensor,
 * then activates a servo motor to assist foot lifting during walking.
 * 
 * Components:
 * - Arduino Uno
 * - MPU6050 Accelerometer + Gyroscope
 * - EMG Muscle Sensor
 * - SG90 Servo Motor
 * 
 * Author: P Abhinaya Gayatri Reddy, N. V. Dheeraj, Avaneesh
 * Date: 2025
 * Version: 1.0
 */

#include <Wire.h>
#include <MPU6050.h>
#include <Servo.h>

// ============================================
// OBJECT DECLARATIONS
// ============================================
MPU6050 mpu;           // MPU6050 sensor object
Servo ankleServo;      // Servo motor object

// ============================================
// PIN DEFINITIONS
// ============================================
const int EMG_PIN = A0;           // Analog pin for EMG muscle sensor
const int SERVO_PIN = 9;          // Digital pin for servo motor control

// ============================================
// SENSOR THRESHOLDS
// ============================================
const int ANGLE_THRESHOLD = 45;   // Angle threshold for foot drop detection (degrees)
const int EMG_THRESHOLD = 200;    // EMG signal threshold for muscle activity detection

// ============================================
// TIMING & MOTION PARAMETERS
// ============================================
unsigned long lastStepTime = 0;   // Time of last detected step (milliseconds)
unsigned long stepInterval = 0;   // Duration between consecutive steps (milliseconds)
float walkingSpeed = 0;           // Calculated walking speed (meters/second)
const float STEP_LENGTH = 0.75;   // Average step length in meters

// ============================================
// SENSOR DATA VARIABLES
// ============================================
int emgValue = 0;                 // Current EMG sensor reading (0-1023)
float footAngle = 0;              // Calculated foot angle from MPU6050 (degrees)

// ============================================
// SERVO POSITIONS (Angle-based)
// ============================================
const int SERVO_REST = 90;        // Rest position (neutral)
const int SERVO_LOW_SUPPORT = 60; // Low support activation (for slower walking)
const int SERVO_MID_SUPPORT = 45; // Medium support activation (for normal walking)
const int SERVO_HIGH_SUPPORT = 0; // High support activation (for EMG muscle signal)

// ============================================
// SETUP FUNCTION - Runs once on startup
// ============================================
void setup() {
  // Initialize Serial communication for debugging
  Serial.begin(9600);
  
  // Initialize I2C communication
  Wire.begin();
  
  // Initialize MPU6050 sensor
  mpu.initialize();
  
  // Attach servo motor to digital pin
  ankleServo.attach(SERVO_PIN);
  
  // Check if MPU6050 is properly connected
  if (!mpu.testConnection()) {
    Serial.println("ERROR: MPU6050 connection failed!");
    Serial.println("Please check I2C connections (SDA=A4, SCL=A5)");
    while (1);  // Halt execution if sensor not detected
  }
  
  Serial.println("Neurolift System Initialized");
  Serial.println("MPU6050 connected successfully!");
  
  // Set EMG pin as input
  pinMode(EMG_PIN, INPUT);
  
  // Initialize servo to rest position
  ankleServo.write(SERVO_REST);
  
  delay(500);  // Wait for servo to move to rest position
  Serial.println("System ready. Starting foot drop detection...");
}

// ============================================
// MAIN LOOP - Runs continuously
// ============================================
void loop() {
  // --------- Read EMG Sensor ---------
  // EMG sensor provides analog signal proportional to muscle activity
  emgValue = analogRead(EMG_PIN);
  
  // --------- Read MPU6050 Sensor ---------
  // Get acceleration data from all three axes
  int16_t ax, ay, az;  // Acceleration values (raw sensor data)
  int16_t gx, gy, gz;  // Gyroscope values (not used in current logic)
  
  mpu.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);
  
  // --------- Calculate Foot Angle ---------
  // Convert acceleration to angle using arctangent
  // This represents the ankle/foot orientation relative to gravity
  footAngle = atan2(ay, az) * 180.0 / PI;
  
  // --------- Debug Output ---------
  // Print sensor values to Serial Monitor
  Serial.print("Foot Angle: ");
  Serial.print(footAngle);
  Serial.print("° | EMG Value: ");
  Serial.print(emgValue);
  Serial.print(" | Walking Speed: ");
  Serial.print(walkingSpeed);
  Serial.println(" m/s");
  
  // =========================================
  // MAIN CONTROL LOGIC
  // =========================================
  
  // Check if foot angle exceeds threshold (indicates foot drop)
  if (footAngle > ANGLE_THRESHOLD) {
    
    // Detect step by checking Y-axis acceleration spike
    // High acceleration in Y-axis indicates foot lifting phase
    if (ay > 15000) {
      
      // --------- Calculate Walking Speed ---------
      unsigned long currentTime = millis();
      stepInterval = currentTime - lastStepTime;
      lastStepTime = currentTime;
      
      // Walking speed = step length / time taken (m/s)
      // Avoid division by zero
      if (stepInterval > 0) {
        walkingSpeed = STEP_LENGTH / (stepInterval / 1000.0);
      }
      
      // --------- Adjust Servo Based on Walking Speed ---------
      // Faster walking = more assistance needed
      if (walkingSpeed > 1.2) {
        // Fast walking: Maximum support
        ankleServo.write(SERVO_MID_SUPPORT);
        Serial.println("► Fast walking detected - Medium support activated");
      } 
      else if (walkingSpeed > 0.8) {
        // Normal walking: Moderate support
        ankleServo.write(SERVO_LOW_SUPPORT);
        Serial.println("► Normal walking detected - Low support activated");
      } 
      else {
        // Slow walking: Minimal support
        ankleServo.write(SERVO_REST);
        Serial.println("► Slow walking - Rest position");
      }
    }
    
    // --------- Check for Muscle Activity (EMG Signal) ---------
    // If muscle activity is detected above threshold, provide maximum support
    if (emgValue > EMG_THRESHOLD) {
      Serial.println("★ STRONG muscle activity detected! Maximum support activated");
      ankleServo.write(SERVO_HIGH_SUPPORT);
    } 
    else {
      // If no muscle activity and angle is normal, return to rest
      ankleServo.write(SERVO_REST);
    }
  } 
  else {
    // Normal foot position: No foot drop detected
    // Keep servo at rest position for energy efficiency
    ankleServo.write(SERVO_REST);
  }
  
  // --------- Sensor Sampling Rate ---------
  // Wait 100ms before next sensor reading
  // This provides adequate responsiveness (10 samples per second)
  delay(100);
}

// ============================================
// HELPER FUNCTIONS (Optional)
// ============================================

/*
 * Function: activateSupport()
 * Purpose: Activate servo motor with specified intensity
 * 
 * Intensity Levels:
 * 0 = Maximum support (full lift)
 * 1 = Medium support
 * 2 = Low support
 * 3 = Rest (no support)
 */
void activateSupport(int intensityLevel) {
  switch(intensityLevel) {
    case 0:
      ankleServo.write(SERVO_HIGH_SUPPORT);
      break;
    case 1:
      ankleServo.write(SERVO_MID_SUPPORT);
      break;
    case 2:
      ankleServo.write(SERVO_LOW_SUPPORT);
      break;
    case 3:
      ankleServo.write(SERVO_REST);
      break;
    default:
      ankleServo.write(SERVO_REST);
  }
}

/*
 * Function: getServoAngle()
 * Purpose: Get current servo position
 * Returns: Current angle (0-180 degrees)
 */
int getServoAngle() {
  // Note: Read position requires additional library support
  // This is a placeholder for future enhancement
  return 90;  // Default return
}

// ============================================
// END OF FIRMWARE
// ============================================
