// main.cpp
#include "game_shared.h"
#include "file_system.h"
#include "game_flow.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void showMainMenu() {
    cout << "\n========================================"<<endl;
    cout << "     ISLAND MERC: 14 DAYS OF BLOOD     "<<endl;
    cout << "========================================"<<endl;
    cout << "1. Deploy to Island (New Contract)" << endl;
    cout << "2. Resume Operation (Load Previous Save)" << endl;
    cout << "0. Abort Mission (Exit Game)" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter Command: ";
}

int main() {
    srand(time(NULL));          // 随机数种子

    Player p = {};              // 初始化为空

    int choice;
    while (true) {
        showMainMenu();
        cin >> choice;

        if (choice == 1) {                    // 开始新游戏
            cout << "\nContract Accepted. Deploying to the island...\n" << endl;
            initPlayer(p);
            setDifficulty(p, 2);              // 默认普通难度（可改成1/3）
            startGame(p);
            break;
        }
        else if (choice == 2) {               // 读取存档
            if (loadGame(p, "save.txt")) {
                cout << "\nOperation Resumed. Welcome back, Merc.\n" << endl;
                startGame(p);                 // 直接继续游戏
                break;
            }
        }
        else if (choice == 0) {
            cout << "\nMission Aborted. See you on the next island, soldier." << endl;
            break;
        }
        else {
            cout << "Command not recognized. Stand by for orders." << endl;
        }
    }

    destroyPlayer(p);
    return 0;
}