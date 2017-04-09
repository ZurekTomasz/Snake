#include "stdafx.h"

sf::RenderWindow renderWindow(sf::VideoMode(1920, 1080), "Snake");
sf::Event event;

void keyboard();

int lwierszy = 96;
int lkolumn = 54;
char mapa[96][54];
int snake_x[4];
int snake_y[4];
int szer_klocka = 20;
int kierunek = 4; //stop-0,lewo-1,gora-2,dol-3,prawo-4
int punkt_x = 50;
int punkt_y = 10;
int punkty = 0;

int main()
{
	//Inicjacja//
	sf::View view1(sf::FloatRect(0, 0, 1920, 1080));
	renderWindow.setView(view1);

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
	//Inicjacja//

	snake_x[0] = 13;
	snake_y[0] = 10;
	snake_x[1] = 12;
	snake_y[1] = 10;
	snake_x[2] = 11;
	snake_y[2] = 10;
	snake_x[3] = 10;
	snake_y[3] = 10;
	
	sf::Clock clock;
	while (renderWindow.isOpen())
	{
		sf::Time t1 = clock.getElapsedTime();

		if (t1.asMilliseconds() > 30.0f)
		{
			for (int i = 3; i > 0; i--)
			{
				int iv = i - 1;
				snake_x[i] = snake_x[iv];
				snake_y[i] = snake_y[iv];
			}

			if (kierunek == 1)
			{
				snake_x[0] -= 1;
				snake_y[0] += 0;
			}

			if (kierunek == 2)
			{
				snake_x[0] += 0;
				snake_y[0] -= 1;
			}

			if (kierunek == 3)
			{
				snake_x[0] += 0;
				snake_y[0] += 1;
			}

			if (kierunek == 4)
			{
				snake_x[0] += 1;
				snake_y[0] += 0;
			}
			clock.restart();
		}

		if (snake_y[0] == 53 || snake_y[0] == 0 || snake_x[0] == 0 || snake_x[0] == 95)
		{
			printf("Game Over\n");
			exit(1);
			_getch();
		}

		if(snake_x[0] == punkt_x && snake_y[0] == punkt_y)
		{
			punkty++;
			printf("Punkty: %i\n", punkty);
			punkt_x = rand() % 90 + 3;
			punkt_y = rand() % 50 + 3;
		}

		keyboard();

		renderWindow.clear();

		for (int a = 0; a < 96; a++)
		{
			for (int b = 0; b < 54; b++)
			{
				mapa[a][b] = '0';
			}
		}
		
		mapa[snake_x[0]][snake_y[0]] = '1';
		mapa[snake_x[1]][snake_y[1]] = '2';
		mapa[snake_x[2]][snake_y[2]] = '2';
		mapa[snake_x[3]][snake_y[3]] = '2';

		mapa[punkt_x][punkt_y] = '3';

		for (int a = 0; a < 96; a++)
		{
			mapa[a][0] = '4';
		}

		for (int a = 0; a < 96; a++)
		{ 
			mapa[a][53] = '4';
		}

		for (int a = 0; a < 54; a++)
		{
			mapa[0][a] = '4';
		}

		for (int a = 0; a < 54; a++)
		{
			mapa[95][a] = '4';
		}
		

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

				if (mapa[a][b] == '3')
				{
					zolte.setPosition(a * szer_klocka, b * szer_klocka);
					renderWindow.draw(zolte);
				}

				if (mapa[a][b] == '4')
				{
					fiolet.setPosition(a * szer_klocka, b * szer_klocka);
					renderWindow.draw(fiolet);
				}
			}
			
		}
		
		renderWindow.display();

	}

	//_getch();
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
		if(kierunek!=4)
		kierunek = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		if (kierunek != 3)
		kierunek = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		if (kierunek != 2)
		kierunek = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		if (kierunek != 1)
		kierunek = 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		snake_x[3] = 30;
		snake_y[3] = 30;
	}
}