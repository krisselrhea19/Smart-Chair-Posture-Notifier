
// This is the initial code we used to test the circuit on TinkerCad and
// also to ensure the FSRs were working fine

const int FSR1_PIN = 34;   // ADC pin - FSR1
const int FSR2_PIN = 35;   // ADC pin - FSR2

// --- Temp Threshold Value ---
int THRESHOLD = 500;

void setup() {
  Serial.begin(115200);
  delay(1000);

  Serial.println("FSR Posture Test Started...");
}

void loop() {
  int fsr1 = analogRead(FSR1_PIN);
  int fsr2 = analogRead(FSR2_PIN);

  
  Serial.print("FSR1: ");
  Serial.print(fsr1);
  Serial.print(" | FSR2: ");
  Serial.println(fsr2);

  //  threshold logic for time being
  if (fsr1 > THRESHOLD && fsr2 > THRESHOLD) {
    Serial.println("Posture: GOOD ");
  } 
  else {
    Serial.println("Posture: BAD ");
  }

  Serial.println("-------------------------");
  delay(500);
}
