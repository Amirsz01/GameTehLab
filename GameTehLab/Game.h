#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Cell.h"

#define POLE 5
#define RANGE 50 // Расстояние между клетками
#define WIDTH 4
#define SHIFT 100
#define WINDOW_HIGH 1280
#define WINDOW_WIDTH 720
#define TEXT_HEIGHT RANGE * 0.8
#define GET_CENTER(d) (((d * RANGE + SHIFT) + ((d+1) * RANGE + SHIFT)) / 2) 

#define IS_NETWORK false

using namespace std;

class Game
{
public:
	Game();
	void DrawArea();
private:
	bool EmptyPoints; // Пустые клетки
	vector<sf::RectangleShape> ArrayPoleCol;
	vector<sf::RectangleShape> ArrayPoleRow;
	Cell ArrayPoints[POLE][POLE];
	Player* Current_Player;
	sf::RenderWindow *window;
};

