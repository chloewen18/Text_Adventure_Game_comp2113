// file.h
#ifndef FILE_H
#define FILE_H

#include "game_shared.h"

// 保存游戏
void saveGame(Player& p, const char* filename);

// 读取游戏
bool loadGame(Player& p, const char* filename);

// 显示存档信息
void showSaveInfo(const char* filename);

#endif