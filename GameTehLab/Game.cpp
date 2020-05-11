#include "Game.h"

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HIGH), "BEST GAME IN THE WORLD");
	switch ((CreateMenu()))
	{
	case 0:
		SetPlayers();
		CreateArea();
		DrawArea();
		StartGame();
		break;
	case 1:
		break;
	default:
		break;
	}
}

int Game::CreateMenu()
{
	ifstream menu("Menu.txt");
	if (!menu.is_open())
	{
		cout << "Failed open file Menu.txt" << endl;
		return -1;
	}
	string text;
	int height = 0;
	while (!menu.eof())
	{
		getline(menu, text);
		setButton(text, height);
		height += BUTTON_HEIGHT * 1.2;
	}
	window->display();
	while (this->window->isOpen())
	{
		sf::Event event;
		sf::Vector2i mouseCord;
		int ind_col, ind_row;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();
			if (event.type == sf::Event::MouseButtonPressed)// если нажата клавиша мыши
			{
				if (event.key.code == sf::Mouse::Left) // а именно левая
				{
					mouseCord = sf::Mouse::getPosition(*this->window);
					if (mouseCord.x <= WINDOW_WIDTH && mouseCord.y <= WINDOW_HIGH && mouseCord.x >= 0 && mouseCord.y >= 0) // если клик в области экрана
					{
						if (mouseCord.x >= WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2 && mouseCord.x < WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2 + BUTTON_WIDTH) // если клик в области кнопок
						{
							int _range = (BUTTON_HEIGHT - TEXT_STATUS_HEIGHT) / 2 - WIDTH*2;
							int _correctCord = (mouseCord.y - _range/2 - WIDTH) % (int(BUTTON_HEIGHT*1.2));
							int numButton = (mouseCord.y - _range/2 - WIDTH) / (BUTTON_HEIGHT * 1.2);
							if (_correctCord > 0 && _correctCord < BUTTON_HEIGHT) // если клик в области кнопок
							{
								switch (numButton)
								{
								case 0:
									return 0;
								case 2:
									this->window->close();
									return 2;
									break;
								default:
									break;
								}
							}
						}
					}
				}
			}
		}
	}
}

void Game::ClearPole()
{
	for (size_t i = 0; i < POLE; ++i)
	{
		for (size_t j = 0; j < POLE; ++j)
		{
			ArrayPoints[i][j].Restart();
		}
	}
}

void Game::CreateArea()
{
	ClearPole();
	for (size_t i = 0; i < POLE + 1; i++)
	{
		ArrayPoleCol.push_back(sf::RectangleShape(sf::Vector2f(RANGE * POLE, WIDTH)));
		ArrayPoleRow.push_back(sf::RectangleShape(sf::Vector2f(WIDTH, RANGE * POLE)));
		ArrayPoleCol[i].setPosition(0 + SHIFT, i * RANGE + SHIFT);
		ArrayPoleRow[i].setPosition(i * RANGE + SHIFT, 0 + SHIFT);
	}
}


int Game::DrawArea()
{
	this->window->clear();
	sf::Font font;
	if (!font.loadFromFile("Equal-Regular.otf"))
	{
		cout << "GG" << endl;
		return -1;
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
	bool EmptyPoints = false;
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
	if (!EmptyPoints)
	{
		cout << "END GAME" << endl;
		return 2;
	}
	else
	{
		this->window->display();
	}
}

void Game::SetPlayers()
{
	Players[0]._SIDE = ZERO;
	Players[1]._SIDE = ONE;
	Players[0].Score = 0;
	Players[1].Score = 0;
	if (IS_NETWORK)
	{
		Players[1].Computer = true;
	}
	Current_Player = &Players[0];
}

void Game::StartGame()
{
	while (this->window->isOpen())
	{
		sf::Event event;
		sf::Vector2i mouseCord;
		int ind_col, ind_row;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();
			if (event.type == sf::Event::MouseButtonPressed)// если нажата клавиша мыши
			{
				if (event.key.code == sf::Mouse::Left) // а именно левая
				{
					mouseCord = sf::Mouse::getPosition(*this->window);
					if (mouseCord.x >= SHIFT && mouseCord.x <= WINDOW_WIDTH && mouseCord.y >= SHIFT && mouseCord.y <= WINDOW_HIGH) // если клик в области экрана
					{
						ind_col = (mouseCord.x - SHIFT) / RANGE;
						ind_row = (mouseCord.y - SHIFT) / RANGE;
						if (ind_col >= 0 && ind_col < POLE && ind_row >= 0 && ind_row < POLE)
						{
							if (!ArrayPoints[ind_col][ind_row].Put(*Current_Player))
							{
								if (DrawArea() == 2)
								{
									this->EndGame();
									break;
								}
								Current_Player->_SIDE == ZERO ? Current_Player = &Players[1] : Current_Player = &Players[0];
							}
						}
					}
				}
			}
		}
		if (IS_NETWORK && Current_Player->Computer)
		{
			bool GO_BREAK = false;
			for (size_t i = POLE - 1; i >= 0; i--)
			{
				for (size_t j = POLE - 1; j >= 0; j--)
				{
					if (!ArrayPoints[i][j].changed)
						if (!ArrayPoints[i][j].Put(*Current_Player))
						{
							if (DrawArea() == 2)
							{
								this->EndGame();
								continue;
							}
							Current_Player->_SIDE == ZERO ? Current_Player = &Players[1] : Current_Player = &Players[0];
							GO_BREAK = true;
							break;
						}
				}
				if (GO_BREAK)
				{
					break;
				}
			}
		}
	}
}

