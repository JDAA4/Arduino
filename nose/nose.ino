#include <DHT.h>
#include <LiquidCrystal.h>

// Definir los pines de conexión del DHT11
#define DHTPIN 13    // Pin digital conectado al DHT11
#define DHTTYPE DHT11   // DHT 11

DHT dht(DHTPIN, DHTTYPE);

// Inicializar la librería de LCD con los números de los pines de interfaz
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Definir pines de los pulsadores
#define MENU_BUTTON 6
#define INC_TEMP_BUTTON 7
#define DEC_TEMP_BUTTON 8
#define INC_HUM_BUTTON 9
#define DEC_HUM_BUTTON 10

// Definir estados del menú
enum MenuState {
  SHOW_TEMP_HUM,
  SET_LIMITS
};

MenuState menuState = SHOW_TEMP_HUM;

// Definir límites de temperatura y humedad
float tempLimit = 30.0;
float humLimit = 50.0;

// Variables para gestionar el estado de los pulsadores
int lastMenuButtonState = HIGH;
int lastIncTempButtonState = HIGH;
int lastDecTempButtonState = HIGH;
int lastIncHumButtonState = HIGH;
int lastDecHumButtonState = HIGH;

void setup() {
  // Iniciar la comunicación serie
  Serial.begin(9600);
  
  // Iniciar el sensor DHT
  dht.begin();
  
  // Iniciar el LCD
  lcd.begin(16, 2);
  
  // Configurar pines de los pulsadores como entradas con pull-up
  pinMode(MENU_BUTTON, INPUT_PULLUP);
  pinMode(INC_TEMP_BUTTON, INPUT_PULLUP);
  pinMode(DEC_TEMP_BUTTON, INPUT_PULLUP);
  pinMode(INC_HUM_BUTTON, INPUT_PULLUP);
  pinMode(DEC_HUM_BUTTON, INPUT_PULLUP);
  
  // Imprimir un mensaje de inicio en el LCD
  lcd.print("Inicializando...");
  delay(2000); // Esperar 2 segundos para ver el mensaje
  
  // Limpiar el LCD y preparar para los datos
  lcd.clear();
}

void loop() {
  // Leer el estado de los pulsadores
  int menuButtonState = digitalRead(MENU_BUTTON);
  int incTempButtonState = digitalRead(INC_TEMP_BUTTON);
  int decTempButtonState = digitalRead(DEC_TEMP_BUTTON);
  int incHumButtonState = digitalRead(INC_HUM_BUTTON);
  int decHumButtonState = digitalRead(DEC_HUM_BUTTON);
  
  // Gestionar el cambio de estado del menú
  if (menuButtonState == LOW && lastMenuButtonState == HIGH) {
    if (menuState == SHOW_TEMP_HUM) {
      menuState = SET_LIMITS;
    } else {
      menuState = SHOW_TEMP_HUM;
    }
    delay(250); // Delay para evitar rebotes en el botón de menú
  }
  lastMenuButtonState = menuButtonState;
  
  // Dependiendo del estado del menú, realizar diferentes acciones
  if (menuState == SHOW_TEMP_HUM) {
    showTempHum();
  } else if (menuState == SET_LIMITS) {
    setLimits(incTempButtonState, decTempButtonState, incHumButtonState, decHumButtonState);
  }
  
  // Guardar el estado de los pulsadores para detectar cambios
  lastIncTempButtonState = incTempButtonState;
  lastDecTempButtonState = decTempButtonState;
  lastIncHumButtonState = incHumButtonState;
  lastDecHumButtonState = decHumButtonState;
  
  // Esperar unos milisegundos para evitar rebotes
  delay(50);
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

  // Ajustar la temperatura si excede el límite
  if (t > tempLimit) {
    t = tempLimit;
  }

  // Ajustar la humedad si excede el límite
  if (h > humLimit) {
    h = humLimit;
  }

  // Imprimir los valores en el LCD
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(t);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Hum: ");
  lcd.print(h);
  lcd.print(" %");

 Serial.print("Humedad: ");
  Serial.print(dht.readHumidity()); // Mostrar la humedad real
  Serial.print(" %\t");
  Serial.print("Temperatura: ");
  Serial.print(dht.readTemperature()); // Mostrar la temperatura real
  Serial.println(" *C");
}


void setLimits(int incTempButtonState, int decTempButtonState, int incHumButtonState, int decHumButtonState) {
  // Gestionar el incremento y decremento del límite de temperatura
  if (incTempButtonState == LOW && lastIncTempButtonState == HIGH) {
    tempLimit += 0.1;
    delay(250); // Delay para evitar rebotes al incrementar temperatura
  }
  if (decTempButtonState == LOW && lastDecTempButtonState == HIGH) {
    tempLimit -= 0.1;
    delay(250); // Delay para evitar rebotes al decrementar temperatura
  }

  // Gestionar el incremento y decremento del límite de humedad
  if (incHumButtonState == LOW && lastIncHumButtonState == HIGH) {
    humLimit += 0.1;
    delay(250); // Delay para evitar rebotes al incrementar humedad
  }
  if (decHumButtonState == LOW && lastDecHumButtonState == HIGH) {
    humLimit -= 0.1;
    delay(250); // Delay para evitar rebotes al decrementar humedad
  }

  // Imprimir los límites en el LCD
  lcd.clear();
  lcd.print("Temp Lim: ");
  lcd.print(tempLimit, 1);
  lcd.setCursor(0, 1);
  lcd.print("Hum Lim: ");
  lcd.print(humLimit, 1);
}