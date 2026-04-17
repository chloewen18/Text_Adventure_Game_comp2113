#ifndef GAME_FLOW_H
#define GAME_FLOW_H

#include "game_shared.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

// Trigger a random event after each action
void triggerRandomEvent(Player& p);

// Handle one full day (5 action points)
void processDay(Player& p);

// Main game loop (Day 1 ~ Day 14)
void startGame(Player& p);

// Check if game should end & show ending
bool checkEndCondition(const Player& p);

#endif