#include "game_shared.h"
#cinluce "action.h"
#include "file_system.h"
#include "game_flow.h"
#include "player.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

void showMainMenu() {
    cout << "\n========================================" << endl;
    cout << "     ISLAND MERC: 14 DAYS OF BLOOD     " << endl;
    cout << "========================================" << endl;
    cout << "1. Start New Contract" << endl;
    cout << "2. Resume Previous Operation (Load Save)" << endl;
    cout << "0. Abort Mission" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Enter Command: ";
}

void showDifficultyMenu() {
    cout << "\n========================================" << endl;
    cout << "         SELECT DIFFICULTY             " << endl;
    cout << "========================================" << endl;
    cout << "1. Standard Difficulty" << endl;
    cout << "2. Hard Difficulty" << endl;
    cout << "----------------------------------------" << endl;
    cout << "Choose difficulty: ";
}

int main() {
    srand(time(NULL));
    Player p = {};

    while (true) {
        showMainMenu();
        int choice;
        cin >> choice;

        if (choice == 1) {
            cout << "\nContract Accepted. Deploying to the island...\n" << endl;

            showDifficultyMenu();
            int diff;
            cin >> diff;

            if (diff != 1 && diff != 2) {
                cout << "Invalid input. Defaulting to Standard difficulty.\n" << endl;
                diff = 1;
            }

            initPlayer(p);
            setDifficulty(p, diff);

            cout << "Mission started on " 
                 << (diff == 1 ? "Standard" : "Hard") 
                 << " difficulty.\n" << endl;

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
