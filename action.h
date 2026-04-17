#ifndef ACTION_H
#define ACTION_H
#include "game_shared.h"

// What it does: Sets initial attributes based on selected difficulty level
// Inputs: Reference to Player, integer representing difficulty (1=Easy, 2=Normal, 3=Hard)
// Outputs: None (Modifies initial strength/health)
void setDifficulty(Player& p, int diffLevel);

// What it does: Calculates combat success based on strength, handles health loss and money gain
// Inputs: Reference to Player
// Outputs: None (Modifies health, money, actionPoints)
void hunt(Player& p);

// What it does: Calculates begging/working success based on intelligence, awards money
// Inputs: Reference to Player
// Outputs: None (Modifies money, actionPoints)
void helpVillager(Player& p);

#endif