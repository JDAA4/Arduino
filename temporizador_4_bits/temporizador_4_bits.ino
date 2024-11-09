
const int ledPins[] = {6, 8, 10, 12};
const int numLEDs = 4;

unsigned long previousMillis = 0;
const long interval = 1000;  

int timerState = 0;

void setup() {
  // Configurar pines de salida para LEDs
  for (int i = 0; i < numLEDs; i++) {
    pinMode(ledPins[i], OUTPUT);
  }
}

void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillis >= interval) {
    // Guardar el tiempo actual
    previousMillis = currentMillis;

    timerState = (timerState + 1) % (1 << numLEDs);

    showBinaryState(timerState);
  }
}

void showBinaryState(int state) {
  for (int i = 0; i < numLEDs; i++) {
    digitalWrite(ledPins[i], (state & (1 << i)) ? HIGH : LOW);
  }
}