#include "player.h"
#include <iostream>
using namespace std;

// 初始化玩家
void initPlayer(Player& p) {
    p.countA = 0;
    p.health = 10;
    p.strength = 3;
    p.intelligence = 3;
    p.money = 0;
    p.currentDay = 1;
    p.actionPoints = 5;

    p.backpackSize = 10;
    p.itemCount = 0;
    p.backpack = new int[p.backpackSize];
}

// 销毁玩家，释放内存
void destroyPlayer(Player& p) {
    delete[] p.backpack;
    p.backpack = nullptr;
}

// 显示状态
void showStatus(const Player& p) {
    cout << "\n===== Player Status =====" << endl;
    cout << "Health：" << p.health << endl;
    cout << "Strength：" << p.strength << endl;
    cout << "Intelligence：" << p.intelligence << endl;
    cout << "Money：" << p.money << endl;
    cout << "Current Day：" << p.currentDay << endl;
    cout << "Action Points：" << p.actionPoints << endl;
    cout << "Item Count：" << p.itemCount << endl;
}

// 添加道具
void addItem(Player& p, int itemId) {
    if (p.itemCount < p.backpackSize) {
        p.backpack[p.itemCount] = itemId;
        p.itemCount++;
        cout << "Item Gained!";
        if (itemId == 1) cout << "1.Bandage (Health+1)";
        if (itemId == 2) cout << "2.Food (Strength+1)";
        if (itemId == 3) cout << "3.Book (Intelligence+1)";
        cout << endl;
    } else {
        cout << "Backpack Is Full!" << endl;
    }
}

// 使用道具（三个道具完整版）
void useItem(Player& p, int itemIndex) {
    if (itemIndex < 0 || itemIndex >= p.itemCount) {
        cout << "Invalid Item!" << endl;
        return;
    }

    int id = p.backpack[itemIndex];

    if (id == 1) {
        cout << "Bandage Used: Health+1" << endl;
        p.health += 2;
        if (p.health > 10) p.health = 10;
    }
    else if (id == 2) {
        cout << "Food Used: Strength+1" << endl;
        p.strength += 1;
    }
    else if (id == 3) {
        cout << "Bood Used: Intelligence+1" << endl;
        p.intelligence += 1;
    }
    else {
        cout << "Unknown Item!" << endl;
    }

    // 移除道具
    for (int i = itemIndex; i < p.itemCount - 1; i++) {
        p.backpack[i] = p.backpack[i + 1];
    }
    p.itemCount--;
}

// 显示背包 + 直接在里面使用道具
void showBackpack(Player& p) {
    cout << "\n===== Backpack =====" << endl;
    if (p.itemCount == 0) {
        cout << "Backpack Is Empty" << endl;
        return;
    }

    for (int i = 0; i < p.itemCount; i++) {
        cout << i << ": ";
        int id = p.backpack[i];
        if (id == 1) cout << "1.Bandage (Health+1)";
        if (id == 2) cout << "2.Food (Strength+1)";
        if (id == 3) cout << "3.Book (Intelligence+1)";
        cout << endl;
    }

    int index;
    cout << "\nType In Item Number（-1 Exit）：";
    cin >> index;

    if (index != -1) {
        useItem(p, index);
    }
}
