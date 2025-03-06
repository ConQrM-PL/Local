#include "functions.h"
#include "classes.h"

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <cassert>
#include <limits>
#include <iomanip>


using namespace std;
using std::cout;

// czysci ekran
void ClearScreen(){
    cout << "\033c";
}

// komunikuje o nierozpoznaniu polecenia
void NotRecognizedCommand(){
    cout << "Command not found\n";
}

// komunikuje ze nie podano polecenia
void NoCommandOnInput(){
    cout << "No command on input\n";
}

// komunikuje brak podania nazwy zapisu
void NoSaveName(){
    cout << "No save name was given. Save not created\n";
}

// zapis nie istnieje
void NoSave(){
    cout << "Save file don't exist\n";
}

// komunikuje ze polecenie jest niepoprawne
void IncorrectCommand(){
    cout << "Incorrect command\n";
}

// wypisuje ekran zwyciestwa
void WinScreen(int n, string name){
    ClearScreen();
    cout << "Congratulations! You have won by building the "+name+" in " << n << " turns!\n\nPress enter to quit to main menu\n";
}

// rozbija strumien string na wyrazy w wektorze
vector<string> GetWords(istream & input){
    vector<string> result;
    string word;
    while (input >> word){
        result.push_back(word);
    }
    return result;
}

// wczytuje dane z wejscia cin i zapisuje je jako wektor string
vector<string> GetCommand(){
    string input;
    getline(cin, input);
    istringstream iss(input);
    return GetWords(iss);
}

// wczytuje dostepne budynki w grze z pliku buildings.txt
vector<building> ReadBuildingData(){
    ifstream input;
    input.open("buildings.txt");
    string line;
    vector<string> words;
    vector<building> result;
    while(getline(input, line)){
        istringstream iss(line);
        words = GetWords(iss);
        assert (words.size() >= 4);
        try {
        result.push_back(building(stoi(words[0]), words[1], stof(words[2]), stof(words[3]))); // id, name, cost, income
        } catch(...) {
            assert (false);
        }
    }
    input.close();
    return result;
}

//  wczytuje dostepne ulepszenia w grze z pliku upgrades.txt
vector<upgrade> ReadUpgrades(){
    ifstream input;
    input.open("upgrades.txt");
    string line;
    vector<string> words;
    vector<upgrade> result;
    while(getline(input, line)){
        istringstream iss(line);
        words = GetWords(iss);
        assert (words.size() >= 5);
        try {
        upgrade temp(stoi(words[0]), words[1], stof(words[2]),  stof(words[3]), stof(words[4]));
        result.push_back(temp);
        } catch(...){
            assert (false);
        }
    }
    input.close();
    return result;
}

// wyswietla menu glowne
void WelcomeScreen(){
    ClearScreen();
    cout << "This is a project of an Idle Game!\n\nType \"play\" to play the game.\nType \"quit\" to quit the game.\n\nWritten by Karol Gajek :3\n\n";
}

// wyswietla menu play
void PlayMenuScreen(){
    ClearScreen();
    cout << "Choose to play a new game by typing \"play\".\nTo play an existing game, type \"load\" followed by the save name.\nTo return to menu type \"back\"\n";
}

// wczytuje z wiersza polecen na menu glownym
void Command_Welcome(int & action){
    vector<string> input = GetCommand();
    if (input.size() < 1) {
        action = -2;
        return;
    }
    string com = input[0];
    if (com == "play"){
        action = 1;
    } else if (com == "quit"){
        action = 0;
    } else {
        action = -1;
    }
}

// opcja quit w menu glownym
void Quit(bool & quit){
    cout << "Are you sure? [y/n]\n";
    char c;
    cin >> c;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (c == 'y'){
        quit = true;
    } else {
        WelcomeScreen();
    }
}

// zapytanie czy chcesz zapisac gre
void AskSave(bool & save){
    cout << "Do you want to save the game? [y/n]\n";
    char c;
    cin >> c;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    if (c == 'y'){
        save = true;
    } else {
        save = false;
    }
}

// czyta komende z wiersza menu play
void Command_PlayMenu(int & action, string & savename){
    vector<string> input = GetCommand();
    if (input.size() < 1) {
        action = -2;
        return;
    }
    string com = input[0];
    if (com == "play"){
        action = 1;
    } else if (com == "back"){
        action = 0;
    } else if(com == "load"){
        action = 2;
        if (input.size() < 2) {
            action = -3;
        } else {
            savename = input[1];
        }
    } else {
        action = -1;
    }
}

