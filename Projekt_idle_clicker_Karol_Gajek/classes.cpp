#include <iostream>
#include <map>
#include <string>
#include <random>
#include <fstream>
#include <filesystem>
#include <cassert>
#include "classes.h"
#include "functions.h"

using namespace std;


random_device device;
mt19937 gen(device());
uniform_int_distribution<int> distr(1, 100);
// liczba losowa w przedziale 1 100 jako distr(random)

// funkcja przyjmujaca aktualny przychod
float GetIncome(vector<building> b, vector<int> n, float event_modifier){
    float sum = 0.0;
    for (size_t i = 0; i < n.size(); i++){
        sum += b[i].base_income * n[i] *b[i].income_modifier*event_modifier;
    }
    return sum;
}

// kreator klasy ulepszenia
upgrade::upgrade(int ID, string text, float price, float cm, float im){
    name = text;
    cost = price;
    building_ID = ID;
    cost_modifier = cm;
    income_modifier = im;
}

// kreator klasy budynku
building::building(int num, string text, float cost, float income){
    ID = num;
    name = text;
    base_cost = cost;
    base_income = income;
    cost_modifier = 1.0;
    income_modifier = 1.0;
}

// aktualizacja modyfikatorow przychodu i kosztow
void building::update_modifiers(float new_im, float new_cm){
    income_modifier += new_im;
    cost_modifier += new_cm;
}

// kreator nowej gry
game::game(){
    money = 0.0;
    turns = 0;
    buildings = ReadBuildingData();
    upgrades = ReadUpgrades();
    vector<int> tempb(buildings.size(), 0);
    owned_buildings = tempb;
    vector<bool> tempu(upgrades.size(), 0);
    owned_upgrades = tempu;
    owned_buildings[0] = 1;
    income = GetIncome(buildings, owned_buildings, event_modifier);
}

// kreator gry z zapisu
game::game(string save, bool & failed){
    buildings = ReadBuildingData();
    upgrades = ReadUpgrades();
    filesystem::path filepath = "saves/"+save;
    ifstream file;
    file.open(filepath);
    if (file) {
        string line;
        vector<string> words;
        getline(file, line);
        istringstream iss(line);
        words = GetWords(iss);
        assert (words.size() >= 7);
        try{
        money = stof(words[0]); 
        turns = stoi(words[1]);
        event_modifier = stof(words[2]);
        event_timer = stoi(words[3]);
        last_event = stoi(words[4]);
        event_ID = stoi(words[5]);
        no_event = stoi(words[6]);
        getline(file, line);
        iss.clear();
        iss.str(line);
        words = GetWords(iss);
        for (size_t i = 0; i < words.size(); i++){
            owned_buildings.push_back(stoi(words[i]));
        }
        getline(file, line);
        iss.clear();
        iss.str(line);
        words = GetWords(iss);
        for (size_t i = 0; i < words.size(); i++){
            owned_upgrades.push_back(stoi(words[i]));
        }
        vector<float> building_modifiers;
        getline(file, line);
        iss.clear();
        iss.str(line);
        words = GetWords(iss);
        for (size_t i = 0; i < words.size()/2; i++){
            buildings[i].update_modifiers(stof(words[2*i]),stof(words[2*i+1]));
        }
        } catch (...){
            assert (false);
        }
        failed = false;
        file.close();
        income = GetIncome(buildings, owned_buildings, event_modifier);
    } else {
        failed = true;
    }
}

// metoda nastepnej tury
void game::next_turn(){
    turns++;
    if (event_timer > 0) {
        event_timer--;
    } else {
        no_event = true;
    }
    income = GetIncome(buildings, owned_buildings, event_modifier);
    money += income;
    event();
}

// sprawdza czy wygrales gre
bool game::check_win(){
    if (owned_buildings.back() > 0){
        return true;
    } else {
        return false;
    }
}

// dodaje wskazana ilosc pieniedzy
void game::add_money(float n){
    money += n;
}

