# Prosty odczyt zdarzeń `EV_KEY` z evdev (Linux)

> **Cel (edukacyjny):** pokazanie jak działa interfejs **evdev** w Linuksie i jak wygląda odczyt struktury `struct input_event` z `/dev/input/eventX`.  
> **Uwaga:** uruchamiaj tylko na **własnym sprzęcie / w swoim środowisku** i zgodnie z regulaminem zajęć oraz prawem. Dostęp do `/dev/input/event*` zwykle wymaga uprawnień (np. root lub odpowiedniej grupy).

---

## Opis działania

Program przyjmuje jako argument ścieżkę do urządzenia evdev (np. `/dev/input/event5`). Następnie:

1. Otwiera wskazany plik urządzenia w trybie tylko do odczytu (`O_RDONLY`).
2. W pętli nieskończonej odczytuje binarne rekordy `struct input_event` funkcją `read()`.
3. Filtruje tylko zdarzenia:
   - `ie.type == EV_KEY` (zdarzenia klawiszy),
   - `ie.value == 1` (pojedyncze wciśnięcie klawisza; pomija puszczenie i autorepeat).
4. Dla spełnionych warunków wypisuje na konsolę kod `ie.code - 1`.
5. Wymusza natychmiastowy flush wyjścia (`fflush(stdout)`), żeby wynik pojawiał się od razu.

---
