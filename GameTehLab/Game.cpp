#include "Game.h"

Game::Game(sf::RenderWindow& window)
{

	for (size_t i = 0; i < POLE + 1; ++i)
	{
		ArrayPoleCol.push_back(sf::RectangleShape(sf::Vector2f(RANGE * POLE, WIDTH)));
		ArrayPoleRow.push_back(sf::RectangleShape(sf::Vector2f(WIDTH, RANGE * POLE)));
		ArrayPoleCol[i].move(0 + SHIFT, i * RANGE + SHIFT);
		ArrayPoleRow[i].move(i * RANGE + SHIFT, 0 + SHIFT);
		window.draw(ArrayPoleCol[i]);
		window.draw(ArrayPoleRow[i]);
	}
	window.display();
	sf::Event event;
	sf::Vector2i mouseCord;
	int ind_col, ind_row;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::MouseButtonPressed)//если нажата клавиша мыши
		{
			if (event.key.code == sf::Mouse::Left)//а именно левая
			{
				mouseCord = sf::Mouse::getPosition(window);
				if (mouseCord.x >= SHIFT && mouseCord.x <= WINDOW_WIDTH && mouseCord.y >= SHIFT && mouseCord.y <= WINDOW_HIGH)//если клик в области экрана
				{
					ind_col = (mouseCord.x - SHIFT) / RANGE;
					ind_row = (mouseCord.y - SHIFT) / RANGE;
					if (ind_col >= 0 && ind_col < POLE && ind_row >= 0 && ind_row < POLE)
						cout << ind_col << " : " << ind_row << endl;//выводим в консоль сообщение об этом
				}
			}
		}
	}
}