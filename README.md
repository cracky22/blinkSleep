# Arduino Pro Micro – LED-Timer mit Energiesparmodus

Dieses Projekt steuert eine LED auf einem **Arduino Pro Micro**.  
Die LED wird per Taster aktiviert, leuchtet für 20 Sekunden und schaltet sich dann wieder aus.  
Zwischen den Aktivierungen versetzt sich der Mikrocontroller in den **Tiefschlafmodus**, um Energie zu sparen.

## Funktionsweise

1. **Taster drücken**  
   - Der Taster ist zwischen Pin **3** und **GND** angeschlossen.  
   - Durch den internen Pull-Up ist der Pin im Ruhezustand HIGH und bei Tastendruck LOW.

2. **LED einschalten**  
   - Pin **17** steuert die Onboard-LED des Pro Micro.  
   - Beim Drücken leuchtet die LED für 20 Sekunden.

3. **LED ausschalten und Tiefschlaf**  
   - Nach Ablauf der Zeit wird die LED ausgeschaltet.  
   - Der Controller schaltet alle unnötigen Peripherien ab und geht in den **SLEEP_MODE_PWR_DOWN**.

4. **Aufwachen per Interrupt**  
   - Ein Tastendruck löst einen Interrupt aus, der den Controller aufweckt.  
   - Danach läuft der Zyklus erneut.

## Pinbelegung

| Pin  | Funktion                  |
|------|---------------------------|
| 17   | LED-Ausgang (Onboard)     |
| 3    | Tastereingang (mit Pull-Up) |

## Codeübersicht

- **`setup()`** – Initialisiert LED- und Button-Pin.  
- **`loop()`** – Prüft Tasterstatus, steuert LED-Timer, ruft Sleep-Funktion auf.  
- **`enterSleepMode()`** – Versetzt den Controller in Tiefschlaf, deaktiviert Peripherien, setzt Interrupt.  
- **`wakeUp()`** – Leere Interrupt-Routine, dient nur zum Aufwecken.  

## Abhängigkeiten

- Arduino AVR Core (für `avr/sleep.h` und `avr/power.h`)
- Board: **Arduino Pro Micro (ATmega32U4)**

## Hinweise

- Der Tiefschlaf spart deutlich Energie, ideal für Batteriebetrieb.  
- Beim Testen am USB-Port kann der Sleep-Modus zu ungewöhnlichem Verhalten in der seriellen Konsole führen, da der Chip komplett abschaltet.  
- Der Interrupt ist auf **LOW** eingestellt – der Taster muss daher nach dem Wecken losgelassen werden, bevor ein neuer Zyklus starten kann.

## Lizenz

Dieses Projekt ist frei nutzbar unter der MIT-Lizenz.
