#include <SoftwareSerial.h>

SoftwareSerial DAVID(12, 11); // TX | RX

void setup() {
  Serial.begin(9600);
  Serial.println("Listo");
  DAVID.begin(38400);
}

void loop() {
  if ( DAVID.available())
  Serial.write( DAVID.read());

  if (Serial.available())
   DAVID.write(Serial.read());
}
