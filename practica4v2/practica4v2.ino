const int potPin = A0; 
const int buttonPin = 2; 
const int ledPin = 3; 

void setup() {
  pinMode(buttonPin, INPUT_PULLUP); 
  pinMode(ledPin, OUTPUT); 
  Serial.begin(9600); 
}

void loop() {
  if (Serial.available()) {
    char command = Serial.read();
    if (command == '1') {
      digitalWrite(ledPin, HIGH); 
    } else if (command == '0') {
      digitalWrite(ledPin, LOW); 
    }
  }

  int potValue = analogRead(potPin); 
  int buttonState = digitalRead(buttonPin); 

  Serial.print("POT:");
  Serial.print(potValue);
  Serial.print(", BUTTON:");
  Serial.println(buttonState);

  delay(100); 
}