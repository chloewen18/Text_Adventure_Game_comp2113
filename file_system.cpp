// file_system.cpp
#include "file_system.h"
#include <fstream>
#include <iostream>
using namespace std;

void saveGame(const Player& p, std::string filename) {
    ofstream fout(filename);
    if (!fout) {
        cout << "Save Operation Failed - Unable to access file!" << endl;
        return;
    }

    fout << p.health << endl;
    fout << p.strength << endl;
    fout << p.intelligence << endl;
    fout << p.money << endl;           // 怪物血液
    fout << p.currentDay << endl;
    fout << p.actionPoints << endl;
    fout << p.backpackSize << endl;
    fout << p.itemCount << endl;

    for (int i = 0; i < p.itemCount; i++) {
        fout << p.backpack[i] << " ";
    }
    fout << endl;

    fout.close();
    cout << "Contract Saved Successfully to " << filename << endl;
}

bool loadGame(Player& p, std::string filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "No Previous Operation Found - Starting New Contract." << endl;
        return false;
    }

    // 释放旧背包内存
    if (p.backpack != nullptr) {
        delete[] p.backpack;
        p.backpack = nullptr;
    }

    fin >> p.health;
    fin >> p.strength;
    fin >> p.intelligence;
    fin >> p.money;
    fin >> p.currentDay;
    fin >> p.actionPoints;
    fin >> p.backpackSize;
    fin >> p.itemCount;

    p.backpack = new int[p.backpackSize];
    for (int i = 0; i < p.backpackSize; i++) p.backpack[i] = 0;

    for (int i = 0; i < p.itemCount; i++) {
        fin >> p.backpack[i];
    }

    fin.close();
    cout << "Operation Resumed Successfully! Day " << p.currentDay 
         << " | Blood Units:" << p.money 
         << " | Backpack: " << p.itemCount << "/" << p.backpackSize << endl;
    return true;
}