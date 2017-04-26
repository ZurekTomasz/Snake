#include "stdafx.h"

sf::RenderWindow renderWindow(sf::VideoMode(1280, 720), "Snake");
sf::View view1(sf::FloatRect(0, 0, 1920, 1080));
Files lvl1("lvl2.csv", ',');

sf::Event event1;
sf::Text text1;
sf::Font font1; 

class Snake
{
	public:
		#define max_length 5184
		int length = 2;
		int start_x = 30;
		int start_y = 10;
		int x[max_length];
		int y[max_length];
		int direction = 4; //STOP-0,LEFT-1,UP-2,DOWN-3,RIGHT-4
		int point_x = 50;
		int point_y = 10;
		int points = 0;
};

Snake snake1;

class Board
{
	public:
		int row = 98; //96+2
		int column = 56; //54+2
		char map[98][56];
		char obstacle[98][56];
		int width_block = 20;
		int game_menu = 1;
		string s_points = "POINTS: 0";
};

Board board1;

void keyboard();
void label(int x = 0, int y = 0, string s = "None", int size = 72);
void clear_level();


int main()
{
	//CONFIG//
	renderWindow.setView(view1);
	renderWindow.setFramerateLimit(60);
	sf::Clock clock;

	//Load font
	if (!font1.loadFromFile("arial.ttf"))
		return EXIT_FAILURE;

	//Load texture
	sf::Texture t_tlo;
	if (!t_tlo.loadFromFile("grafika/tlo.png"))
		return EXIT_FAILURE;
	sf::Sprite tlo;
	tlo.setTexture(t_tlo);

	sf::Texture t_menu;
	if (!t_menu.loadFromFile("grafika/menu.png"))
		return EXIT_FAILURE;
	sf::Sprite menu;
	menu.setTexture(t_menu);

	sf::Texture t_loss;
	if (!t_loss.loadFromFile("grafika/loss.png"))
		return EXIT_FAILURE;
	sf::Sprite loss;
	loss.setTexture(t_loss);

	sf::Texture t_trawa;
	if (!t_trawa.loadFromFile("grafika/trawa.png"))
		return EXIT_FAILURE;
	sf::Sprite trawa;
	trawa.setTexture(t_trawa);

	sf::Texture t_niebieskie;
	if (!t_niebieskie.loadFromFile("grafika/niebieskie.png"))
		return EXIT_FAILURE;
	sf::Sprite niebieskie;
	niebieskie.setTexture(t_niebieskie);

	sf::Texture t_czerwone;
	if (!t_czerwone.loadFromFile("grafika/czerwone.png"))
		return EXIT_FAILURE;
	sf::Sprite czerwone;
	czerwone.setTexture(t_czerwone);

	sf::Texture t_zolte;
	if (!t_zolte.loadFromFile("grafika/zolte.png"))
		return EXIT_FAILURE;
	sf::Sprite zolte;
	zolte.setTexture(t_zolte);

	sf::Texture t_fiolet;
	if (!t_fiolet.loadFromFile("grafika/fiolet.png"))
		return EXIT_FAILURE;
	sf::Sprite fiolet;
	fiolet.setTexture(t_fiolet);

	sf::Texture t_biel;
	if (!t_biel.loadFromFile("grafika/biel.png"))
		return EXIT_FAILURE;
	sf::Sprite biel;
	biel.setTexture(t_biel);

	//LOGIC//
	while (renderWindow.isOpen())
	{
		renderWindow.clear();
		keyboard();

		switch (board1.game_menu)
		{
			case 0:
			{
				label(30, 30, board1.s_points, 48);

				//Changing the position of the snake
				sf::Time t1 = clock.getElapsedTime();
				if (t1.asMilliseconds() > 1000.0f / 10.0f)
				{
					board1.map[snake1.x[snake1.length - 1]][snake1.y[snake1.length - 1]] = '0';
					for (int i = snake1.length - 1; i > 0; i--)
					{
						snake1.x[i] = snake1.x[i-1];
						snake1.y[i] = snake1.y[i-1];
					}

					if (snake1.direction == 1)
					{
						snake1.x[0] -= 1;
						snake1.y[0] += 0;
					}

					if (snake1.direction == 2)
					{
						snake1.x[0] += 0;
						snake1.y[0] -= 1;
					}

					if (snake1.direction == 3)
					{
						snake1.x[0] += 0;
						snake1.y[0] += 1;
					}

					if (snake1.direction == 4)
					{
						snake1.x[0] += 1;
						snake1.y[0] += 0;
					}
					clock.restart();
				}

				//Acquiring a point
				if (snake1.x[0] == snake1.point_x && snake1.y[0] == snake1.point_y)
				{
					snake1.points++;
					snake1.length++;

					bool coltail = false;
					do 
					{
						coltail = false;;
						snake1.point_x = rand() % 96 + 2;
						snake1.point_y = rand() % 54 + 2;

						for (int a = 1; a < snake1.length; a++)
						{
							if (snake1.point_x == snake1.x[a] && snake1.point_y == snake1.y[a])
								coltail = true;
						}

					} while (board1.obstacle[snake1.point_x][snake1.point_y] != '0' || coltail == true);

					board1.s_points = "POINTS: " + std::to_string(snake1.points);
					cout << board1.s_points << endl;
				}

				//Snake generator
				board1.map[snake1.x[0]][snake1.y[0]] = '1';//Color snake first block
				for (int i = 1; i < snake1.length; i++)
				{
					board1.map[snake1.x[i]][snake1.y[i]] = '2';//Color tail snake
				}
				board1.map[snake1.point_x][snake1.point_y] = '3';//Color point
				board1.map[0][0] = lvl1.matrix[0][0][0];

				//Collision with snake tail
				for (int a = 1; a < snake1.length; a++)
				{
					if (snake1.x[0] == snake1.x[a] && snake1.y[0] == snake1.y[a])
					{
						printf("Collision with the tail\n");
						board1.game_menu = 2;
					}
				}

				//Drawing map
				for (int a = 0; a < 98; a++)
				{
					for (int b = 0; b < 56; b++)
					{

						if (board1.map[a][b] == '0')
						{
							trawa.setPosition(a * board1.width_block - 20, b * board1.width_block -  20);
							renderWindow.draw(trawa);
						}

						if (board1.map[a][b] == '1')
						{
							if (board1.obstacle[a][b] == '1' || board1.obstacle[a][b] == '4')
							{
								printf("Collision with obstacle\n");
								board1.game_menu = 2;
							}

							czerwone.setPosition(a * board1.width_block - 20, b * board1.width_block - 20);
							renderWindow.draw(czerwone);
						}

						if (board1.map[a][b] == '2')
						{
							niebieskie.setPosition(a * board1.width_block - 20, b * board1.width_block - 20);
							renderWindow.draw(niebieskie);
						}

						if (board1.map[a][b] == '3')
						{
							fiolet.setPosition(a * board1.width_block - 20, b * board1.width_block - 20);
							renderWindow.draw(fiolet);
						}

						if (board1.map[a][b] == '4')
						{
							zolte.setPosition(a * board1.width_block - 20, b * board1.width_block - 20);
							renderWindow.draw(zolte);
						}

						if (board1.map[a][b] == '5')
						{
							biel.setPosition(a * board1.width_block - 20, b * board1.width_block - 20);
							renderWindow.draw(biel);
						}
					}

				}

				//No walls
				if (snake1.x[0] >= 97)
				{
					if (snake1.direction != 1)
						snake1.x[0] = 1;
				}
				if (snake1.x[0] <= 0)
				{
					if (snake1.direction != 4)
						snake1.x[0] = 96;
				}
				if (snake1.y[0] >= 55)
				{
					if (snake1.direction != 2)
						snake1.y[0] = 1;
				}
				if (snake1.y[0] <= 0)
				{
					if (snake1.direction != 3)
						snake1.y[0] = 54;
				}


				renderWindow.draw(text1);
			}
			break;

			case 1:
			{
				renderWindow.draw(menu);
			}
			break;

			case 2:
			{
				renderWindow.draw(loss);

				board1.s_points = "POINTS: " + std::to_string(snake1.points) + "     PRESS 'X' TO START THE GAME";
				label(50, 300, board1.s_points, 72);

				renderWindow.draw(text1);
			}
			break;

		}
		renderWindow.display();
	}

	return 0;
}

