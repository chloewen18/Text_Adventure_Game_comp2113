#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <limits>
using namespace std;

struct Player {
    int health;
    int strength;
    int intelligence;
    int money;
    int currentDay;
    int actionPoints;
    int* backpack;
    int backpackSize;
    int itemCount;
};

void initPlayer(Player& p) {
    p.health = 10;
    p.strength = 2;
    p.intelligence = 2;
    p.money = 0;
    p.currentDay = 1;
    p.actionPoints = 5;
    p.backpack = new int[5];
    p.backpackSize = 5;
    p.itemCount = 0;
}

void destroyPlayer(Player& p) { delete[] p.backpack; }

void showStatus(const Player& p) {
    cout << "\n=== Status ===" << endl;
    cout << "HP: " << p.health << endl;
    cout << "Strength: " << p.strength << endl;
    cout << "Intelligence: " << p.intelligence << endl;
    cout << "Money: " << p.money << endl;
}

void addItem(Player& p, int id) {
    if (p.itemCount < p.backpackSize)
        p.backpack[p.itemCount++] = id;
}

void showBackpack(const Player& p) {
    cout << "[Backpack] Empty" << endl;
}

void hunt(Player& p) {
    cout << "Hunt success! +20 money" << endl;
    p.money += 20;
    p.strength++;
}

void helpVillager(Player& p) {
    cout << "Help villager! +15 money" << endl;
    p.money += 15;
    p.intelligence++;
}

void showMainMenu() {
    cout << "=== 14 Days Survival: Pay 1000 Debt ===" << endl;
}

const int DEBT_TARGET = 1000;

void showGameIntro() {
    cout << "\n==============================================\n";
    cout << "          14 DAYS SURVIVAL GUIDE\n";
    cout << "==============================================\n";
    cout << "You owe 1000 gold to the lender.\n";
    cout << "You have ONLY 14 DAYS to pay it back.\n";
    cout << "If you fail, you will be exiled from town.\n\n";
    cout << "Each day you have 5 ACTION POINTS.\n";
    cout << "1) Hunt\n2) Help Villager\n3) Backpack\n4) End Day\n";
    cout << "==============================================\n";
}

void triggerRandomEvent(Player& p) {
    int chance = rand() % 100;
    if (chance >= 15) return;

    int eventId = rand() % 10;
    cout << "\n[ RANDOM EVENT! ]" << endl;

    switch (eventId) {
        case 0: cout << "You found a money bag! +30 money\n"; p.money += 30; break;
        case 1: cout << "Villager gave you herb! Item obtained\n"; addItem(p,1); break;
        case 2: cout << "Beat a beast! Strength +1\n"; p.strength +=1; break;
        case 3: cout << "Helped traveler! Intelligence +1\n"; p.intelligence +=1; break;
        case 4: cout << "Found supplies! AP +1\n"; p.actionPoints +=1; break;
        case 5: cout << "Bad weather! Money -5\n"; p.money = max(0,p.money-5); break;
        case 6: cout << "Lucky coin! Item obtained\n"; addItem(p,2); break;
        case 7: cout << "You rested well!\n"; break;
        case 8: cout << "Found backpack! Slot +1\n"; p.backpackSize = min(10,p.backpackSize+1); break;
        case 9: cout << "Charity received! +15 money\n"; p.money +=15; break;
    }
}

void clearCin() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}
void processDay(Player& p) {
    p.actionPoints = 5;
    cout << "\n==================== DAY " << p.currentDay << " ====================\n";

    while (p.actionPoints > 0) {
        showStatus(p);
        cout << "\nAP: " << p.actionPoints << endl;
        cout << "1:Hunt  2:Help  3:Bag  4:End\nChoice: ";

        int c;
        cin >> c;
        clearCin();

        if (c == 4) break;

        if (c == 1) hunt(p);
        else if (c == 2) helpVillager(p);
        else if (c == 3) { showBackpack(p); continue; }
        else {
            cout << "Invalid input!\n";
            continue;
        }

        p.actionPoints--;
        triggerRandomEvent(p);
    }

    cout << "\nDay " << p.currentDay << " END\n";
    p.currentDay++;
}

bool checkEndCondition(const Player& p) {
    if (p.currentDay > 14) {
        cout << "\n==================== 14 DAYS OVER ====================\n";
        cout << "Your money: " << p.money << " | Debt: 1000\n";
        if (p.money >= 1000) cout << "[PERFECT ENDING]\n";
        else if (p.money >= 700) cout << "[NORMAL ENDING]\n";
        else cout << "[BAD ENDING]\n";
        return true;
    }
    return false;
}

void startGame(Player& p) {
    srand(time(0));
    initPlayer(p);
    showMainMenu();
    showGameIntro();

    cout << "\nPress ENTER to start...";
    cin.get();

    while (!checkEndCondition(p)) {
        processDay(p);
    }

    destroyPlayer(p);
}

int main() {
    Player p;
    startGame(p);
    return 0;
}