void Game::EndGame()
{
	CalculateScore();
	setStatus("END GAME", 0);
	this->window->display();
	SetPlayers();
	ClearPole();
	system("pause");
	DrawArea();
}


void Game::setStatus(string text, int height)
{
	sf::Font font;
	if (!font.loadFromFile("Equal-Regular.otf"))
	{
		cout << "GG" << endl;
		return;
	}
	sf::Text status;
	status.setFont(font);
	status.setCharacterSize(100);
	status.setFillColor(sf::Color::White);
	status.setStyle(sf::Text::Bold);
	status.setString(text);
	status.setPosition(SHIFT + (POLE * RANGE / 2)  - status.getGlobalBounds().width / 2, height);
	this->window->draw(status);
}

void Game::setButton(string text, int height)
{
	sf::Font font;
	if (!font.loadFromFile("Equal-Regular.otf"))
	{
		cout << "GG" << endl;
		return;
	}
	sf::Text button;
	button.setFont(font);
	button.setCharacterSize(TEXT_STATUS_HEIGHT);
	button.setFillColor(sf::Color::White);
	button.setStyle(sf::Text::Bold);
	button.setString(text);
	button.setPosition(WINDOW_WIDTH / 2 - button.getGlobalBounds().width / 2, height);
	sf::RectangleShape Frame(sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT));
	Frame.setOutlineThickness(WIDTH);
	Frame.setFillColor(sf::Color(0, 0, 0, 0));
	Frame.setPosition(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, ((BUTTON_HEIGHT - TEXT_STATUS_HEIGHT)/2) + height);
	this->window->draw(Frame);
	this->window->draw(button);
}

void Game::CalculateScore()
{
	int score[POLE * 2 + 2];
	for (size_t i = 0; i < POLE * 2 + 2; i++)
	{
		score[i] = 0;
	}
	for (size_t i = 0; i < POLE; i++)
	{
		for (size_t j = 0; j < POLE; j++)
		{
			addNum(score[j+POLE], ArrayPoints[i][j].value);
			addNum(score[i], ArrayPoints[i][j].value);
			if (i == j)
				addNum(score[POLE*2], ArrayPoints[i][j].value);
			if (i + j + 1 == POLE)
				addNum(score[POLE * 2 + 1], ArrayPoints[i][j].value);
		}
	}
	for (size_t i = 0; i < POLE * 2 + 2; i++)
	{
		if (score[i] % 2 == 0)
		{
			if (Players[0]._SIDE == 0)
			{
				Players[0].Score++;
			}
			else
			{
				Players[1].Score++;
			}
		}
		else
		{
			if (Players[0]._SIDE == 1)
			{
				Players[0].Score++;
			}
			else
			{
				Players[1].Score++;
			}
		}
	}
	Players[0].Score > Players[1].Score ? setStatus("PLAYER 0 WIN", (POLE * RANGE + SHIFT) / 2) : Players[1].Score != Players[0].Score ? setStatus("PLAYER 1 WIN", (POLE * RANGE + SHIFT) / 2) : setStatus("GAME DRAW", (POLE * RANGE + SHIFT) / 2);
}

void Game::addNum(int& Origin, int Add)
{
	Origin *= 10;
	Origin += Add;
}
