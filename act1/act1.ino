#include <SevSeg.h>

SevSeg sevseg;

void setup() {
  // Configurar pines para el display de 7 segmentos
  byte Numdigits = 4;
  byte Comunes[] = {2, 3, 5, 4};
  byte Segmentos[] = {6, 7, 8, 9, 10, 11, 12};
  byte Tipo = COMMON_ANODE;
  sevseg.begin(Tipo, Numdigits, Comunes, Segmentos);
}

void loop() {
  static unsigned long tiempoejec = millis() + 100;
  static int contador = 0;

  if (millis() >= tiempoejec) {
    tiempoejec += 100;
    contador++;
    if (contador == 1999) {
      contador = 0;
    }
    sevseg.setNumber(contador, 3);
  }
  sevseg.refreshDisplay();
}











