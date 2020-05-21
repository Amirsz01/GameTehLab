#include "Game.h"

Game::Game()
{
	this->window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HIGH), "BEST GAME IN THE WORLD");
	LoadConfig();
	CreateMenu();
}

int Game::LoadConfig()
{
	ifstream config(CONFIG_FILE);
	string param;
	int value;
	if (!config.is_open())
	{
		config.close();
		SaveConfig();
		LoadConfig();
	}
	while (!config.eof())
	{
		config >> param >> value;
		if (param == "Pole")
		{
			NumPoints = value;
		}
		if (param == "Range")
		{
			_Range = value;
			_TextHeight = _Range * 0.8;
		}
		if (param == "Thickness")
		{
			_Thickness = value;
		}
		if (param == "Shift")
		{
			_Shift = value;
		}
	}
	config.close();
	return 0;
}

int Game::CreateMenu()
{
	this->window->clear();
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
		int iMenuValue;
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
							int _range = (BUTTON_HEIGHT - TEXT_STATUS_HEIGHT) / 2 - _Thickness * 2;
							int _correctCord = (mouseCord.y - _range/2 - _Thickness) % (int(BUTTON_HEIGHT*1.2));
							int numButton = (mouseCord.y - (_range/2) - _Thickness) / int(BUTTON_HEIGHT * 1.2);
							if (_correctCord > 0 && _correctCord < BUTTON_HEIGHT) // если клик в области кнопок
							{
								switch (numButton)
								{
								case 0:
									system("CLS");
									SetPlayers();
									CreateArea();
									DrawArea();
									StartGame();
									break;
								case 1:
									system("CLS");
									cout << "***************************" << endl
										<< "Меню настроек поля" << endl
										<< "***************************" << endl
										<< "[1] Установить размер поля" << endl
										<< "[2] Установить размер клетки" << endl
										<< "[3] Установить толщину границы клетки" << endl
										<< "[4] Установить смещение" << endl
										<< "Выбор: ";
									cin >> iMenuValue;
									switch (iMenuValue)
									{
									case 1:
										cout << "Значение параметра: " << NumPoints << endl
											<< "Новое значение: ";
										cin >> NumPoints;
										break;
									case 2:
										cout << "Значение параметра: " << _Range << endl
											<< "Новое значение: ";
										cin >> _Range;
										_TextHeight = _Range * 0.8;
										break;
									case 3:
										cout << "Значение параметра: " << _Thickness << endl
											<< "Новое значение: ";
										cin >> _Thickness;
										break;
									case 4:
										cout << "Значение параметра: " << _Shift << endl
											<< "Новое значение: ";
										cin >> _Shift;
										break;
									default:
										break;
									}
									system("CLS");
									cout << "Значение установлено!" << endl;
									SaveConfig(NumPoints, _Range, _Thickness, _Shift);
									break;
								case 2:
									this->window->close();
									return 2;
								default:
									return -2;
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
	ArrayPoints.resize(NumPoints * NumPoints);
	for (size_t i = 0; i < NumPoints * NumPoints; ++i)
	{
		ArrayPoints[i].Restart();
	}
	ArrayPoleCol.clear();
	ArrayPoleRow.clear();
}

void Game::CreateArea()
{
	ClearPole();
	for (size_t i = 0; i < NumPoints + 1; i++)
	{
		ArrayPoleCol.push_back(sf::RectangleShape(sf::Vector2f(_Range * NumPoints, _Thickness)));
		ArrayPoleRow.push_back(sf::RectangleShape(sf::Vector2f(_Thickness, _Range * NumPoints)));
		ArrayPoleCol[i].setPosition(0 + _Shift, i * _Range + _Shift);
		ArrayPoleRow[i].setPosition(i * _Range + _Shift, 0 + _Shift);
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
	text.setCharacterSize(_TextHeight); // in pixels, not points!
	text.setFillColor(sf::Color::White);
	text.setStyle(sf::Text::Bold);
	for (size_t i = 0; i < NumPoints + 1; ++i)
	{
		this->window->draw(ArrayPoleCol[i]);
		this->window->draw(ArrayPoleRow[i]);
	}
	bool EmptyPoints = false;
	for (size_t i = 0; i < NumPoints*NumPoints; ++i)
	{
			if (ArrayPoints[i].value == -1)
			{
				EmptyPoints = true;
				continue;
			}
			text.setString(to_string(ArrayPoints[i].value));
			text.setPosition(GET_CENTER(i / NumPoints) - (text.getLocalBounds().width / 2), GET_CENTER(i % NumPoints) - (_TextHeight / 1.7));
			this->window->draw(text);
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
	bool EndGame = false;
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
					if (mouseCord.x >= _Shift && mouseCord.x <= WINDOW_WIDTH && mouseCord.y >= _Shift && mouseCord.y <= WINDOW_HIGH && !EndGame) // если клик в области экрана
					{
						ind_col = (mouseCord.x - _Shift) / _Range;
						ind_row = (mouseCord.y - _Shift) / _Range;
						if (ind_col >= 0 && ind_col < NumPoints && ind_row >= 0 && ind_row < NumPoints)
						{
							if (!ArrayPoints[ind_col * NumPoints + ind_row].Put(*Current_Player))
							{
								if (DrawArea() == 2)
								{
									this->EndGame();
									EndGame = true;
									continue;
								}
								Current_Player->_SIDE == ZERO ? Current_Player = &Players[1] : Current_Player = &Players[0];
							}
						}
					}
					else if (EndGame)
					{
						CreateMenu();
					}
				}
			}
		}
		if (IS_NETWORK && Current_Player->Computer)
		{
			for (int i = NumPoints*NumPoints - 1; i >= 0; i--)
			{
				if (!ArrayPoints[i].changed)
					if (!ArrayPoints[i].Put(*Current_Player))
					{
						if (DrawArea() == 2)
						{
							this->EndGame();
							EndGame = true;
							continue;
						}
						Current_Player->_SIDE == ZERO ? Current_Player = &Players[1] : Current_Player = &Players[0];
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
}


void Game::setStatus(string text, int height)
{
	sf::Font font;
	if (!font.loadFromFile("Equal-Regular.otf"))
	{
		cout << "Нет файла со шрифтом" << endl;
		return;
	}
	sf::Text status;
	status.setFont(font);
	status.setCharacterSize(100);
	status.setFillColor(sf::Color::White);
	status.setStyle(sf::Text::Bold);
	status.setString(text);
	status.setPosition(_Shift + (NumPoints * _Range / 2)  - status.getGlobalBounds().width / 2, height);
	this->window->draw(status);
}

void Game::setButton(string text, int height)
{
	sf::Font font;
	if (!font.loadFromFile("Equal-Regular.otf"))
	{
		cout << "Нет файла со шрифтом" << endl;
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
	Frame.setOutlineThickness(_Thickness);
	Frame.setFillColor(sf::Color(0, 0, 0, 0));
	Frame.setPosition(WINDOW_WIDTH / 2 - BUTTON_WIDTH / 2, ((BUTTON_HEIGHT - TEXT_STATUS_HEIGHT)/2) + height);
	this->window->draw(Frame);
	this->window->draw(button);
}

void Game::CalculateScore()
{
	int *score = new int[NumPoints * 2 + 2];
	for (size_t i = 0; i < NumPoints * 2 + 2; i++)
	{
		score[i] = 0;
	}
	for (size_t i = 0; i < NumPoints* NumPoints; i++)
	{
		addNum(score[i% NumPoints + NumPoints], ArrayPoints[i/ NumPoints + i% NumPoints].value);
		addNum(score[i% NumPoints], ArrayPoints[i/ NumPoints + i% NumPoints].value);
		if (i / NumPoints == i % NumPoints)
			addNum(score[NumPoints *2], ArrayPoints[i/ NumPoints + i% NumPoints].value);
		if (i / NumPoints + i % NumPoints % NumPoints + 1 == NumPoints)
			addNum(score[NumPoints * 2 + 1], ArrayPoints[i/ NumPoints + i% NumPoints].value);
	}
	for (size_t i = 0; i < NumPoints * 2 + 2; i++)
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
	Players[0].Score > Players[1].Score ? setStatus("PLAYER 0 WIN", (NumPoints * _Range + _Shift) / 2) : Players[1].Score != Players[0].Score ? setStatus("PLAYER 1 WIN", (NumPoints * _Range + _Shift) / 2) : setStatus("GAME DRAW", (NumPoints * _Range + _Shift) / 2);
}

void Game::addNum(int& Origin, int Add)
{
	Origin *= 10;
	Origin += Add;
}

void Game::SaveConfig(int Param1, int Param2, int Param3, int Param4)
{
	ofstream config(CONFIG_FILE);
	config << "Pole " << Param1 << endl
		<< "Range " << Param2 << endl
		<< "Thickness " << Param3 << endl
		<< "Shift " << Param4;
	config.close();
}