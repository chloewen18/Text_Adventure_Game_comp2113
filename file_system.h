#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H
#include "game_shared.h"
#include <string>

// What it does: Writes player stats and dynamic array contents to a text file
// Inputs: Constant reference to Player struct, string filename
// Outputs: Creates or overwrites a text file
void saveGame(const Player& p, std::string filename);

// What it does: Reads data from text file, deletes old backpack, and creates a new one
// Inputs: Reference to Player struct, string filename
// Outputs: Returns true if load was successful, false if file missing or corrupted
bool loadGame(Player& p, std::string filename);

#endif