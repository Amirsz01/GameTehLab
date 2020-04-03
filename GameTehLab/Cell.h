#pragma once
#include "Player.h"

class Cell
{
public:
	int value;
	bool changed;
	Cell();
	int Put(Player &_Player);
};