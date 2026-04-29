#include "game_shared.h"
#include "action.h"
#include "file_system.h"
#include "game_flow.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void showMainMenu() {
    cout << "\n========================================" << endl;
    cout << "     ISLAND MERC: 5 DAYS OF BLOOD     " << endl;
    cout << "========================================" << endl;
    cout << "1. Start New Contract" << endl;
    cout << "2. Resume Previous Operation (Load Save)" << endl;
    cout << "0. Abort Mission" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter Command: ";
}

int main() {
    srand(time(NULL));
    Player p = {};

    while (true) {
        showMainMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "\n[SYSTEM] Contract Accepted. Deploying to the island..." << endl;
            
            cout << "Select Difficulty: 1. EASY  2. NORMAL" << endl;
            cout << "Choice >> ";
            int diff;
            cin >> diff;
            
            initPlayer(p);

            if (diff != 1 && diff != 2) {
                cout << "[!] Invalid input. Defaulting to NORMAL difficulty." << endl;
                diff = 2;
            }
            
            setDifficulty(p, diff);

            cout << "\n[MISSION START] Mode: " 
                 << (diff == 1 ? "EASY" : "NORMAL") << endl;

            startGame(p);
            break;
        }
        else if (choice == 2) {
            if (loadGame(p, "save.txt")) {
                cout << "\nOperation Resumed. Welcome back, Mercenary.\n" << endl;
                startGame(p);
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
