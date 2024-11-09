const int potPin = A0; // Pin analógico para el potenciómetro
const int buttonPin = 2; // Pin digital para el botón pulsador
const int ledPin = 3; // Pin digital para el LED

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); // Configurar el pin del botón como entrada con pull-up interno
  pinMode(ledPin, OUTPUT); // Configurar el pin del LED como salida
  Serial.begin(9600); // Inicializar comunicación serial
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == '1') {
      digitalWrite(ledPin, HIGH); // Encender el LED
    } else if (command == '0') {
      digitalWrite(ledPin, LOW); // Apagar el LED
    }
  }

  int potValue = analogRead(potPin); // Leer el valor del potenciómetro
  int buttonState = digitalRead(buttonPin); // Leer el estado del botón

  // Enviar los datos al puerto serial
  Serial.print("POT:");
  Serial.print(potValue);
  Serial.print(", BUTTON:");
  Serial.println(buttonState);

  delay(100); // Esperar 100 ms
}
