
### Implementacja wątka do komunikacji z usb
- zapisujemy do bufora dane które chcemy wysłać
- w momencie wysyłki kopiujemy bufor to tmp po czym czyścimu bufor
- odczytujemy w while() dane z kopii bufora i wysyłamy przez USB
- na czas kopiowania bufora blokujemy zapis mutexami 
- jeżeli przycisk jest zablokowany (bo dane są wysyłane) to co?
    -> opcja 1 - eventy lecą w kosmos i tyle (nie powinno być za dużo)
    -> opcja 2 - jakiś drugi bufor (i tylko jak sie przepełni to wywalamy w kosmos)
