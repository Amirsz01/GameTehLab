#pragma once
#include "Player.h"

class Cell
{
public:
	int value;
	bool changed;
	Cell();
	void Restart();
	int Put(Player &_Player);
};