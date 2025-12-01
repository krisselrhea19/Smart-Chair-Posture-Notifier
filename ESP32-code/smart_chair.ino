#include <Preferences.h>

#define FSR_SEAT 26
#define FSR_BACK 2
//#define LED_PIN 25
#define BUZZER_PIN 12

Preferences prefs;

int baseSeat = 0, baseBack = 0;
unsigned long poorPostureStart = 0;
const int window = 5000;

// -------------- Smooth Read (Moving Average) ----------------
int smoothRead(int pin) {
  long sum = 0;
  for (int i = 0; i < 10; i++) {
    sum += analogRead(pin);
    delay(5);
  }
  return sum / 10;
}

// -------------- Calibration Function ------------------------
void calibrateSensors() {
  long sumSeat = 0, sumBack = 0;
  int samples = 200;
  int progressStep = samples / 20;

  Serial.println("Sit upright... Calibration starts in 1s");
  delay(1000);
  Serial.println("Calibrating...");

  for (int i = 1; i <= samples; i++) {
    sumSeat += smoothRead(FSR_SEAT);
    sumBack += smoothRead(FSR_BACK);

    if (i % progressStep == 0) Serial.print(".");
    delay(20);
  }
  Serial.println("\nCalibration complete!");

  baseSeat = sumSeat / samples;
  baseBack = sumBack / samples;

  Serial.print("Seat Baseline = "); Serial.println(baseSeat);
  Serial.print("Back Baseline = "); Serial.println(baseBack);

  // Save to Flash
  prefs.begin("posture", false);
  prefs.putInt("seatBase", baseSeat);
  prefs.putInt("backBase", baseBack);
  prefs.end();

  Serial.println(" Baselines saved to flash!");
}

// -------------- Load Calibration From Flash ------------------
bool loadCalibration() {
  prefs.begin("posture", true);

  if (!prefs.isKey("seatBase") || !prefs.isKey("backBase")) {
    prefs.end();
    return false;  // no stored values → calibration needed
  }

  baseSeat = prefs.getInt("seatBase");
  baseBack = prefs.getInt("backBase");
  prefs.end();
  return true;
}

// -------------- Reset Calibration via Serial -----------------
void resetCalibration() {
  prefs.begin("posture", false);
  prefs.clear();
  prefs.end();
  Serial.println(" Calibration cleared! Restart ESP and it will recalibrate.");
}

void setup() {
  Serial.begin(115200);
  //pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  while (!Serial) delay(10);

  Serial.println("\n=== Posture System Booting ===");

  // Try loading calibration values
  if (loadCalibration()) {
    Serial.println(" Loaded saved calibration from flash!");
    Serial.print("Seat Baseline = "); Serial.println(baseSeat);
    Serial.print("Back Baseline = "); Serial.println(baseBack);
  } else {
    Serial.println(" No calibration found. Running calibration now...");
    calibrateSensors();
  }

  Serial.println("Type RESETCAL to recalibrate anytime.");
}

void loop() {
  // ---- Check for Serial Command ----
  if (Serial.available()) {
    String cmd = Serial.readStringUntil('\n');
    cmd.trim();
    if (cmd == "RESETCAL") {
      resetCalibration();
    }
  }

  // ---- Normal posture monitoring ----
  int seat = smoothRead(FSR_SEAT);
  int back = smoothRead(FSR_BACK);

  Serial.print("Seat: "); Serial.print(seat);
  Serial.print("  Back: "); Serial.print(back);

  int seatThreshold = baseSeat * 0.20;
  int backThreshold = baseBack * 0.20;

  bool poor = false;

  if (back < baseBack - backThreshold) {
    poor = true; Serial.print("  (Forward Slouch)");
  }
  if (back > baseBack + backThreshold) {
    poor = true; Serial.print("  (Leaning Back)");
  }
  if (seat < baseSeat - seatThreshold) {
    poor = true; Serial.print("  (Seat Shift)");
  }

  if (poor) {
    if (poorPostureStart == 0) poorPostureStart = millis();
    if (millis() - poorPostureStart > window) {
      //digitalWrite(LED_PIN, HIGH);
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.print("  <-- ALERT!");
    }
  } else {
    poorPostureStart = 0;
    //digitalWrite(LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
    Serial.print("  --> Good");
  }

  Serial.println();
  delay(200);
}
