#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Cell.h"

#define POLE 5
#define RANGE 100 // Расстояние между клетками
#define WIDTH 4
#define SHIFT 100
#define WINDOW_HIGH 1280
#define WINDOW_WIDTH 720

using namespace std;

class Game
{
public:
	Game(sf::RenderWindow& window);
private:
	vector<sf::RectangleShape> ArrayPoleCol;
	vector<sf::RectangleShape> ArrayPoleRow;
	Cell ArrayPoints[POLE][POLE];
	vector<Player> Players;
};

