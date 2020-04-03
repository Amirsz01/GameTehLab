#include "Game.h"

Game::Game()
{
	EmptyPoints = true;
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_HIGH, WINDOW_WIDTH), "SFML GAME!");
	for (size_t i = 0; i < POLE+1; i++)
	{
		ArrayPoleCol.push_back(sf::RectangleShape(sf::Vector2f(RANGE * POLE, WIDTH)));
		ArrayPoleRow.push_back(sf::RectangleShape(sf::Vector2f(WIDTH, RANGE * POLE)));
		ArrayPoleCol[i].setPosition(0 + SHIFT, i * RANGE + SHIFT);
		ArrayPoleRow[i].setPosition(i * RANGE + SHIFT, 0 + SHIFT);
	}
	this->DrawArea();
	Player A;
	A._SIDE = ZERO;
	Player B;
	B._SIDE = ONE;
	Current_Player = &A;
	while (this->window->isOpen())
	{
		sf::Event event;
		sf::Vector2i mouseCord;
		int ind_col, ind_row;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();
			if (event.type == sf::Event::MouseButtonPressed)//если нажата клавиша мыши
			{
				if (event.key.code == sf::Mouse::Left)//а именно левая
				{
					mouseCord = sf::Mouse::getPosition(*this->window);
					if (mouseCord.x >= SHIFT && mouseCord.x <= WINDOW_WIDTH && mouseCord.y >= SHIFT && mouseCord.y <= WINDOW_HIGH)//если клик в области экрана
					{
						ind_col = (mouseCord.x - SHIFT) / RANGE;
						ind_row = (mouseCord.y - SHIFT) / RANGE;
						if (ind_col >= 0 && ind_col < POLE && ind_row >= 0 && ind_row < POLE)
						{
							if (!ArrayPoints[ind_col][ind_row].Put(*Current_Player))
							{
								DrawArea();
								Current_Player->_SIDE == ZERO ? Current_Player = &B : Current_Player = &A;
							}
						}
					}
				}
			}
		}
	}
}


void Game::DrawArea()
{
	sf::Font font;
	if (!font.loadFromFile("Equal-Regular.otf"))
	{
		cout << "GG" << endl;
		return;
	}
	sf::Text text;
	text.setFont(font);
	text.setCharacterSize(TEXT_HEIGHT); // in pixels, not points!
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	for (size_t i = 0; i < POLE + 1; ++i)
	{
		this->window->draw(ArrayPoleCol[i]);
		this->window->draw(ArrayPoleRow[i]);
	}
	EmptyPoints = false;
	for (size_t i = 0; i < POLE; ++i)
	{
		for (size_t j = 0; j < POLE; ++j)
		{
			if (ArrayPoints[i][j].value == -1)
			{
				EmptyPoints = true;
				continue;
			}
			text.setString(to_string(ArrayPoints[i][j].value));
			text.setPosition(GET_CENTER(i) - (text.getLocalBounds().width / 2) , GET_CENTER(j) - (TEXT_HEIGHT / 1.7));
			this->window->draw(text);
		}
	}
	this->window->display();
	if (!EmptyPoints)
	{
		cout << "END GAME" << endl;
	}
}