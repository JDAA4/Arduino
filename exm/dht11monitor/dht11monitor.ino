#include <LiquidCrystal.h>
#include <DHT.h>

#define DHTPIN 8
#define DHTTYPE DHT11

LiquidCrystal lcd(7, 6, 5, 4, 3, 2);
DHT dht(DHTPIN, DHTTYPE);

const int led = 12;
const int move = 11;

const int addMax = 10;
const int addMin = 9;

int menu = 1;

char brightness = 0;
unsigned long previousMillisLet = 0;
unsigned long btnDebounceMajor = 2000;
unsigned long btnDebounce = 200;
bool buttonsBlocked = false;

int max = 40;
int maxMax = 50;
int min = 20;
int minMax = 30;

float temperature = 0;

int maxHz = 70;
int maxHzMax = 80;
int minHz = 30;
int minHzMax = 40;

float humidity = 0;

byte degreeSymbol[8] = {
  B00110,
  B01001,
  B01001,
  B00110,
  B00000,
  B00000,
  B00000,
  B00000
};

void setup() {
  pinMode(move, OUTPUT);
  pinMode(addMax, OUTPUT);
  pinMode(addMin, OUTPUT);
  pinMode(led, OUTPUT);
  lcd.begin(16, 2);
  delay(50);
  loadCustomCharacter(0, degreeSymbol);
  displayMenu();
  dht.begin();
  delay(50);
  Serial.begin(9600);
}

void loop() {
  humidity = dht.readHumidity();
  temperature = dht.readTemperature();

  if (!isnan(humidity) || !isnan(temperature)) {
    Serial.println(String(temperature) + "/" + String(humidity));
  }

  if (Serial.available() > 0) {
    brightness = Serial.read();
  }

  switch (brightness)
  {
  case '0':
    analogWrite(led, 0);
    break;
  case '1':
    analogWrite(led, 20);
    break;
  case '2':
    analogWrite(led, 40);
    break;
  case '3':
    analogWrite(led, 60);
    break;
  case '4':
    analogWrite(led, 80);
    break;
  case '5':
    analogWrite(led, 100);
    break;
  case '6':
    analogWrite(led, 120);
    break;
  case '7':
    analogWrite(led, 140);
    break;
  case '8':
    analogWrite(led, 160);
    break;
  case '9':
    analogWrite(led, 180);
    break;
  default:
    break;
  }

  delay(1000);
  
  displayMenu();
}

bool btnPushed() {
  if (digitalRead(move) == HIGH) {
    moveMenu();
    displayMenu();
    delay(btnDebounceMajor);
    return true;
  } else if (digitalRead(addMax) == HIGH) {
    if (menu == 2) {
      addMaxValue();
      displayMenu();
      delay(btnDebounce);
      return false;
    } else if (menu == 3) {
      addMaxHzValue();
      displayMenu();
      delay(btnDebounce);
      return false;
    }
  } else if (digitalRead(addMin) == HIGH) {
    if (menu == 2) {
      addMinValue();
      displayMenu();
      delay(btnDebounce);
      return false;
    } else if (menu == 3) {
      addMinHzValue();
      displayMenu();
      delay(btnDebounce);
      return false;
    }
  }

  return false;
}

void moveMenu() {
  menu++;
  if (menu > 3) {
    menu = 1;
  }
}

void addMaxValue() {
  max++;
  if (max > maxMax) {
    max = 30;
  }
}

void addMaxHzValue() {
  maxHz++;
  if (maxHz > maxHzMax) {
    maxHz = 80;
  }
}

void addMinValue() {
  min++;
  if (min > minMax) {
    min = 10;
  }
}

void addMinHzValue() {
  minHz++;
  if (minHz > minHzMax) {
    minHz = 20;
  }
}

void loadCustomCharacter(uint8_t charIndex, const uint8_t charData[]) {
  uint8_t data;
  lcd.createChar(charIndex, charData);
}

void printLCD(String text,int col = 0, int row = 0) {
  lcd.setCursor(col, row);
  lcd.print(text);
}

void writeCustomCharacter(int charIndex, int col, int row) {
  lcd.setCursor(col, row);
  lcd.write(byte(charIndex));
}

void displayMenu() {
  lcd.clear();
  switch (menu) {
    case 1:
      writeCustomCharacter(0, 0, 0);
      printLCD("C: " + String(temperature), 1, 0);
      lcd.write(byte(0));
      lcd.print(" " + String(brightness));
      printLCD("Hz: " + String(humidity) + "%", 0, 1);
      break;
    case 2:
      printLCD("Temperature", 0, 0);
      printLCD("Min:" + String(min), 0, 1);
      lcd.write(byte(0));
      lcd.print(" Max:" + String(max));
      lcd.write(byte(0));
      break;
    case 3:
      printLCD("Humidity", 0, 0);
      printLCD("Min:" + String(minHz) + "% Max:" + String(maxHz) + "%", 0, 1);
      break;
  }
}
