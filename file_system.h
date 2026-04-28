#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include "game_shared.h"
#include <string>

void saveGame(const Player& p, std::string filename);
bool loadGame(Player& p, std::string filename);

void autoSave(const Player& p);

void showDayStartSummary(const Player& p);

#endif
