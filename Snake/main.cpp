#include "stdafx.h"

sf::RenderWindow renderWindow(sf::VideoMode(1280, 720), "Snake");
sf::Event event;
sf::Text text;
sf::Font font; 

void keyboard();

int lwierszy = 96;
int lkolumn = 54;
char mapa[96][54];
char przeszkoda[96][54];
int snake_dlugosc = 2;
int snake_x[90];//Maksymalna dlugosc weza
int snake_y[90];
int szer_klocka = 20;
int kierunek = 4; //stop-0,lewo-1,gora-2,dol-3,prawo-4
int punkt_x = 50;
int punkt_y = 10;
int punkty = 0;
int menugry = 1;
string s_punkty = "POINTS: 0";

int main()
{
	//Inicjacja//
	sf::View view1(sf::FloatRect(0, 0, 1920, 1080));
	renderWindow.setView(view1);

	renderWindow.setFramerateLimit(60);

	//Ladowanie tekstur
	
	if (!font.loadFromFile("arial.ttf"))
	{
		// error...
	}

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

	//
	// Load an image file from a file
	sf::Image background;
	background.loadFromFile("grafika/image1.bmp");

	sf::Image image;
	image.create((int)background.getSize().x, (int)background.getSize().y, sf::Color::Black);
	image.copy(background, 0, 0);
	sf::Color color = image.getPixel(10, 90);
	cout << "R: " << (int)color.r << endl << "G: " << (int)color.g << endl << "B: " << (int)color.b << endl;
	image.saveToFile("grafika/result.png");



	text.setFont(font);
	text.setCharacterSize(48);
	text.setFillColor(sf::Color::Blue);
	text.setPosition(30, 30);
	text.setStyle(sf::Text::Bold);
	text.setString(s_punkty);

	//Inicjacja//
	
	for (int i = 0; i < snake_dlugosc; i++)
	{
		snake_x[i] = 30 - i;
		snake_y[i] = 10;
	}

	sf::Clock clock;

	while (renderWindow.isOpen())
	{
		renderWindow.clear();

		if (menugry == 0)
		{

			for (int a = 0; a < 96; a++)
			{
				for (int b = 0; b < 54; b++)
				{
					przeszkoda[a][b] = '0';
					mapa[a][b] = '0';
				}
			}

			sf::Time t1 = clock.getElapsedTime();

			if (t1.asMilliseconds() > 100.0f)
			{
				for (int i = snake_dlugosc - 1; i > 0; i--)
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

			if (snake_x[0] == punkt_x && snake_y[0] == punkt_y)
			{
				punkty++;
				//printf("Punkty: %i\n", punkty);

				snake_dlugosc++;
				punkt_x = rand() % 90 + 3;
				punkt_y = rand() % 50 + 3;
			}

			text.setFont(font);
			text.setCharacterSize(48);
			text.setFillColor(sf::Color::Blue);
			text.setPosition(30, 30);
			text.setStyle(sf::Text::Bold);
			text.setString(s_punkty);

			s_punkty = "POINTS: " + std::to_string(punkty);
			text.setString(s_punkty);

			keyboard();

			for (int a = 0; a < 96; a++)
			{
				przeszkoda[a][0] = '4';
				mapa[a][0] = '4';
			}

			for (int a = 0; a < 96; a++)
			{
				przeszkoda[a][53] = '4';
				mapa[a][53] = '4';
			}

			for (int a = 0; a < 54; a++)
			{
				przeszkoda[0][a] = '4';
				mapa[0][a] = '4';
			}

			for (int a = 0; a < 54; a++)
			{
				przeszkoda[95][a] = '4';
				mapa[95][a] = '4';
			}

			/*
			for (int a = 0; a < 54; a++)
			{
				przeszkoda[35][a] = '4';
				mapa[35][a] = '4';
			}

			for (int a = 0; a < 54; a++)
			{
				przeszkoda[45][a] = '2';
				mapa[45][a] = '2';
			}
			*/

			mapa[snake_x[0]][snake_y[0]] = '1';
			for (int i = 1; i < snake_dlugosc; i++)
			{
				mapa[snake_x[i]][snake_y[i]] = '2';
			}

			mapa[punkt_x][punkt_y] = '3';

			for (int a = 1; a < snake_dlugosc; a++)
			{
				if (snake_x[0] == snake_x[a] && snake_y[0] == snake_y[a])
				{
					printf("Kolizja z ogonem\n");
					menugry = 2;
					//exit(1);
				}
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
						if (przeszkoda[a][b] == '4' || przeszkoda[a][b] == '2')
						{
							printf("Kolizja zwykla\n");
							menugry = 2;
							//exit(1);
						}
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
			
			renderWindow.draw(text);

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

			renderWindow.display();
		}
		else if(menugry==1)
		{

			keyboard();
			renderWindow.clear();
			renderWindow.draw(menu);
			renderWindow.display();
		}
		else
		{

			keyboard();
			renderWindow.clear();
			renderWindow.draw(loss);

			text.setFont(font);
			text.setCharacterSize(72);
			text.setFillColor(sf::Color::Blue);
			text.setPosition(50, 300);
			text.setStyle(sf::Text::Bold);
			text.setString(s_punkty);
			s_punkty = "POINTS: " + std::to_string(punkty) + "     PRESS 'X' TO START THE GAME";
			text.setString(s_punkty);
			renderWindow.draw(text);

			renderWindow.display();
		}
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

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		if(kierunek!=4)
		kierunek = 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		//sf::Image screenshot;
		//screenshot = renderWindow.capture();
		//screenshot.saveToFile("grafika/result.png");

		//renderWindow.capture().saveToFile("grafika/result.png");

		

		if (kierunek != 3)
		kierunek = 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (kierunek != 2)
		kierunek = 3;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		if (kierunek != 1)
		kierunek = 4;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
	{
		if (menugry != 0)
		{
			text.setFont(font);
			text.setCharacterSize(48);
			text.setFillColor(sf::Color::Blue);
			text.setPosition(30, 30);
			text.setStyle(sf::Text::Bold);
			text.setString(s_punkty);

			lwierszy = 96;
			lkolumn = 54;
			mapa[96][54];
			przeszkoda[96][54];
			snake_dlugosc = 2;
			snake_x[30];
			snake_y[30];
			szer_klocka = 20;
			kierunek = 4; //stop-0,lewo-1,gora-2,dol-3,prawo-4
			punkt_x = 50;
			punkt_y = 10;
			s_punkty = "POINTS: 0";
			punkty = 0;

			for (int i = 0; i < snake_dlugosc; i++)
			{
				snake_x[i] = 30 - i;
				snake_y[i] = 10;
			}

			menugry = 0;
		}
	}
}