void clear_level()
{
	snake1.length = 6;
	snake1.direction = 4; //STOP-0,LEFT-1,UP-2,DOWN-3,RIGHT-4
	snake1.point_x = 50;
	snake1.point_y = 10;
	snake1.points = 0;
	board1.s_points = "POINTS: 0";
	label(30, 30, board1.s_points, 48);

	//Map generator
	lvl1.load();
	for (int a = 0; a < 98; a++)
	{
		for (int b = 0; b < 56; b++)
		{
			board1.map[a][b] = lvl1.matrix[b][a][0];
			board1.obstacle[a][b] = lvl1.matrix[b][a][0];
		}
	}
	
	for (int i = 0; i < snake1.length; i++)
	{
		snake1.x[i] = snake1.start_x - i;
		snake1.y[i] = snake1.start_y;
	}

	board1.game_menu = 0;
}

void label(int x, int y, string s, int size)
{
	text1.setFont(font1);
	text1.setFillColor(sf::Color::Blue);
	text1.setStyle(sf::Text::Bold);
	text1.setPosition(x, y);
	text1.setCharacterSize(size);
	text1.setString(s);
}

void keyboard()
{
	while (renderWindow.pollEvent(event1)) {
		if (event1.type == sf::Event::EventType::Closed)
			renderWindow.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			renderWindow.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(snake1.direction!=4)
			snake1.direction = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (snake1.direction != 3)
			snake1.direction = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (snake1.direction != 2)
			snake1.direction = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (snake1.direction != 1)
			snake1.direction = 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (board1.game_menu != 0)
		{
			clear_level();
		}
	}
}
