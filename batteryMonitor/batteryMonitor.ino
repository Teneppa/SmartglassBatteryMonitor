int value = 0;
float voltage;

// The voltage divider resistor values are here [R1 -> +BAT] [R2 -> GND]
float R1 = 5100.0;
float R2 = 10000.0;

long oldCheck = 0;

// Get the voltage
void readVoltage() {
  value = analogRead(A0);
  voltage = value * (3.3 / 1024) * ((R1 + R2) / R2);
}

void setup() {
  pinMode(3, OUTPUT);
  Serial.begin(115200);

  // Update the voltage on startup, not really needed
  // but yea I just wanted to do it so...
  readVoltage();
}

void loop() {
  // Read the serial port
  if (Serial.available() > 0) {
    String msg = Serial.readStringUntil(';');

    // If the message was "v," send the voltage to the Pi
    if (msg == "v") {
      readVoltage();
      Serial.print(String(voltage)+"\n");
    }
  }

  // Update the voltage even if there's no queries on the serial port
  if(millis() - oldCheck > 4000) {
    readVoltage();

    // If the voltage is under 3.6, shine some light
    if (voltage < 3.6) {
      digitalWrite(3, 1);
    }else{
      digitalWrite(3, 0);
    }

    oldCheck = millis();
  }
}
