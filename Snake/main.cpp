#include "stdafx.h"

sf::RenderWindow renderWindow(sf::VideoMode(1280, 720), "Snake");
sf::View view1(sf::FloatRect(0, 0, 1920, 1080));

sf::Event event1;
sf::Text text1;
sf::Font font1; 

class Snake
{
	public:
		#define max_length 100
		int length = 2;
		int start_x = 30;
		int start_y = 10;
		int x[max_length];//Maksymalna dlugosc weza
		int y[max_length];
		int direction = 4; //stop-0,lewo-1,gora-2,dol-3,prawo-4
		int point_x = 50;
		int point_y = 10;
		int points = 0;
};

Snake snake1;

class Board
{
	public:
		int row = 96;
		int column = 54;
		char map[96][54];
		char obstacle[96][54];
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
	//Initiation//
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

	
	while (renderWindow.isOpen())
	{
		renderWindow.clear();
		keyboard();

		switch (board1.game_menu)
		{
			case 0:
			{
				for (int a = 0; a < 96; a++)
				{
					for (int b = 0; b < 54; b++)
					{
						board1.obstacle[a][b] = '0';
						board1.map[a][b] = '0';
					}
				}


				sf::Time t1 = clock.getElapsedTime();
				if (t1.asMilliseconds() > 1000.0f / 10.0f)
				{
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

				if (snake1.x[0] == snake1.point_x && snake1.y[0] == snake1.point_y)
				{
					snake1.points++;
					snake1.length++;
					snake1.point_x = rand() % 90 + 3;
					snake1.point_y = rand() % 50 + 3;
				}

				board1.s_points = "POINTS: " + std::to_string(snake1.points);
				label(30, 30, board1.s_points, 48);

				for (int a = 0; a < 96; a++)
				{
					board1.obstacle[a][0] = '4';
					board1.map[a][0] = '4';
				}

				for (int a = 0; a < 96; a++)
				{
					board1.obstacle[a][53] = '4';
					board1.map[a][53] = '4';
				}

				for (int a = 0; a < 54; a++)
				{
					board1.obstacle[0][a] = '4';
					board1.map[0][a] = '4';
				}

				for (int a = 0; a < 54; a++)
				{
					board1.obstacle[95][a] = '4';
					board1.map[95][a] = '4';
				}

				/*
				for (int a = 0; a < 54; a++)
				{
					obstacle[35][a] = '4';
					map[35][a] = '4';
				}

				for (int a = 0; a < 54; a++)
				{
					obstacle[45][a] = '2';
					map[45][a] = '2';
				}
				*/

				board1.map[snake1.x[0]][snake1.y[0]] = '1';//Kolor dziubka
				for (int i = 1; i < snake1.length; i++)
				{
					board1.map[snake1.x[i]][snake1.y[i]] = '2';//Kolor ogona
				}

				board1.map[snake1.point_x][snake1.point_y] = '3';//Kolor punkta

				for (int a = 1; a < snake1.length; a++)
				{
					if (snake1.x[0] == snake1.x[a] && snake1.y[0] == snake1.y[a])
					{
						printf("Kolizja z ogonem\n");
						board1.game_menu = 2;
					}
				}

				for (int a = 0; a < 96; a++)
				{
					for (int b = 0; b < 54; b++)
					{

						if (board1.map[a][b] == '0')
						{
							trawa.setPosition(a * board1.width_block, b * board1.width_block);
							renderWindow.draw(trawa);
						}

						if (board1.map[a][b] == '1')
						{
							if (board1.obstacle[a][b] == '4' || board1.obstacle[a][b] == '2')
							{
								printf("Kolizja zwykla\n");
								board1.game_menu = 2;
							}

							czerwone.setPosition(a * board1.width_block, b * board1.width_block);
							renderWindow.draw(czerwone);
						}

						if (board1.map[a][b] == '2')
						{
							niebieskie.setPosition(a * board1.width_block, b * board1.width_block);
							renderWindow.draw(niebieskie);
						}

						if (board1.map[a][b] == '3')
						{
							zolte.setPosition(a * board1.width_block, b * board1.width_block);
							renderWindow.draw(zolte);
						}

						if (board1.map[a][b] == '4')
						{
							fiolet.setPosition(a * board1.width_block, b * board1.width_block);
							renderWindow.draw(fiolet);
						}
					}

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
	snake1.length = 2;
	snake1.direction = 4; //stop-0,lewo-1,gora-2,dol-3,prawo-4
	snake1.point_x = 50;
	snake1.point_y = 10;
	snake1.points = 0;
	board1.s_points = "POINTS: 0";
	label(30, 30, board1.s_points, 48);
	
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



/*
sf::Vector2u windowSize = renderWindow.getSize();
sf::Texture texture;
texture.create(windowSize.x, windowSize.y);
texture.update(renderWindow);
sf::Image screenshot = texture.copyToImage();


//screenshot.saveToFile("grafika/result.png");
//476x142

sf::Color color2 = screenshot.getPixel(476, 142);
cout << "R: " << (int)color2.r  << "G: " << (int)color2.g  << "B: " << (int)color2.b << endl;
//_getch();
*/

/*
// Load an image file from a file
sf::Image background;
background.loadFromFile("grafika/image1.bmp");

sf::Image image;
image.create((int)background.getSize().x, (int)background.getSize().y, sf::Color::Black);
image.copy(background, 0, 0);
sf::Color color = image.getPixel(10, 90);
cout << "R: " << (int)color.r << endl << "G: " << (int)color.g << endl << "B: " << (int)color.b << endl;
image.saveToFile("grafika/result.png");

for (int i = 0; i < snake1.length; i++)
{
snake1.x[i] = 30 - i;
snake1.y[i] = 10;
}
*/

/*
sf::Image screenshot;
screenshot = renderWindow.capture();
screenshot.saveToFile("grafika/result.png");
renderWindow.capture().saveToFile("grafika/result.png");
*/
