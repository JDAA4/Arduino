#include <DHT.h>
#include <LiquidCrystal.h>
#include <Wire.h>

// Definiciones para el sensor DHT11
#define DHTPIN 2  // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11

// Definiciones para los pulsadores
#define BUTTON1_PIN 3  // Pin del primer pulsador
#define BUTTON2_PIN 4  // Pin del segundo pulsador

// Variables globales
DHT dht(DHTPIN, DHTTYPE);
int tempMax = 25;
int tempMin = 18;
int humMax = 70;
int humMin = 40;
int pwmPin = 9;
int menuOption = 0;
float temperature;
float humidity;
bool button1Pressed = false;
bool button2Pressed = false;

// Objeto para controlar el LCD
// Objeto para controlar el LCD
LiquidCrystal lcd(12, 11, 7, 6, 5, 8);  // (RS, E, D4, D5, D6, D7)


void setup() {
  // Inicialización
  lcd.begin(16, 2);  // Inicializa el LCD con 16 columnas y 2 filas
  dht.begin();
  Serial.begin(9600);

  // Configuración del pin PWM
  pinMode(pwmPin, OUTPUT);

  // Configuración de los pulsadores
  pinMode(BUTTON1_PIN, INPUT_PULLUP);
  pinMode(BUTTON2_PIN, INPUT_PULLUP);

  lcdMenu();
}

void loop() {
  // Leer los estados de los pulsadores
  button1Pressed = !digitalRead(BUTTON1_PIN);
  button2Pressed = !digitalRead(BUTTON2_PIN);

  // Navegación del menú
  if (button1Pressed) {
    menuOption = (menuOption + 1) % 3;
    lcdMenu();
    delay(300);  // Para evitar múltiples lecturas por el rebote del pulsador
  }

  // Selección de opciones del menú
  switch (menuOption) {
    case 0:
      readSensors();
      displayTempHum();
      break;
    case 1:
      if (button2Pressed) {
        setLimits();
        delay(300);  // Para evitar múltiples lecturas por el rebote del pulsador
      }
      break;
    case 2:
      readSensors();
      controlRefrigeration();
      break;
  }
  delay(1000);
}

void lcdMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("1.Temp & Hum");
  lcd.setCursor(0, 1);
  lcd.print("2.Set Limits");
  lcd.setCursor(0, 1);
  lcd.print("3.Control");
}

void readSensors() {
  // Lectura del sensor DHT11
  temperature = dht.readTemperature();
  humidity = dht.readHumidity();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.print(" C, Humidity: ");
  Serial.print(humidity);
  Serial.println(" %");
}

void displayTempHum() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(humidity);
  lcd.print(" %");
}

void setLimits() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Temp Limits:");
  lcd.setCursor(0, 1);
  lcd.print("Max: ");
  lcd.print(tempMax);
  lcd.print(" Min: ");
  lcd.print(tempMin);
  delay(2000);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Set Hum Limits:");
  lcd.setCursor(0, 1);
  lcd.print("Max: ");
  lcd.print(humMax);
  lcd.print(" Min: ");
  lcd.print(humMin);
  delay(2000);
}

void controlRefrigeration() {
  int pwmValue = map(temperature, tempMin, tempMax, 0, 255);
  pwmValue = constrain(pwmValue, 0, 255);
  analogWrite(pwmPin, pwmValue);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Cooling PWM: ");
  lcd.print(pwmValue);
}
