#ifndef FUNCTIONS_H
    #define FUNCTIONS_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "classes.h"

using namespace std;

void ClearScreen();

void NotRecognizedCommand();

void NoCommandOnInput();

void NoSave();

void IncorrectCommand();

vector<string> GetWords(istream & input);

vector<string> GetCommand();

vector<building> ReadBuildingData();

vector<upgrade> ReadUpgrades();

void WelcomeScreen();

void WinScreen(int n);

void PlayMenuScreen();

void Command_Welcome(int & action);

void Quit(bool & quit);

void AskSave(bool & save);

void Command_PlayMenu(int & action);

void PlayMenu();

void MenuLoop();

void Command_InGame(int & action, int & quantity, string & build, string & upgrade);

void GameLoop(bool loaded, string savename, bool & load_fail);

#endif
