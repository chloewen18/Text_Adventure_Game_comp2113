#include "game_flow.h"
#include "player.h"
#include "action.h"
#include "file_system.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// Target debt to repay
const int DEBT_TARGET = 1000;

// Random event system (15% chance)
void triggerRandomEvent(Player& p) {
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
            p.money = max(0, p.money - 5);
            break;
        case 6:
            cout << "Lucky coin found! Next income doubled effect" << endl;
            addItem(p, 2);
            break;
        case 7:
            cout << "You rested well! You feel energized." << endl;
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

// Daily start: show summary + auto-save game
void startNewDay(Player& p) {
    showDayStartSummary(p);
    autoSave(p);
    cout << "\n====================================" << endl;
    cout << "          DAY " << p.currentDay << " START" << endl;
    cout << "====================================" << endl;
    cout << "Day " << p.currentDay << " has begun. Good luck, Mercenary!" << endl;
}

// Daily action loop (5 action points per day)
void processDay(Player& p) {
    p.actionPoints = 5;

    while (p.actionPoints > 0 && p.health > 0) {
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
                continue;
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
}

// Main game loop (14 days + save system)
void startGame(Player& p) {
    srand(time(0));
    initPlayer(p);
    showMainMenu();

    cout << "\nYour debt: 1000 gold. You have 14 days to pay it back." << endl;
    cout << "Press Enter to start the contract..." << endl;
    cin.get();
    cin.get();

    while (p.currentDay <= 14) {
        // Auto-save at the beginning of each day
        startNewDay(p);

        // Run daily actions
        processDay(p);

        // If player dies, reload morning save and replay the day
        if (p.health <= 0) {
            cout << "\nYou died during Day " << p.currentDay << "..." << endl;
            cout << "Loading morning save... Restarting the day." << endl;
            loadGame(p, "save.txt");
            continue;
        }

        // Proceed to next day
        p.currentDay++;
    }

    // Show final ending after 14 days
    checkEndCondition(p);
}

// Check game end conditions and show endings
bool checkEndCondition(const Player& p) {
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
