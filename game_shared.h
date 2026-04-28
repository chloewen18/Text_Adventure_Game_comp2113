#ifndef GAME_SHARED_H
#define GAME_SHARED_H

// 玩家结构体
struct Player {
    int countA;
    int health;          // 生命值 0-10
    int strength;        // 武力值
    int intelligence;    // 智力值
    int money;           // 钱
    int currentDay;      // 当前天数
    int actionPoints;    // 行动点
    int* backpack;       // 背包（动态数组）
    int backpackSize;    // 背包容量
    int itemCount;       // 道具数量
};

#endif
