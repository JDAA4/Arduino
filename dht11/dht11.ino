#include <DHT.h>

#define DHTPIN 2  // Pin de datos del sensor DHT11
#define BUTTONPIN 3  // Pin del botón para cambiar entre temperatura y humedad
#define DISPLAY_PIN_A 4
#define DISPLAY_PIN_B 5
#define DISPLAY_PIN_C 6
#define DISPLAY_PIN_D 7
#define DISPLAY_PIN_E 8
#define DISPLAY_PIN_F 9
#define DISPLAY_PIN_G 10
#define DISPLAY_PIN_DP 11
#define DIGIT_1 12
#define DIGIT_2 13
#define DIGIT_3 A0
#define DIGIT_4 A1

DHT dht(DHTPIN, DHT11);

bool showTemperature = true;

void setup() {
  pinMode(BUTTONPIN, INPUT_PULLUP);

  pinMode(DISPLAY_PIN_A, OUTPUT);
  pinMode(DISPLAY_PIN_B, OUTPUT);
  pinMode(DISPLAY_PIN_C, OUTPUT);
  pinMode(DISPLAY_PIN_D, OUTPUT);
  pinMode(DISPLAY_PIN_E, OUTPUT);
  pinMode(DISPLAY_PIN_F, OUTPUT);
  pinMode(DISPLAY_PIN_G, OUTPUT);
  pinMode(DISPLAY_PIN_DP, OUTPUT);
  pinMode(DIGIT_1, OUTPUT);
  pinMode(DIGIT_2, OUTPUT);
  pinMode(DIGIT_3, OUTPUT);
  pinMode(DIGIT_4, OUTPUT);

  digitalWrite(DIGIT_1, HIGH);
  digitalWrite(DIGIT_2, HIGH);
  digitalWrite(DIGIT_3, HIGH);
  digitalWrite(DIGIT_4, HIGH);
}

void loop() {
  float temperature, humidity;

  if (showTemperature) {
    temperature = dht.readTemperature();  // Obtener temperatura del DHT11
    displayTemperature(int(temperature));
  } else {
    humidity = dht.readHumidity();  // Obtener humedad del DHT11
    displayHumidity(int(humidity));
  }

  // Cambiar entre temperatura y humedad al presionar el botón
  if (digitalRead(BUTTONPIN) == LOW) {
    showTemperature = !showTemperature;
    delay(500); // Debouncing
  }
}

void displayTemperature(int temp) {
  int digit1 = temp / 10;
  int digit2 = temp % 10;

  displayNumber(digit1, DIGIT_1);
  displayNumber(digit2, DIGIT_2);

  digitalWrite(DIGIT_3, HIGH);
  digitalWrite(DIGIT_4, HIGH);
}

void displayHumidity(int hum) {
  int digit1 = hum / 10;
  int digit2 = hum % 10;

  displayNumber(digit1, DIGIT_3);
  displayNumber(digit2, DIGIT_4);

  digitalWrite(DIGIT_1, HIGH);
  digitalWrite(DIGIT_2, HIGH);
}

void displayNumber(int number, int digitPin) {
   // Definir los segmentos para cada dígito
  int segments[] = {DISPLAY_PIN_A, DISPLAY_PIN_B, DISPLAY_PIN_C, DISPLAY_PIN_D, DISPLAY_PIN_E, DISPLAY_PIN_F, DISPLAY_PIN_G, DISPLAY_PIN_DP};

  // Definir los patrones para cada número (0-9)
  int digitPatterns[10][7] = {
    {1, 1, 1, 1, 1, 1, 0},  // 0
    {0, 1, 1, 0, 0, 0, 0},  // 1
    {1, 1, 0, 1, 1, 0, 1},  // 2
    {1, 1, 1, 1, 0, 0, 1},  // 3
    {0, 1, 1, 0, 0, 1, 1},  // 4
    {1, 0, 1, 1, 0, 1, 1},  // 5
    {1, 0, 1, 1, 1, 1, 1},  // 6
    {1, 1, 1, 0, 0, 0, 0},  // 7
    {1, 1, 1, 1, 1, 1, 1},  // 8
    {1, 1, 1, 1, 0, 1, 1}   // 9
  };

  // Apagar todos los segmentos
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], LOW);
  }

  // Obtener el patrón para el número actual
  int *pattern = digitPatterns[number];

  // Encender los segmentos correspondientes
  for (int i = 0; i < 7; i++) {
    digitalWrite(segments[i], pattern[i]);
  }

  // Encender el dígito actual
  digitalWrite(digitPin, LOW);

  // Esperar un breve periodo para la visualización
  delay(5);

  // Apagar el dígito actual
  digitalWrite(digitPin, HIGH);
}

