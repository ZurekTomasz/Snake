#include "stdafx.h"

sf::RenderWindow renderWindow(sf::VideoMode(1920, 1080), "SpaceShips");
sf::Event event;

void keyboard();

int lwierszy = 96;
int lkolumn = 54;
char mapa[96][54];
int snake_x[15];
int snake_y[5];
int szer_klocka = 20;

int main()
{
	

	//Inicjacja//
	renderWindow.setFramerateLimit(60);

	//Ladowanie tekstur
	sf::Texture t_tlo;
	if (!t_tlo.loadFromFile("grafika/tlo.png"))
		return EXIT_FAILURE;
	sf::Sprite tlo;
	tlo.setTexture(t_tlo);

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
	//Inicjacja//

	snake_x[0] = 10;
	snake_y[0] = 10;
	snake_x[1] = 10;
	snake_y[1] = 11;
	snake_x[2] = 10;
	snake_y[2] = 12;
	snake_x[3] = 10;
	snake_y[3] = 13;

	mapa[snake_x[0]][snake_y[0]] = '1';
	mapa[snake_x[1]][snake_y[1]] = '1';
	mapa[snake_x[2]][snake_y[2]] = '1';
	mapa[snake_x[3]][snake_y[3]] = '1';


	while (renderWindow.isOpen())
	{
		keyboard();

		renderWindow.clear();
		for (int a = 0; a < 96; a++)
		{
			for (int b = 0; b < 54; b++)
			{
				mapa[a][b] = '0';
			}
		}
		
		mapa[snake_x[0]][snake_y[0]] = '2';
		mapa[snake_x[1]][snake_y[1]] = '2';
		mapa[snake_x[2]][snake_y[2]] = '2';
		mapa[snake_x[3]][snake_y[3]] = '1';
		

		for (int a = 0; a < 96; a++)
		{
			for (int b = 0; b < 54; b++)
			{
				if (mapa[a][b] == '0')
				{
					trawa.setPosition(a * szer_klocka, b * szer_klocka);
					renderWindow.draw(trawa);
				}

				if (mapa[a][b] == '1')
				{
					czerwone.setPosition(a * szer_klocka, b * szer_klocka);
					renderWindow.draw(czerwone);
				}

				if (mapa[a][b] == '2')
				{
					niebieskie.setPosition(a * szer_klocka, b * szer_klocka);
					renderWindow.draw(niebieskie);
				}
			}
			printf("\n");
		}

		renderWindow.display();
	}

	_getch();
	return 0;
}

void keyboard()
{
	while (renderWindow.pollEvent(event)) {
		if (event.type == sf::Event::EventType::Closed)
			renderWindow.close();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			renderWindow.close();
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		snake_x[0] = snake_x[1];
		snake_y[0] = snake_y[1];
		snake_x[1] = snake_x[2];
		snake_y[1] = snake_y[2];
		snake_x[2] = snake_x[3];
		snake_y[2] = snake_y[3];
		snake_x[3] -= 1;
		snake_y[3] += 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		snake_x[0] = snake_x[1];
		snake_y[0] = snake_y[1];
		snake_x[1] = snake_x[2];
		snake_y[1] = snake_y[2];
		snake_x[2] = snake_x[3];
		snake_y[2] = snake_y[3];
		snake_x[3] += 0;
		snake_y[3] -= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		snake_x[0] = snake_x[1];
		snake_y[0] = snake_y[1];
		snake_x[1] = snake_x[2];
		snake_y[1] = snake_y[2];
		snake_x[2] = snake_x[3];
		snake_y[2] = snake_y[3];
		snake_x[3] += 1;
		snake_y[3] += 0;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		snake_x[0] = snake_x[1];
		snake_y[0] = snake_y[1];
		snake_x[1] = snake_x[2];
		snake_y[1] = snake_y[2];
		snake_x[2] = snake_x[3];
		snake_y[2] = snake_y[3];
		snake_x[3] += 0;
		snake_y[3] += 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		snake_x[3] = 30;
		snake_y[3] = 30;
	}
}