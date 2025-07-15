/*
Program napisany na potrzeby procesu rekrutacyjnego dla firmy ImpiCode

Kompilacja normalna, np. g++ main.cpp -o slonie.exe
*/
#include<iostream>
#include<vector>

using namespace std;

class slon {
public:
    int ID;
    int pozycja_poczatkowa;
    int pozycja_docelowa;
    int masa;
    bool czy_w_ciagu = false;
    slon(){};
};

template <class T>
T Minimum (T a, T b){
    if (a > b){
        return b;
    } else {
        return a;
    }
}

vector<slon> Wczytaj_dane_wejsciowe(){
    vector<slon> lista_sloni;
    slon tymczasowy_slon;
    int N, wejscie, pozycja;
    cin >> N;
    for (size_t i = 0; i < N; i++){
        cin >> wejscie;
        tymczasowy_slon.masa = wejscie;
        tymczasowy_slon.ID = i;
        lista_sloni.push_back(tymczasowy_slon);
    }
    for (size_t i = 0; i < N; i++){
        cin >> wejscie;
        lista_sloni[wejscie-1].pozycja_poczatkowa = i;
    }
    for (size_t i = 0; i < N; i++){
        cin >> wejscie;
        lista_sloni[wejscie-1].pozycja_docelowa = i;
    }
    return lista_sloni;
}

int Globalna_masa_min(vector<slon> lista_sloni){
    int wynik = 6500;
    for (size_t i = 0; i < lista_sloni.size(); i++){
        wynik = Minimum(wynik, lista_sloni[i].masa);
    }
    return wynik;
}

int Znajdz_ID(vector<slon> lista_sloni, int pozycja){
    for (size_t i = 0; i < lista_sloni.size(); i++){
        if (lista_sloni[i].pozycja_poczatkowa == pozycja){
            return (int) i;
        }
    }
    cout <<"error: nie powinno bylo tego widac\n";
    return -1;
}

int Rozwaz_cykl(vector<slon> & lista_sloni, int ID_startu_cyklu, int min_masa_globalna){
    int min_masa = 6500, dlugosc_cyklu = 0;
    int ID_rozwazane = ID_startu_cyklu;
    long suma_mas = 0, metoda1, metoda2;
    while (!(lista_sloni[ID_rozwazane].czy_w_ciagu)){
        lista_sloni[ID_rozwazane].czy_w_ciagu = true;
        min_masa = Minimum(min_masa, lista_sloni[ID_rozwazane].masa);
        suma_mas += lista_sloni[ID_rozwazane].masa;
        ID_rozwazane = Znajdz_ID(lista_sloni, lista_sloni[ID_rozwazane].pozycja_docelowa);
        dlugosc_cyklu++;
    }
    metoda1 = suma_mas + (dlugosc_cyklu - 2) * min_masa;
    metoda2 = suma_mas + min_masa + (dlugosc_cyklu + 1) * min_masa_globalna;
    return Minimum(metoda1, metoda2);
}


int Rozwaz_wszystkie_cykle(vector<slon> lista_sloni){
    int min_masa_globalna = Globalna_masa_min(lista_sloni);
    int caly_koszt = 0;
    for (size_t i = 0; i < lista_sloni.size(); i++){
        if (!(lista_sloni[i].czy_w_ciagu)){
            caly_koszt += Rozwaz_cykl(lista_sloni, i, min_masa_globalna);
        }
    }
    return caly_koszt;
}



int main(){
    vector<slon> lista_sloni = Wczytaj_dane_wejsciowe();
    int wynik = Rozwaz_wszystkie_cykle(lista_sloni);
    cout << wynik << "\n";
    return 0;
}
