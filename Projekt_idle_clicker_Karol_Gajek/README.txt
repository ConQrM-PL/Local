Karol Gajek 439438

I projekt zaliczeniowy PIMN - gra typu idle

Kompilacja i uruchomienie:

Program skompilowano poleceniem:
g++ main.cpp functions.cpp classes.cpp -o gra -Wall
program do uruchomienia musi być w tym samym folderze co pliki buildings.txt i upgrades.txt oraz folder saves*

*-być może to konkretne nie jest konieczne, nie testowałem tego

Instrukcja:

Menu główne:
Gra jest napisana po angielsku (bo jakoś tak mi było wygodniej).
Po uruchomieniu widzimy ekran menu głównego, z którego możemy przejść do menu rozgrywek (play), lub wyjść z gry (quit).
Polecenia są wyświetlane na ekranie gdybyśmy zapomnieli.

Kiedy wpiszemy quit, gra spyta się o potwierdzenie znakiem 'y'. każdy inny znak zostanie zinterpretowany za odrzucenie 'n'.
Warto tu zaznaczyć, że program ignoruje spacje między wyrazami na wejściu, dlatego "y" zostanie zinterpretowane tak samo jak "    y  ".
Potwierdzenie zamyka program, natomiast zaprzeczenie pozostawia nas w menu głównym.

Zaznaczam tutaj od razu, że jeśli niczego nie przeoczyłem, program powinien reagować na niepoprawne komendy, wyświetlając stosowne komunikaty.

Menu rozgrywek:
Polecenie play tworzy nową grę. Polecenie load pozwala na wczytanie gry z pliku o danej nazwie.
Program jest odporny na brak podania nazwy oraz na podanie nazwy nieistniejącego pliku (wtedy program wyjdzie do menu głównego).
Polecenie back cofa nas do menu głównego (działa również polecenie menu - robi to samo).

Gra - interfejs:
Po wybraniu nowej gry, wyświetlają się dostępne polecenia. Kiedy przejdziemy do nowej tury, komunikat zniknie.
Polecenia:
    back lub menu - wyjście do menu głównego (gra spyta czy chcemy zapisać grę czy nie)
    save [nazwa pliku] - tworzy zapis obecnego stanu gry do pliku o podanej nazwie
    buy [ilość] [nazwa budynku] - kupuje budunki w podanej ilości
    upgrade [nazwa budynku] [nazwa ulepszenia] - kupuje ulepszenie dla danego budynku o danej nazwie
    (pusty wiersz) - następna tura.
Tutaj też uwaga - spacja jest separatorem między poszczególnymi wyrazami na wejściu, ale ilość spacji jest ignorowana.

Gra wyświetla informacje na temat:
    - obecny efekt zdarzeń losowych
    - numer obecnej tury
    - całkowity przychód
    - dostępne pieniądze
    - dostępne budynki z ich przychodem i ceną oraz ile danego rodzaju posiadamy.
Tutaj uwaga - w grze nie ma mechanizmu by sprawdzić jakie są możliwe ulepszenia do kupienia.
Domyślnie, każdy budynek ma ulepszenia: income_I income_II income_III oraz cost_I cost_II cost_III.

Rozgrywka:
Przychód jest liczony z posiadanych budynków, ulepszeń i ewentualnie jest modyfikowany przez wydarzenie losowe.
Koszt danego budynku rośnie o 5% ceny bazowej po każdym zakupie (nie budynku)- dodaje to trochę strategicznej głębi:
czy lepiej jest kupić budynek od razu by mieć szybciej przychód, czy może uzbierać by kupić ich więcej taniej?

Grę można skończyć kupując 1 zamek (1 castle) - wyświetli się ekran z gratulacjami i wynikiem, to jest liczbą rozegranych tur.

wydarzenia:
W grze są obecne 2 zdarzenia losowe - pozytywne (20%) i negatywne (10%) - które wpływają na nasz przychód.
W pierwsze 10 tur gry, oraz przez 20 tur od ostatniego wydarzenia, szansa na kolejne wydarzenie wynosi 0.

Modyfikacja:
Możemy zmodyfikować zawartość plików buildings.txt i upgrades.txt, by zmieniać ich nazwy i parametry.
Budynek jest zapisany następująco:
[ID] [nazwa] [cena bazowa] [przychód bazowy]
uwaga: ostatni budynek to zawsze ten którego kupienie kończy grę.
Ulepszenie zapisujemy następująco:
[ID budynku] [nazwa] [cena] [modyfikator kosztu] [modyfikator przychodu]
Uwaga: niepoprawnie zapisane pliki upgrade i buildings mogą wymusić zamknięcie programu.

Gra nie była testowana pod względem balansu.

To chyba tyle na ten moment, także tak :>