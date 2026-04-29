#include "game_flow.h"
#include "player.h"
#include "action.h"
#include "file_system.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

// Target debt to repay (core game rule)
const int DEBT_TARGET = 1000;
const string SAVE_FILE = "save.txt"; // Save file path

// Random event system (15% trigger chance)
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

// Manual save function
void saveGameData(Player& p) {
    ofstream saveFile(SAVE_FILE);
    if (!saveFile) {
        cout << "Error: Failed to save game!" << endl;
        return;
    }

    // Save all player stats
    saveFile << p.health << endl;
    saveFile << p.strength << endl;
    saveFile << p.intelligence << endl;
    saveFile << p.money << endl;
    saveFile << p.currentDay << endl;
    saveFile << p.actionPoints << endl;
    saveFile << p.backpackSize << endl;
    saveFile << p.itemCount << endl;

    // Save backpack items
    for (int i = 0; i < p.itemCount; i++) {
        saveFile << p.backpack[i] << " ";
    }

    saveFile.close();
    cout << "\n✅ Game saved to " << SAVE_FILE << endl;
}

// Daily start (replaced showDayStartSummary with simple status)
void startNewDay(Player& p) {
    // Show day start status (instead of unimplemented showDayStartSummary)
    cout << "\n====================================" << endl;
    cout << "          DAY " << p.currentDay << " START" << endl;
    cout << "====================================" << endl;
    cout << "Current Status:" << endl;
    cout << "Health: " << p.health << " | Strength: " << p.strength << " | Intelligence: " << p.intelligence << endl;
    cout << "Money: " << p.money << " | Action Points: 5 (reset)" << endl;
    cout << "------------------------------------" << endl;
    
    // Auto-save at day start
    saveGameData(p);
    cout << "Day " << p.currentDay << " has begun. Good luck, Mercenary!" << endl;
}

// Daily action loop (5 action points per day)
void processDay(Player& p) {
    p.actionPoints = 5; // Reset action points daily

    while (p.actionPoints > 0 && p.health > 0) {
        cout << "\nRemaining Action Points: " << p.actionPoints << endl;
        cout << "1. Hunt Monster (Earn money + Strength)" << endl;
        cout << "2. Help Villager (Earn money + Intelligence)" << endl;
        cout << "3. Show Backpack (No AP cost)" << endl;
        cout << "4. End Today" << endl;
        cout << "Your choice: ";

        int choice;
        cin >> choice;

        if (choice == 4) {
            cout << "\nYou decide to rest early. Ending Day " << p.currentDay << "." << endl;
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
                continue; // No AP cost
            default:
                cout << "Invalid input! Please enter 1-5." << endl;
                continue;
        }

        p.actionPoints--;
        triggerRandomEvent(p);
    }

    // Day end message
    cout << "\n====================================" << endl;
    cout << "          DAY " << p.currentDay << " END" << endl;
    cout << "====================================" << endl;
}

// Main game loop (5 days + working save/load)
void startGame(Player& p) {
    srand(time(0)); // Initialize random seed
    initPlayer(p);  // Initialize player stats
    showMainMenu(); // Show game main menu

    // Game intro (English only)
    cout << "\n GAME INTRO" << endl;
    cout << "You owe 1000 gold to the town lender. You have 5 DAYS to repay it." << endl;
    cout << "Fail, and you will be exiled from the town forever." << endl;
    cout << "Press Enter to start your journey..." << endl;
    cin.get();
    cin.get();

    // 5-day core loop
    while (p.currentDay <= 5) {
        // Start day: show status + auto-save
        startNewDay(p);

        // Run daily actions
        processDay(p);

        // If player dies: reload save and retry the day
        if (p.health <= 0) {
            cout << "\n💀 You died during Day " << p.currentDay << "!" << endl;
            cout << "Loading the morning save to retry this day..." << endl;
            loadGameData(p); // Reload auto-save
            continue; // Restart the same day (no day increment)
        }

        // Proceed to next day
        p.currentDay++;
    }

    // Show final ending after 5 days
    checkEndCondition(p);
}

// Check end conditions and show endings (100% English)
bool checkEndCondition(const Player& p) {
    cout << "\n====================================" << endl;
    cout << "          5 DAYS COMPLETED" << endl;
    cout << "====================================" << endl;
    cout << "Final Money: " << p.money << " | Required Debt: " << DEBT_TARGET << endl;
    cout << "------------------------------------" << endl;

    if (p.money >= DEBT_TARGET) {
        cout << "[✨ PERFECT ENDING ]" << endl;
        cout << "You paid off all debt and have extra savings!" << endl;
        cout << "The town welcomes you, and you start a new, stable life." << endl;
    } 
    else if (p.money >= DEBT_TARGET * 0.7) {
        cout << "[🟡 NORMAL ENDING ]" << endl;
        cout << "You barely repaid the debt (70%+ of the total)." << endl;
        cout << "You stay in the town but live a simple, ordinary life." << endl;
    } 
    else {
        cout << "[🔴 BAD ENDING ]" << endl;
        cout << "You failed to repay enough debt (less than 70%)." << endl;
        cout << "You are exiled from the town—your fate is unknown." << endl;
    }
    return true;
}
