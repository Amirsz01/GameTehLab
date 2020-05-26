#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Cell.h"
#include "Defines.h"
#include "fstream"
#include <string>

#define IS_NETWORK false

using namespace std;

class Game
{
	/*	Вектора для хранения данных	*/
	vector<sf::RectangleShape> ArrayPoleCol;
	vector<sf::RectangleShape> ArrayPoleRow;
	vector<Cell> ArrayPoints;
	Player* Current_Player;
	Player Players[2];
	sf::RenderWindow* window;

	/*	Настройки поля	*/
	int NumPoints; // Число клеток
	int _Range; // Расстояние между клетками
	int _Thickness; // Толщина стенок
	int _Shift; // Смещение
	int _TextHeight; //Высота текста
public:
	Game();

	/*	Пошаговое создание игры	*/
	int LoadConfig(); // Загрузить конфиг
	int CreateMenu(); // Создание меню
	void ClearPole(); // Очистка поля
	void CreateArea(); // Создание поля
	int DrawArea(); // Рисовка поля и изменений
	void SetPlayers(); // Установка игрков
	void StartGame(); // Начало игры
	void EndGame(); // Конец игры

	/*	Вывод текста	*/
	void setStatus(string text, int height);
	void setButton(string text, int height);

	/*	Подсчет очков	*/
	void CalculateScore(); // Подсчет очков
	void addNum(int &Origin, int Add);

	/*	Расчет центра в клетке	*/
	int GET_CENTER(int point)
	{
		return ((point * _Range + _Shift) + ((point + 1) * _Range + _Shift)) / 2;
	}
	/*	Побочные методы	*/
	void SaveConfig(int Param1 = 4, int Param2 = 50, int Param3 = 2, int Param4 = 100);
};

