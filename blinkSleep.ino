#include <avr/sleep.h>
#include <avr/power.h>

const int ledPin = 17; // Pin 17 ist mit der Onboard-LED des Pro Micro verbunden
const int buttonPin = 3; // Der Taster ist an Pin 3 und Ground angeschlossen

void setup() {
  pinMode(ledPin, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP); // Internen Pull-Up-Widerstand aktivieren
}

void loop() {
  // Prüfen, ob der Button gedrückt ist (LOW, weil INPUT_PULLUP aktiviert ist)
  if (digitalRead(buttonPin) == LOW) {
    // LED einschalten
    digitalWrite(ledPin, HIGH);
    
    // 20 Sekunden warten
    delay(20000);
    
    // LED ausschalten
    digitalWrite(ledPin, LOW);
  }

  // In den Tiefschlaf gehen, um Strom zu sparen
  enterSleepMode();
}

void enterSleepMode() {
  // Vorbereitung für den Tiefschlaf
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();
  
  // Alle unnötigen Peripherien deaktivieren
  power_all_disable();
  
  // Interrupt aufwecken bei Tastendruck (Pin Change Interrupt)
  attachInterrupt(digitalPinToInterrupt(buttonPin), wakeUp, LOW);

  // Den Tiefschlafmodus aktivieren
  sleep_cpu();
  
  // Wenn der Arduino hierher zurückkehrt, wurde er geweckt
  sleep_disable();
  
  // Peripherien wieder aktivieren
  power_all_enable();
  
  // Interrupt deaktivieren, da er nach dem Aufwachen nicht mehr benötigt wird
  detachInterrupt(digitalPinToInterrupt(buttonPin));
}

// Diese Funktion wird aufgerufen, wenn der Arduino durch den Interrupt geweckt wird
void wakeUp() {
  // Hier ist kein Code notwendig, die Funktion dient nur als Weckruf
}