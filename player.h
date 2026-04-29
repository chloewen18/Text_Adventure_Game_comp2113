#ifndef PLAYER_H
#define PLAYER_H

#include "game_shared.h"

// 初始化玩家
void initPlayer(Player& p);

// 销毁玩家（释放背包内存）
void destroyPlayer(Player& p);

// 显示玩家状态
void showStatus(const Player& p);

// 添加道具到背包
void addItem(Player& p, int itemId);

// 使用道具
void useItem(Player& p, int itemIndex);

// 显示背包
void showBackpack(Player& p);

#endif
