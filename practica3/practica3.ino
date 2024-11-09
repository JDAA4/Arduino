int valorPot = 0;
int led = 9;
int poten = A0;
int offTime = 0;
int onTime = 0;
int timeAll = 10;

void setup() {
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  valorPot = analogRead(poten);
  onTime = (valorPot * timeAll)/1023;
  offTime = timeAll - onTime;
  digitalWrite(led, HIGH);
  delay(onTime);
  digitalWrite(led, LOW);
  delay(offTime);
  Serial.println(valorPot);
}