// opcja play w menu glownym
void PlayMenu(){
    PlayMenuScreen();
    bool back = false;
    int action;
    string temp;
    bool load_fail;
    while (!back){
        Command_PlayMenu(action, temp);
        switch (action){
            case 1: // play
                GameLoop(false, temp, load_fail);
                back = true;
                break;
            case 0: // back
                WelcomeScreen();
                back = true;
                break;
            case 2: // load
                GameLoop(true, temp, load_fail);
                back = true;
                break;
            case -3:
                PlayMenuScreen();
                IncorrectCommand();
                break;
            case -2:
                PlayMenuScreen();
                NoCommandOnInput();
                break;
            case -1:
            default:
                PlayMenuScreen();
                NotRecognizedCommand();
                break;
        }
    }
}

// interpretuje polecenie w trakcie gry
void Command_InGame(int & action, int & quantity, string & build, string & upgrade){
    vector<string> input = GetCommand();
    if (input.size() < 1) {
        action = 0; // next turn
        return;
    }
    string com = input[0];
    if (com == "buy"){
        action = 1;
        if (input.size() < 3){
            action = -3;
        } else {
            try{
                quantity = stoi(input[1]);
                build = input[2];
            } catch (...){
                action = -3;
            }
        }
    } else if (com == "menu" || com == "back"){
        action = 2;
    } else if(com == "upgrade"){
        action = 3;
        if (input.size() < 3){
            action = -3;
        } else {
            build = input[1];
            upgrade = input[2];
        }
    } else if(com == "save"){
        action = 4;
        if (input.size() < 2) {
            action = -3;
        } else {
            build = input[1];
        }
    } else {
        action = -1;
    }    

}

// glowny trzon gry
void GameLoop(bool loaded, string savename, bool & load_fail){
    int action;
    int quantity;
    string build;
    string upgrade_name;
    bool playing = true;
    bool didbuild, hasup;
    float difference;
    game core;
    bool save_not_exist;
    if (loaded){
        game tempgame(savename, save_not_exist);
        if (!save_not_exist) core = tempgame;
    }
    if (!save_not_exist){
        load_fail = false;
        core.show();
        while (playing){
            Command_InGame(action, quantity, build, upgrade_name);
            switch(action){
                case 0: // next turn
                    core.next_turn();
                    core.show();
                        break;
                case 1:
                    core.build(quantity, build, didbuild, difference);
                    if (didbuild){
                        if (core.won){
                            playing = false;
                        } else {
                            core.show();
                            cout << "Purchase of " << quantity << " " << build <<" successfull!\n";
                        }
                    } else {
                        core.show();
                        cout << "Not enough money! Need "<< setprecision(3) << difference <<" more!\n";
                    }
                    break;
                case 2:
                    bool saving;
                    AskSave(saving);
                    if (saving){
                        cout << "Type a name for your save: \n";
                        vector<string> temp = GetCommand();
                        if (temp.size() > 0) {
                            core.save_game(temp[0]);
                            playing = false;
                            WelcomeScreen();
                        } else {
                            WelcomeScreen();
                            NoSaveName();
                        }
                    } else {
                        playing = false;
                        WelcomeScreen();
                    }

                    break;
                case 3:
                    core.upgrade(build, upgrade_name, didbuild, hasup, difference);
                    if (hasup){
                        core.show();
                        cout << "Already bought that upgrade!\n";
                    } else {
                        if (didbuild){
                            core.show();
                            cout << build << " successfuly upgraded with " << upgrade_name << "!\n";
                        } else {
                            if (difference < 0){
                                core.show();
                                NotRecognizedCommand();
                            } else {
                                core.show();
                                    cout << "Not enough money! Need "<< setprecision(3) << difference <<" more!\n";
                            }
                        }
                    }
                    break;
                case 4:
                    core.save_game(build);
                    core.show();
                    cout << "Game saved!\n";
                    break;
                case -3:
                    core.show();
                    IncorrectCommand();
                    break;
                case -1:
                default:
                    core.show();
                    NotRecognizedCommand();
                    break;
            }
        }
        if (core.won){
            WinScreen(core.turns, core.buildings.back().name);
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            WelcomeScreen();
    
        }
    } else {
        load_fail = true;
        WelcomeScreen();
        NoSave();
    }
}

// menu glowne
void MenuLoop(){
    WelcomeScreen();
    int menu;
    bool quit = false;
    while (!quit){
        Command_Welcome(menu);
        switch(menu){
            case 0:{
                Quit(quit);
                break;
            }
            case 1:
                PlayMenu();
                break;
            case -2:
                WelcomeScreen();
                NoCommandOnInput();
                break;
            case -1:
            default:
                WelcomeScreen();
                NotRecognizedCommand();
                break;
        }
    }

}