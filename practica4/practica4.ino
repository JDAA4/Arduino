#include <LiquidCrystal.h>
#include <DHT.h>
#define DHTPIN 9
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);
const int led = 8;
const int tempSensor;
void setup() {
lcd.begin(16, 2);
Serial.begin(9600);
pinMode(led, OUTPUT);
dht.begin();
}
void loop() {
lcd.clear();
String texto = leerTexto();
if (texto.length() > 0) {
imprimirTextoAjustado(texto);
digitalWrite(led, HIGH);
delay(5000);
} else {
digitalWrite(led, LOW);
}
if (Serial.available() > 0) {
char comando = Serial.read();
if (comando == 'T') {
float temp = dht.readTemperature();
if (isnan(temp)) {
Serial.println("Error al leer la temperatura");
} else {
String tempStr = String(temp, 2);
Serial.println(tempStr);
}
}
}
}
String leerTexto() {
String texto = "";
if (Serial.available()) {
texto = Serial.readStringUntil('\n');
}
return texto;
}
void imprimirTextoAjustado(String texto) {
int linea = 0;
int posicion = 0;
while (posicion < texto.length()) {
lcd.setCursor(0, linea);
for (int i = 0; i < 16 && posicion < texto.length(); i++,
posicion++) {
lcd.print(texto[posicion]);
}
linea++;
}
}







