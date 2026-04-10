// file.cpp
#include "file.h"
#include <fstream>
#include <iostream>
using namespace std;

void saveGame(Player& p, const char* filename) {
    ofstream fout(filename);
    
    if (!fout) {
        cout << "保存失败" << endl;
        return;
    }
    
    // 保存所有数据
    fout << p.health << endl;
    fout << p.strength << endl;
    fout << p.intelligence << endl;
    fout << p.money << endl;
    fout << p.currentDay << endl;
    fout << p.currentActionPoint << endl;
    fout << p.backpackSize << endl;
    
    // 保存背包内容
    for (int i = 0; i < p.backpackSize; i++) {
        fout << p.backpack[i] << " ";
    }
    fout << endl;
    
    fout.close();
    cout << "游戏已保存到 " << filename << endl;
}

bool loadGame(Player& p, const char* filename) {
    ifstream fin(filename);
    
    if (!fin) {
        cout << "没有找到存档文件" << endl;
        return false;
    }
    
    // 读取数据
    fin >> p.health;
    fin >> p.strength;
    fin >> p.intelligence;
    fin >> p.money;
    fin >> p.currentDay;
    fin >> p.currentActionPoint;
    fin >> p.backpackSize;
    
    // 重新分配背包内存
    p.backpack = new int[p.backpackSize];
    for (int i = 0; i < p.backpackSize; i++) {
        fin >> p.backpack[i];
    }
    
    fin.close();
    cout << "读取存档成功！" << endl;
    cout << "第 " << p.currentDay << " 天，金钱：" << p.money << endl;
    return true;
}

void showSaveInfo(const char* filename) {
    ifstream fin(filename);
    if (!fin) {
        cout << "无存档" << endl;
        return;
    }
    
    int day, money;
    fin >> day;  // 跳过的简单示范
    // 实际需要完整读取，这里简化
    fin.close();
}