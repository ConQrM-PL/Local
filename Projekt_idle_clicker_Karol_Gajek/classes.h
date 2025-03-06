#ifndef CLASSES_H
    #define CLASSES_H

#include <iostream>
#include <string>
#include <vector>


using namespace std;

class upgrade{
public:
    string name;
    float cost;
    int building_ID;
    // perks
    float cost_modifier;
    float income_modifier;

    upgrade(int ID, string text, float price, float cm, float im);
};

class building{
public:
    int ID;
    string name;
    // stats per budynek
    float base_cost;
    float base_income;
    float cost_modifier;
    float income_modifier;

    void update_modifiers(float new_im, float new_cm);

    building(int num, string text, float cost, float income);
};

class game{
public:
    float money;
    float income;
    int turns;
    float event_modifier = 1.0;
    int event_timer = 0;
    int last_event = 0;
    int event_ID = 0;
    bool no_event = true;
    bool won = false;

    vector<building> buildings; // buildings in game
    vector<upgrade> upgrades; // upgrades in game
    vector<int> owned_buildings; // buildings owned
    vector<bool> owned_upgrades; // upgrades owned

    game();
    game(string save, bool & failed);
    void event();
    void next_turn();
    void add_money(float n);
    void show();
    void build(int k, string structure, bool & if_build, float & diff);
    void upgrade(string structure, string name, bool & if_bought, bool & already_bought, float & diff);
    bool has_money(float m);
    void check_new_modifiers(float & new_im, float & new_cm);
    void save_game(string text);
    bool check_win();
    
};

float GetIncome(vector<building> b, vector<int> n);

#endif