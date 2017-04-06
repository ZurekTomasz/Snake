#include "stdafx.h"

int lwierszy = 24;
int lkolumn = 78;
char mapa[24][78];
int snake_x[5];
int snake_y[5];

int main()
{
	printf("Snake Game 2D in console");
	_getch();

	snake_x[0] = 20;
	snake_y[0] = 20;
	snake_x[1] = 20;
	snake_y[1] = 21;
	snake_x[2] = 20;
	snake_y[2] = 22;
	snake_x[3] = 20;
	snake_y[3] = 23;
	char key;
	key = 'a';
	while (key != '.') 
	{

		for (int a = 0; a < lwierszy; a++)
		{
			for (int b = 0; b < lkolumn; b++)
			{
				mapa[a][b] = ' ';
			}
		}

		mapa[snake_x[0]][snake_y[0]] = '1';
		mapa[snake_x[1]][snake_y[1]] = '2';
		mapa[snake_x[2]][snake_y[2]] = '3';
		mapa[snake_x[3]][snake_y[3]] = '4';
		mapa[snake_x[4]][snake_y[4]] = ' ';

		for (int a = 0; a < lwierszy; a++)
		{
			for (int b = 0; b < lkolumn; b++)
			{
				cout << mapa[a][b];
			}
			printf("\n");
		}

		cin >> key;
		if (key == 'w')
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

		if (key == 'a')
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

		if (key == 's')
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

		if (key == 'd')
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

	}
	_getch();
	return 0;
}