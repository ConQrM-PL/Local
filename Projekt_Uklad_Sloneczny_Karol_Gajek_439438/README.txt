#########################################################

Instrukcja oprogramowania "symulatora ukladu slonecznego"

#########################################################

    Karol Gajek 439438


1. kompilacja

    g++ projekt.cpp Vec2D.cpp Planeta.cpp Uklad_Sloneczny.cpp -std=c++11 -I[sciezka do pythona] -lpython3.10

    dla komputerow OKWF, uzylem sciezki: /usr/include/python3.10, czyli polecenie postaci:
    g++ projekt.cpp Vec2D.cpp Planeta.cpp Uklad_Sloneczny.cpp -std=c++11 -I/usr/include/python3.10 -lpython3.10

2. edycja
    Projekt pozwala na edycję z poziomu pliku glownego (projekt.cpp):
        -   kroku symulacji
        -   maksymalnego czasu symulacji
        -   czestosci generowania grafik
    Alternatywne dane wejsciowe mozna ustawic podmieniajac zawartosc pliku "planety.txt"

    Domyslne dane wejsciowe:
        -   krok = 10*(24*60*60) (10 dni w [s])
        -   maksymalny czas = 1000*krok
        -   czestotliwosc = 50 krokow

3. uruchomienie i wyjscie
    Domyslnie program uruchamiamy komenda ./a.out

    Program twozy w folderach "data" oraz "plots" odpowiednio:
        -   surowe dane z kolejnych krokow dzialania programu
        -   grafiki w formacie .png

    Program mozna uruchamiac wielokrotnie, poniewaz nadpisuje on dane wygenerowane
    z popzedniej sesji (przy niezmienionym pliku planety.txt)
