#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2); // Pines del LCD

const byte botonSeleccion = 6; // Pin del botón de selección
const byte botonMenu = 7; // Pin del botón de navegación

byte seleccionAnterior = LOW, seleccionActual = LOW;
byte menuAnterior = LOW, menuActual = LOW;

byte opcionMenuActual = 1; // Opción del menú actual (1, 2 o 3)

byte ledRojo = A5, ledVerde = A2, ledAmarillo = A4; // Pines de los LEDs

const unsigned long tiempoEjecucion = 5000; // Tiempo de ejecución en milisegundos (5 segundos)
unsigned long tiempoInicial = 0; // Almacena el tiempo de inicio

void setup() {
  lcd.begin(16, 2); // Inicializar el LCD: 16 columnas, 2 filas

  // Configurar pines de entrada y salida
  pinMode(botonSeleccion, INPUT_PULLUP);
  pinMode(botonMenu, INPUT_PULLUP);
  pinMode(ledRojo, OUTPUT);
  pinMode(ledVerde, OUTPUT);
  pinMode(ledAmarillo, OUTPUT);

  // Mostrar el menú inicial
  mostrarMenu();
}

void loop() {
  seleccionActual = digitalRead(botonSeleccion);
  menuActual = digitalRead(botonMenu);

  // Detectar pulsación del botón de selección
  if (seleccionActual == LOW && seleccionAnterior == HIGH) {
    ejecutarOpcion();
    tiempoInicial = millis(); // Guardar el tiempo de inicio
  }

  // Detectar pulsación del botón de navegación
  if (menuActual == LOW && menuAnterior == HIGH) {
    delay(100);
    navegarMenu();
  }

  // Reiniciar el menú después del tiempo de ejecución
  if (tiempoInicial != 0 && millis() - tiempoInicial >= tiempoEjecucion) {
    reiniciarMenu();
    tiempoInicial = 0; // Reiniciar el tiempo de inicio
  }

  seleccionAnterior = seleccionActual;
  menuAnterior = menuActual;
}

void mostrarMenu() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (opcionMenuActual) {
    case 1:
      lcd.print("1. Inicializar");
      break;
    case 2:
      lcd.print("2. Calibrar");
      break;
    case 3:
      lcd.print("3. Medir");
      break;
  }
  lcd.setCursor(0, 1);
  lcd.print("Seleccione>>>");
}

void ejecutarOpcion() {
  lcd.clear();
  lcd.setCursor(0, 0);
  switch (opcionMenuActual) {
    case 1:
      lcd.print("Iniciando...");
      digitalWrite(ledVerde, HIGH);
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledAmarillo, LOW);
      break;
    case 2:
      lcd.print("Calibrando...");
      digitalWrite(ledAmarillo, HIGH);
      digitalWrite(ledRojo, LOW);
      digitalWrite(ledVerde, LOW);
      break;
    case 3:
      lcd.print("Midiendo...");
      digitalWrite(ledRojo, HIGH);
      digitalWrite(ledVerde, LOW);
      digitalWrite(ledAmarillo, LOW);
      break;
  }
}

void navegarMenu() {
  opcionMenuActual++;
  if (opcionMenuActual > 3) {
    opcionMenuActual = 1;
  }
  mostrarMenu();
}

void reiniciarMenu() {
  digitalWrite(ledRojo, LOW);
  digitalWrite(ledVerde, LOW);
  digitalWrite(ledAmarillo, LOW);
  mostrarMenu();
}
