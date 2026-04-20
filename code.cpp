// Pin Definitions
const int waterSensorPin = A0; 
const int motorMosfetPin = 9;  
const int electrodeMosfetPin = 10; 

// Sensitivity Adjustment
// 0 = Bone Dry, 1023 = Direct Short Circuit
// Start with 200 and increase if you get false alarms.
const int waterThreshold = 200; 

void setup() {
  pinMode(motorMosfetPin, OUTPUT);
  pinMode(electrodeMosfetPin, OUTPUT);
  
  // Safety: Ensure systems are OFF until the sensor is checked
  digitalWrite(motorMosfetPin, LOW);
  digitalWrite(electrodeMosfetPin, LOW);
  
  Serial.begin(9600);
}

void loop() {
  int sensorValue = analogRead(waterSensorPin);
  
  // Output value to Serial Monitor (Tools > Serial Monitor) 
  // to see what your "wet" vs "dry" numbers actually look like.
  Serial.print("Sensor Value: ");
  Serial.println(sensorValue);

  if (sensorValue > waterThreshold) {
    // WATER DETECTED: Shut everything down
    digitalWrite(motorMosfetPin, LOW);
    digitalWrite(electrodeMosfetPin, LOW);
  } else {
    // DRY: Run systems normally
    digitalWrite(motorMosfetPin, HIGH);
    digitalWrite(electrodeMosfetPin, HIGH);
  }

  delay(200); // 5 checks per second is plenty for a safety shut-off
}
