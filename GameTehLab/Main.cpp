﻿#include "Game.h"
/*
* Игра «чет-нечет». Два игрока, «нечетный» и «четный», по очереди ставят единицы и нули в незанятые позиции поля N на N (размер поля задается пользователем). 
* Каждый из игроков может ставить 1 или 0 в произвольную свободную позицию, тем самым занимая ее. Игра продолжается до заполнения всех позиций. 
* После этого суммируются числа вдоль каждой строки, каждого столбца и главных диагоналей. Число нечетных сумм сравнивается с числом четных сумм. 
* Если «Число нечетных сумм > Числа четных сумм», выигрывает «нечетный»; иначе выигрывает «четный»; если числа равны, результат считается ничейным. 
* Второй игрок может быть сервером.
*/

int main()
{
	setlocale(LC_ALL, "Rus");
	Game app;
	return 0;
}