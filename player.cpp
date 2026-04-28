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
    cout << "\n===== 玩家状态 =====" << endl;
    cout << "血量：" << p.health << endl;
    cout << "武力：" << p.strength << endl;
    cout << "智力：" << p.intelligence << endl;
    cout << "金钱：" << p.money << endl;
    cout << "当前天数：" << p.currentDay << endl;
    cout << "行动点：" << p.actionPoints << endl;
    cout << "背包道具数：" << p.itemCount << endl;
}

// 添加道具
void addItem(Player& p, int itemId) {
    if (p.itemCount < p.backpackSize) {
        p.backpack[p.itemCount] = itemId;
        p.itemCount++;
        cout << "获得道具：";
        if (itemId == 1) cout << "回血药剂";
        if (itemId == 2) cout << "力量药剂";
        if (itemId == 3) cout << "智慧药剂";
        cout << endl;
    } else {
        cout << "背包已满！" << endl;
    }
}

// 使用道具（三个道具完整版）
void useItem(Player& p, int itemIndex) {
    if (itemIndex < 0 || itemIndex >= p.itemCount) {
        cout << "无效道具位置！" << endl;
        return;
    }

    int id = p.backpack[itemIndex];

    if (id == 1) {
        cout << "使用：回血药剂 → 血量 +2" << endl;
        p.health += 2;
        if (p.health > 10) p.health = 10;
    }
    else if (id == 2) {
        cout << "使用：力量药剂 → 武力 +1" << endl;
        p.strength += 1;
    }
    else if (id == 3) {
        cout << "使用：智慧药剂 → 智力 +1" << endl;
        p.intelligence += 1;
    }
    else {
        cout << "未知道具！" << endl;
    }

    // 移除道具
    for (int i = itemIndex; i < p.itemCount - 1; i++) {
        p.backpack[i] = p.backpack[i + 1];
    }
    p.itemCount--;
}

// 显示背包 + 直接在里面使用道具
void showBackpack(Player& p) {
    cout << "\n===== 背包 =====" << endl;
    if (p.itemCount == 0) {
        cout << "背包是空的" << endl;
        return;
    }

    for (int i = 0; i < p.itemCount; i++) {
        cout << i << ": ";
        int id = p.backpack[i];
        if (id == 1) cout << "回血药剂";
        if (id == 2) cout << "力量药剂";
        if (id == 3) cout << "智慧药剂";
        cout << endl;
    }

    int index;
    cout << "\n输入要使用的道具编号（-1 退出）：";
    cin >> index;

    if (index != -1) {
        useItem(p, index);
    }
}
