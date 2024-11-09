#include <LiquidCrystal.h>

LiquidCrystal lcd(2, 3, 4, 5, 6, 7); // Pines del LCD

byte specialChar[8] = {
  B00000,
  B10001,
  B10001,
  B00100,
  B10001,
  B01110,
  B00000,
  B00000
};

void setup() {
  lcd.begin(16, 2); // Inicializar el LCD: 16 columnas, 2 fila
  // Cargar el patrón del carácter especial en la memoria del LCD
  lcd.createChar(0, specialChar);
  // Escribir el carácter especial en el LCD
  lcd.setCursor(0, 0);
  lcd.write((byte)0);
  lcd.setCursor(2, 0);
  lcd.print("Hola, mundo"); // Mensaje inicial
}

void loop() {
  for (int i = 0; i < 24; i++) { // Recorrer 24 posiciones (16+8=24)
    lcd.scrollDisplayLeft(); // Desplazar el contenido del LCD una posición a la izquierda
    delay(500); // Esperar 500 milisegundos antes de desplazar el siguiente carácter
  }
  delay(100); // Esperar 2 segundos antes de reiniciar el desplazamiento
}