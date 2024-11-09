#include <DHT.h>
#include <LiquidCrystal.h>

// Definir los pines de conexión del DHT11 y el LED
#define DHTPIN 13    // Pin digital conectado al DHT11
#define DHTTYPE DHT11   // DHT 11
#define LEDPIN 10     // Pin PWM conectado al LED

DHT dht(DHTPIN, DHTTYPE);

// Inicializar la librería de LCD con los números de los pines de interfaz
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Definir límites de temperatura y humedad
float tempLimitMax = 30.0;
float humLimitMax = 50.0;
float tempLimitMin = 20.0;
float humLimitMin = 20.0;

void setup() {
  // Iniciar la comunicación serie
  Serial.begin(9600);
  
  // Iniciar el sensor DHT
  dht.begin();
  
  // Iniciar el LCD
  lcd.begin(16, 2);
  
  // Configurar el pin del LED como salida
  pinMode(LEDPIN, OUTPUT);
  
  // Imprimir un mensaje de inicio en el LCD
  lcd.print("Inicializando...");
  delay(2000); // Esperar 2 segundos para ver el mensaje
  
  // Limpiar el LCD y preparar para los datos
  lcd.clear();
}

void loop() {
  showTempHum();
  
  // Esperar unos milisegundos para evitar rebotes
  delay(2000);
}

void showTempHum() {
  // Leer la humedad relativa (humedad en porcentaje)
  float h = dht.readHumidity();
  
  // Leer la temperatura en grados Celsius
  float t = dht.readTemperature();

  // Comprobar si las lecturas han fallado
  if (isnan(h) || isnan(t)) {
    Serial.println("Error al leer del sensor DHT");
    lcd.clear();
    lcd.print("Error DHT");
    return;
  }
  
  // Controlar el LED basado en los límites
  int ledBrightness;
  if (t > tempLimitMax || h > humLimitMax) {
    ledBrightness = 255;  // Máxima intensidad
  } else if (t < tempLimitMin || h < humLimitMin) {
    ledBrightness = 0;    // Apagar el LED
  } else {
    ledBrightness = 10;   // Intensidad media
  }
  analogWrite(LEDPIN, ledBrightness);
  
  // Enviar los valores en el formato "Temp:xx.xx/Hum:xx.xx"
  Serial.print("Temp:");
  Serial.print(t);
  Serial.print("/Hum:");
  Serial.println(h);
  
  // Imprimir los valores en el LCD
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print(" %");
}


