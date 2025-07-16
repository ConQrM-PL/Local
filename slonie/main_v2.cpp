/*
Program napisany na potrzeby procesu rekrutacyjnego dla firmy ImpiCode

Kompilacja normalna, np. g++ main_v2.cpp -o slonie.exe

wersja 2.0
*/
#include<iostream>
#include<vector>

using namespace std;

class slon {
public:
    int ID;
    int masa;
    bool czy_w_ciagu = false;
    int kolejny_slon_ID;
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
    vector<int> pozycje_poczatkowe, pozycje_koncowe;
    for (size_t i = 0; i < N; i++){
        cin >> wejscie;
        pozycje_poczatkowe.push_back(wejscie - 1);
    }
    for (size_t i = 0; i < N; i++){
        cin >> wejscie;
        pozycje_koncowe.push_back(wejscie - 1);
    }
    for (size_t i = 0; i < N; i++){
        lista_sloni[pozycje_poczatkowe[i]].kolejny_slon_ID = lista_sloni[pozycje_koncowe[i]].ID;
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

long long Rozwaz_cykl(vector<slon> & lista_sloni, int ID_rozwazane, int min_masa_globalna){
    int min_masa = 6500, dlugosc_cyklu = 0;
    long long suma_mas = 0, metoda1, metoda2;

    while (!(lista_sloni[ID_rozwazane].czy_w_ciagu)){
        lista_sloni[ID_rozwazane].czy_w_ciagu = true;
        min_masa = Minimum(min_masa, lista_sloni[ID_rozwazane].masa);
        suma_mas += lista_sloni[ID_rozwazane].masa;
        ID_rozwazane = lista_sloni[ID_rozwazane].kolejny_slon_ID;
        dlugosc_cyklu++;
    }
    metoda1 = suma_mas + (dlugosc_cyklu - 2) * min_masa;
    metoda2 = suma_mas + min_masa + (dlugosc_cyklu + 1) * min_masa_globalna;
    return Minimum(metoda1, metoda2);
}


long long Rozwaz_wszystkie_cykle(vector<slon> lista_sloni){
    bool flag = false;
    int min_masa_globalna = Globalna_masa_min(lista_sloni);
    long long caly_koszt = 0;
    for (size_t i = 0; i < lista_sloni.size(); i++){
        if (!(lista_sloni[i].czy_w_ciagu)){
            caly_koszt += Rozwaz_cykl(lista_sloni, i, min_masa_globalna);
        }
    }
    return caly_koszt;
}



int main(){
    vector<slon> lista_sloni = Wczytaj_dane_wejsciowe();
    long long wynik = Rozwaz_wszystkie_cykle(lista_sloni);
    cout << wynik << "\n";
    return 0;
}
