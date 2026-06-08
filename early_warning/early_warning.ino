// MQ-4 Early Warning System Setup
const int mq4Pin = A0;         // Analog pin connected to MQ-4
const int warningLed = 13;      // Early warning indicator light
const float R0_CLEAN_AIR = 10.0; // Your sensor's base resistance (Calibrate this first!)

// Threshold constants
const float PRE_ALARM_PPM = 1000.0; // Early warning target (far below certified alarm)

void setup() {
  Serial.begin(9600);
  pinMode(warningLed, OUTPUT);
}

void loop() {
  int rawADC = analogRead(mq4Pin);
  
  // 1. Calculate sensor resistance (Rs) from voltage divider
  float sensor_volt = (float)rawADC / 1023.0 * 5.0;
  float Rs = (5.0 - sensor_volt) / sensor_volt; // Assumes standard 10k Load Resistor
  
  // 2. Calculate the ratio Rs/R0
  float ratio = Rs / R0_CLEAN_AIR;
  
  // 3. Formula derived from the curve log-log graph in datasheet: PPM = 10^(log10(ratio)*m + b)
  // For MQ-4 methane curve: slope (m) ≈ -0.38, intercept (b) ≈ 2.30
  float ppm = pow(10, ((log10(ratio) - 0.35) / -0.38)); 
  // Print diagnostics to the Serial Monitor
  Serial.print("Methane PPM: ");
  Serial.println(ppm);

  // 4. Trigger early warning check
  if (ppm >= PRE_ALARM_PPM) {
    digitalWrite(warningLed, HIGH); // Turn on early warning indicator
  } else {
    digitalWrite(warningLed, LOW);
  }

  delay(1000); // Check once per second
}
