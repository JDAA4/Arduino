#include <DHT.h>
#include <SevSeg.h>  // Incluimos la biblioteca para el display de 7 segmentos

#define DHTPIN 2     // Pin digital al que está conectado el sensor DHT11
#define DHTTYPE DHT11  // Tipo de sensor DHT (DHT11 en este caso)

#define ACCESS_CODE 1234  // Código de acceso permitido
#define MAX_TEMP 30  // Temperatura máxima permitida en grados Celsius

DHT dht(DHTPIN, DHTTYPE);
SevSeg sevseg;  // Creamos un objeto SevSeg para controlar el display de 7 segmentos

int greenLedPin = 3;  // Pin del LED verde
int redLedPin = 4;    // Pin del LED rojo

// Pines para los botones de entrada del código
int buttonPins[] = {5, 6, 7, 8};
int buttonState[] = {LOW, LOW, LOW, LOW};
int correctCode[] = {1, 2, 3, 4};  // Código de acceso correcto

void setup() {
  Serial.begin(9600);  // Inicializar comunicación serial
  pinMode(greenLedPin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  
  // Configurar pines de los botones como entradas
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  byte numDigits = 4;  // 4 dígitos en el display de 7 segmentos
  byte digitPins[] = {9, 10, 11, 12};  // Pines para los dígitos (comunes)
  byte segmentPins[] = {A0, A1, A2, A3, A4, A5, 13, A6};  // Pines para los segmentos

  sevseg.begin(COMMON_ANODE, numDigits, digitPins, segmentPins); // COMMON_ANODE para display común ánodo
  sevseg.setBrightness(90);  // Configuramos el brillo del display
}

void loop() {
  float temperature = dht.readTemperature();  // Leer temperatura
  int humidity = dht.readHumidity();          // Leer humedad

  Serial.print("Temperatura: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Verificar si se cumple la condición de acceso
  if (temperature <= MAX_TEMP) {
    Serial.println(" - Acceso permitido");
    // Verificar el código ingresado
    if (checkCode()) {
      // Acceso permitido
      digitalWrite(greenLedPin, HIGH);  // Encender LED verde
      delay(5000);  // Mantener el LED encendido durante 5 segundos
      digitalWrite(greenLedPin, LOW);   // Apagar LED verde
    } else {
      // Código incorrecto
      Serial.println("Código incorrecto");
      digitalWrite(redLedPin, HIGH);  // Encender LED rojo
      displayTemperature(temperature);  // Mostrar la temperatura en el display de 7 segmentos
      delay(1000);  // Mantener el LED encendido durante 1 segundo
      digitalWrite(redLedPin, LOW);   // Apagar LED rojo
    }
  } else {
    // Temperatura excede el límite
    Serial.println(" - Temperatura demasiado alta. Acceso denegado");
    digitalWrite(redLedPin, HIGH);  // Encender LED rojo
    displayTemperature(temperature);  // Mostrar la temperatura en el display de 7 segmentos
    delay(1000);  // Mantener el LED encendido durante 1 segundo
    digitalWrite(redLedPin, LOW);   // Apagar LED rojo
  }

  delay(5000);  // Esperar 5 segundos antes de volver a verificar la temperatura
}

bool checkCode() {
  for (int i = 0; i < 4; i++) {
    buttonState[i] = digitalRead(buttonPins[i]);
    if (buttonState[i] != correctCode[i]) {
      return false;
    }
  }
  return true;
}

void displayTemperature(float temperature) {
  // Mostrar la temperatura en el formato "XX°C" en el display de 7 segmentos
  int temperatureInt = (int)temperature;  // Convertir la temperatura a entero
  sevseg.setNumber(temperatureInt);  // Mostrar la parte entera de la temperatura en el display
}
