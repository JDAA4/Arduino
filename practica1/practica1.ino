#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); 

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
  lcd.begin(16, 2);
  lcd.createChar(0, specialChar);
  lcd.setCursor(0, 0);
  lcd.write((byte)0);
  lcd.setCursor(2, 0);
  lcd.print("Hola, mundo"); 
}

void loop() {
  for (int i = 0; i < 18; i++) { 
    lcd.scrollDisplayLeft(); 
    delay(500); 
  }
  delay(10); 
}