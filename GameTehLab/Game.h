#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Player.h"
#include "Cell.h"
#include "Defines.h"
#include "fstream"

#define IS_NETWORK false

using namespace std;

class Game
{
	/*	������� ��� �������� ������	*/
	vector<sf::RectangleShape> ArrayPoleCol;
	vector<sf::RectangleShape> ArrayPoleRow;
	vector<Cell> ArrayPoints;
	Player* Current_Player;
	Player Players[2];
	sf::RenderWindow* window;

	/*	��������� ����	*/
	int NumPoints; // ����� ������
	int _Range; // ���������� ����� ��������
	int _Thickness; // ������� ������
	int _Shift; // ��������
	int _TextHeight; //������ ������
public:
	Game();

	/*	��������� �������� ����	*/
	int CreateMenu(); // �������� ����
	void ClearPole(); // ������� ����
	void CreateArea(); // �������� ����
	int DrawArea(); // ������� ���� � ���������
	void SetPlayers(); // ��������� ������
	void StartGame(); // ������ ����
	void EndGame(); // ����� ����

	/*	����� ������	*/
	void setStatus(string text, int height);
	void setButton(string text, int height);

	/*	������� �����	*/
	void CalculateScore(); // ������� �����
	void addNum(int &Origin, int Add);

	/*	������ ������ � ������	*/
	int GET_CENTER(int point)
	{
		return ((point * _Range + _Shift) + ((point + 1) * _Range + _Shift)) / 2;
	}
};

