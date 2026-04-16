#include "player.h"
#include <iostream>
using namespace std;

// 1. 初始化玩家
void initPlayer(Player& p) {
    p.health = 10;
    p.strength = 3;
    p.intelligence = 3;
    p.money = 0;
    p.currentDay = 1;
    p.actionPoints = 5;

    // 背包动态内存
    p.backpackSize = 10;
    p.itemCount = 0;
    p.backpack = new int[p.backpackSize];
}

// 2. 销毁玩家，释放内存
void destroyPlayer(Player& p) {
    delete[] p.backpack;
    p.backpack = nullptr;
}

// 3. 显示状态
void showStatus(const Player& p) {
    cout << "\n===== 玩家状态 =====" << endl;
    cout << "血量：" << p.health << endl;
    cout << "武力：" << p.strength << endl;
    cout << "智力：" << p.intelligence << endl;
    cout << "金钱：" << p.money << endl;
    cout << "当前天数：" << p.currentDay << endl;
    cout << "行动点：" << p.actionPoints << endl;
    cout << "背包道具数：" << p.itemCount << endl;
}

// 4. 添加道具
void addItem(Player& p, int itemId) {
    if (p.itemCount < p.backpackSize) {
        p.backpack[p.itemCount] = itemId;
        p.itemCount++;
        cout << "获得道具 ID：" << itemId << endl;
    } else {
        cout << "背包已满！" << endl;
    }
}

// 5. 使用道具
void useItem(Player& p, int itemIndex) {
    if (itemIndex < 0 || itemIndex >= p.itemCount) {
        cout << "无效道具位置！" << endl;
        return;
    }

    int id = p.backpack[itemIndex];
    cout << "使用道具：" << id << endl;

    // 道具效果样例代码，具体效果待定
    if (id == 1) {
        p.health += 2;
        if (p.health > 10) p.health = 10;
        cout << "回血 +2" << endl;
    } else if (id == 2) {
        p.strength += 1;
        cout << "武力 +1" << endl;
    }

    // 删掉这个道具（后面往前挪）
    for (int i = itemIndex; i < p.itemCount - 1; i++) {
        p.backpack[i] = p.backpack[i + 1];
    }
    p.itemCount--;
}

// 6. 显示背包
void showBackpack(const Player& p) {
    cout << "\n===== 背包 =====" << endl;
    if (p.itemCount == 0) {
        cout << "背包是空的" << endl;
        return;
    }
    for (int i = 0; i < p.itemCount; i++) {
        cout << i << ": 道具" << p.backpack[i] << endl;
    }
}