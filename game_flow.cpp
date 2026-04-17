#include "game_flow.h"
#include "player.h"
#include "action.h"
#include "file_system.h"

// Debt target you decided: 1000
const int DEBT_TARGET = 1000;

void triggerRandomEvent(Player& p) {
    // 15% chance to trigger an event
    int chance = rand() % 100;
    if (chance >= 15) return;

    int eventId = rand() % 10;
    cout << "\n[ RANDOM EVENT TRIGGERED! ]" << endl;

    switch (eventId) {
        case 0:
            cout << "You found a lost money bag! +30 money" << endl;
            p.money += 30;
            break;
        case 1:
            cout << "A villager gave you herbs! Obtained item" << endl;
            addItem(p, 1);
            break;
        case 2:
            cout << "You fought off a wild beast! Strength +1" << endl;
            p.strength += 1;
            break;
        case 3:
            cout << "You helped an old traveler! Intelligence +1" << endl;
            p.intelligence += 1;
            break;
        case 4:
            cout << "You found extra supplies! +1 Action Point" << endl;
            p.actionPoints += 1;
            break;
        case 5:
            cout << "Bad weather wasted your trip! Money -5" << endl;
            if (p.money >= 5) p.money -= 5;
            else p.money = 0;
            break;
        case 6:
            cout << "Lucky coin found! Next income doubled effect" << endl;
            addItem(p, 2);
            break;
        case 7:
            cout << "You rested well! You feel energized." << endl;
            // No stat change, just flavor
            break;
        case 8:
            cout << "Found an old backpack! Backpack +1 slot" << endl;
            p.backpackSize = min(10, p.backpackSize + 1);
            break;
        case 9:
            cout << "A stranger gave you charity! +15 money" << endl;
            p.money += 15;
            break;
    }
}

void processDay(Player& p) {
    p.actionPoints = 5;
    cout << "\n====================================" << endl;
    cout << "          DAY " << p.currentDay << " START" << endl;
    cout << "====================================" << endl;

    while (p.actionPoints > 0) {
        cout << "\nRemaining Action Points: " << p.actionPoints << endl;
        cout << "1. Hunt Monster" << endl;
        cout << "2. Help Villager" << endl;
        cout << "3. Show Backpack" << endl;
        cout << "4. End Today" << endl;
        cout << "Your choice: ";

        int choice;
        cin >> choice;

        if (choice == 4) {
            cout << "\nYou decide to rest early." << endl;
            break;
        }

        switch (choice) {
            case 1:
                hunt(p);
                break;
            case 2:
                helpVillager(p);
                break;
            case 3:
                showBackpack(p);
                continue; // does not cost AP
            default:
                cout << "Invalid input. Try again." << endl;
                continue;
        }

        p.actionPoints--;
        triggerRandomEvent(p);
    }

    cout << "\n====================================" << endl;
    cout << "          DAY " << p.currentDay << " END" << endl;
    cout << "====================================" << endl;
    p.currentDay++;
}

void startGame(Player& p) {
    srand(time(0)); // init random
    initPlayer(p);
    showMainMenu();

    cout << "\nYour debt: 1000 gold. You have 14 days to pay it back." << endl;
    cout << "Press any key to start..." << endl;
    cin.get();
    cin.get();

    while (true) {
        if (checkEndCondition(p)) {
            break;
        }
        processDay(p);
    }
}

bool checkEndCondition(const Player& p) {
    // End condition 1: Day > 14
    if (p.currentDay > 14) {
        cout << "\n====================================" << endl;
        cout << "          14 DAYS PASSED" << endl;
        cout << "====================================" << endl;
        cout << "Your total money: " << p.money << endl;
        cout << "Debt to repay:    " << DEBT_TARGET << endl;

        if (p.money >= DEBT_TARGET) {
            cout << "\n[ PERFECT ENDING ]" << endl;
            cout << "You paid off all debt and have savings!" << endl;
            cout << "You can start a new life in the town." << endl;
        } 
        else if (p.money >= DEBT_TARGET * 0.7) {
            cout << "\n[ NORMAL ENDING ]" << endl;
            cout << "You barely paid the debt." << endl;
            cout << "You stay in town and live an ordinary life." << endl;
        } 
        else {
            cout << "\n[ BAD ENDING ]" << endl;
            cout << "You cannot pay the debt." << endl;
            cout << "You are exiled from the town..." << endl;
        }
        return true;
    }

    // End condition 2: health <= 0
    if (p.health <= 0) {
        cout << "\nYou collapsed... Game Over." << endl;
        return true;
    }

    return false;
}