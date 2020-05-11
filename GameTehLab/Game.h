#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Cell.h"
#include "fstream"

#define POLE 3
#define RANGE 50 // Расстояние между клетками
#define WIDTH 2
#define SHIFT 200
#define WINDOW_HIGH 720
#define WINDOW_WIDTH 1280
#define TEXT_HEIGHT RANGE * 0.8
#define TEXT_STATUS_HEIGHT 100
#define BUTTON_WIDTH 400
#define BUTTON_HEIGHT 110
#define GET_CENTER(d) (((d * RANGE + SHIFT) + ((d+1) * RANGE + SHIFT)) / 2) 

#define IS_NETWORK false

using namespace std;

class Game
{
	vector<sf::RectangleShape> ArrayPoleCol;
	vector<sf::RectangleShape> ArrayPoleRow;
	Cell ArrayPoints[POLE][POLE];
	Player* Current_Player;
	Player Players[2];
	sf::RenderWindow* window;
public:
	Game();
	int CreateMenu(); // Создание меню
	void ClearPole(); // Очистка поля
	void CreateArea(); // Создание поля
	int DrawArea(); // Рисовка поля и изменений
	void SetPlayers(); // Установка игрков
	void StartGame(); // Начало игры
	void EndGame(); // Конеч игры
	void setStatus(string text, int height);
	void setButton(string text, int height);
	void CalculateScore(); // Подсчет очков
	void addNum(int &Origin, int Add);
};