// wyswietla stan gry
void game::show(){
    ClearScreen();
    income = GetIncome(buildings, owned_buildings, event_modifier);
    if (turns == 0 ) cout << "This is the game. Press enter for the next turn.\nType \"buy [number] [building name]\" to buy buildings.\nType \"upgrade [building] [upgrade name]\" to buy an upgrade.\nType \"save [savefile]\"to create a save named as chosen.\nType \"back\" to quit to main menu.\n"; // TBA
    if (!no_event){
        switch(event_ID){
            case 1:
                cout << "Event: Prospering times! Income from buildings increased by 50\% for next " << event_timer << " turns.\n";
                break;
            case 2:
                cout << "Event: A catastrophe! Income from buildings decreased by 20\% for next " << event_timer << " turns.\n";
                break;
            default:
                break;
        }
    } else {
        cout << "Event: no effect from event\n";
    }
    cout << "Turns: " << turns <<"\n";
    cout << "Total income: " << income << "\n";
    cout << "Money on hand: " << money << "\n\n";
    cout << "Properties: \n";
    for (size_t i = 0; i < buildings.size() - 1; i++){
        cout << buildings[i].name << " x " << owned_buildings[i] << " income per unit: " << buildings[i].base_income*buildings[i].income_modifier << " cost per unit: " << buildings[i].base_cost*buildings[i].cost_modifier <<"\n";
    }
    cout << buildings.back().name << " - buy it to win the game! Price: " << buildings.back().base_cost << endl;

}

// sprawdza czy gracz posiada pieniadze na zakup
bool game::has_money(float m){
    if (m <= money){
        return true;
    } else {
        return false;
    }
}

// buduje wskazany typ budynku wskazana ilosc razy
void game::build(int k, string structure, bool & if_build, float & diff){
    size_t i = 0;
    while(buildings[i].name != structure && i < buildings.size()){
        i++;
    }
    
    float payment = k*buildings[i].base_cost*buildings[i].cost_modifier;
    if (has_money(payment)){
        owned_buildings[i] += k;
        add_money(-payment);
        if_build = true;
        buildings[i].cost_modifier += 0.05;
        won = check_win();
    } else {
        if_build = false;
        diff = payment-money;
    }
}

// sprawdza o ile powinny zmienic sie modyfikatory w budynkach
void game::check_new_modifiers(float & new_im, float & new_cm){
    new_im = 0.0;
    new_cm = 0.0;
    for (size_t i = 0; i < owned_upgrades.size(); i++){
        if (owned_upgrades[i]){
            new_im += upgrades[i].income_modifier;
            new_cm += upgrades[i].cost_modifier;
        }
    }
}

// kupuje ulepszenie o danej nazwie dla danego budynku
void game::upgrade(string structure, string name, bool & if_bought, bool & already_bought, float & diff){
    size_t ib = 0;
    already_bought = false;
    while(buildings[ib].name != structure && ib < buildings.size()){
        ib++;
    }
    size_t iu = 0;
    while ((upgrades[iu].building_ID != (int) ib || upgrades[iu].name != name) && iu < upgrades.size()){
        iu++;
    }
    if (iu == upgrades.size() || ib == buildings.size()){
        if_bought = false;
        diff = -1;
    } else if (owned_upgrades[iu]){
        already_bought = true;
    } else {
        float payment = upgrades[iu].cost;
        if (has_money(payment)){
            owned_upgrades[iu] = true;
            add_money(-payment);
            if_bought = true;
            float im, cm;
            check_new_modifiers(im, cm);
            buildings[ib].income_modifier = 1.0;
            buildings[ib].cost_modifier = 1.0;
            buildings[ib].update_modifiers(im, cm);
        } else {
            if_bought = false;
            diff = payment-money;
        }
    }

}


// losuje wydarzenia
void game::event(){
    if (no_event && turns > 10){
        int l = distr(gen);
        if (l <= 70){
            // no events
            no_event = true;
            last_event++;
            event_modifier = 1.0;
            event_ID = 0;
        } else if (l <= 90 && last_event > 20){
            // good events
            event_timer = 10;
            event_modifier = 1.5;
            no_event = false;
            last_event = 0;
            event_ID = 1;
        } else if (last_event > 20){
            // bad events
            event_timer = 10;
            event_modifier = 0.8;
            no_event = false;
            last_event = 0;
            event_ID = 2;
        } else {
            no_event = true;
            last_event++;
            event_modifier = 1.0;
            event_ID = 0;
        }
    }
}

// zapisuje stan gry do pliku
void game::save_game(string text){
    fstream file;
    filesystem::path filepath = "saves/"+text;
    file.open(filepath, ios::out);
    // variables
    file << money << " " << turns << " " << event_modifier << " " << event_timer << " " << last_event << " " << event_ID << " " << no_event << endl;
    for (size_t i = 0; i < owned_buildings.size(); i++){
        file << owned_buildings[i] <<  " ";
    }
    file << endl;
    for (size_t i = 0; i < owned_upgrades.size(); i++){
        file << owned_upgrades[i] << " ";
    }
    file << endl;
    for (size_t i = 0; i < buildings.size(); i++){
        file << buildings[i].income_modifier - 1 << " " << buildings[i].cost_modifier - 1 << " ";
    }
    file.close();
}