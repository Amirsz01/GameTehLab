#pragma once
enum Side
{
	NONE = -1,
	ZERO,
	ONE
};

class Player
{
public:
	Player();
	int Score;
	Side _SIDE;
	bool Computer;
};