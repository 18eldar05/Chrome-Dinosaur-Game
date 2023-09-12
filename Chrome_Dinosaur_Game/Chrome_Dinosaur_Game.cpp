//#include "stdafx.h"
#include "pch.h"
#include <iostream>
#include <windows.h>
#include <ctime>
#include <string>
#include <conio.h>
using namespace std;

const int x = 87;
const int y = 12;

enum colors
{
	BLACK, BLUE, GREEN, CYAN, RED, PURPLE, YELLOW, GREY,
	LIGHTGREY, LIGHTBLUE, LIGHTGREEN, LIGHTCYAN, LIGHTRED,
	LIGHTPURPLE, LIGHTYELLOW, WHITE
};

enum Direction
{
	Left = 75,
	Right = 77,
	Up = 72,
	Down = 80
};

void setConsoleColor(int textColor, int bgColor)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (textColor + (bgColor * 16)));
}

void stream(string a[x][y])
{
	for (int i = 0; i < 11; i++)
	{
		for (int j = 0; j < x - 1; j++)
		{
			a[j][i] = a[j + 1][i];
		}
	}
}

/*
void stream_cycle(string a[x][y])
{
	for (int i = 0; i < 2; i++)
	{
		string buf = a[0][i];
		for (int j = 0; j < x - 1; j++)
		{
			a[j][i] = a[j + 1][i];
		}
		a[x - 1][i] = buf;
	}

	int i = 11;
	string buf = a[0][i];
	for (int j = 0; j < x - 1; j++)
	{
		a[j][i] = a[j + 1][i];
	}
	a[x - 1][i] = buf;
}
*/

bool drago_constructor(char drago[], string a[x][y], int col, int b, int c, bool loose)
{
	int g = 0;
	for (int i = b; i <= c; i++)
	{
		if (a[i][col] != " ") { loose = true; }
		a[i][col] = drago[g];
		g++;
	}
	return loose;
}

void drago_destructor(string a[x][y], int col, int b, int c)
{
	for (int i = b; i <= c; i++)
	{
		a[i][col] = " ";
	}
}

void print(string a[x][y], int h, int zad, int score, int style)
{
	int bg;
	int plants;
	int birds;
	int drago;
	int grass;
	int font;
	string buf[x][2];

	if (style == 0)
	{
		setConsoleColor(WHITE, BLACK);
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < x; j++)
			{
				buf[j][i] = a[j][i];
				a[j][i] = " ";
			}
		}
	}
	if (style == 1)
	{
		bg = BLACK;
		plants = LIGHTGREEN;
		birds = LIGHTBLUE;
		drago = LIGHTRED;
		grass = GREEN;
		font = WHITE;
		setConsoleColor(font, bg);
	}	
	if (style == 2)
	{
		setConsoleColor(BLACK, WHITE);
	}

	//вывод на экран
	system("cls");
	cout << "____________________zad: " << zad << "____________score: " << score << "______________________________________________" << endl;
	for (int i = 0; i < y; i++)
	{
		for (int j = 0; j < x; j++)
		{
			if ((style != 0) && (style != 2))
			{
				if ((i >= 8) && (i <= 10) && (a[j][i] != " ")) { setConsoleColor(plants, bg); }

				if ((i >= 4) && (i <= 6) && (a[j][i] != " ")) { setConsoleColor(birds, bg); }

				if (((i == h) && (j >= 11) && (j <= 13)) ||
					((i == h + 1) && (j >= 5) && (j <= 14)) ||
					((i == h + 2) && (j >= 6) && (j <= 14)) ||
					((i == h + 3) && (j >= 9) && (j <= 11)))
				{
					setConsoleColor(drago, bg);
				}

				if (i == 11) { setConsoleColor(grass, bg); }
			}
			cout << a[j][i];

			if ((style != 0) && (style != 2)) { setConsoleColor(font, bg); }
		}
		cout << endl;
	}
	if (style == 0)
	{
		for (int i = 0; i < 2; i++)
		{
			for (int j = 0; j < x; j++)
			{
				a[j][i] = buf[j][i];
			}
		}
	}
}

int main()
{
	setlocale(LC_ALL, "rus");
	srand(time(NULL)); 
	string a[x][y];
	bool once = true;
	int dif;
	int style = 1;

	while (true)
	{
		bool loose = false;
		int score = 0;
		int zad = 60;
		bool jump = false;
		int t = 0;
		int h = 7;
		int birds = 0;
		int kaktus = 0;
		int brunch = 0;
		int drevo = 0;
		int cloud0 = 0;
		int cloud1 = 0;
		int r = 0;
		int d = 0;
		int rc0 = 0;
		int dc0 = 0;
		int rc1 = 0;
		int dc1 = 0;

		//пустота
		for (int i = 0; i < y; i++)
		{
			for (int j = 0; j < x; j++)
			{
				a[j][i] = " ";
			}
		}

		//трава
		for (int i = 0; i < x; i++)
		{
			if (i % 2 != 0) { a[i][11] = "\""; }
			else { a[i][11] = "'"; }
		}

		//объявление драго
		char drago_1[] = "___";
		char drago_2[] = "\\  __(o_o)";
		char drago_3[] = "\\(_____)~";
		char drago_4[] = "| |";

		//объявление птиц
		char birds_1[] = "\\/      \\/";
		char birds_2[] = "  \\/  \\/  ";
		char birds_3[] = "    \\/    ";

		//объявление кактуса
		char kaktus_1[] = "##";
		char kaktus_2[] = "##";

		//объявление куста
		char brunch_1[] = "{~~}";
		char brunch_2[] = "{~~}";

		//объявление дрэва
		char drevo_1[] = "{~~}";
		char drevo_2[] = "{~~}";
		char drevo_3[] = " || ";

		//объявление облаков 2,3,4
		char cloud_two[] = "(~~)";
		char cloud_three[] = "(~~~)";
		char cloud_four[] = "(~~~~)";

		if (style != 0)
		{
			//начальные облака
			a[11][0] = "(";
			a[12][0] = "~";
			a[13][0] = "~";
			a[14][0] = "~";
			a[15][0] = ")";

			a[20][0] = "(";
			a[21][0] = "~";
			a[22][0] = "~";
			a[23][0] = ")";

			a[50][0] = "(";
			a[51][0] = "~";
			a[52][0] = "~";
			a[53][0] = "~";
			a[54][0] = ")";

			a[65][0] = "(";
			a[66][0] = "~";
			a[67][0] = "~";
			a[68][0] = ")";

			a[79][0] = "(";
			a[80][0] = "~";
			a[81][0] = "~";
			a[82][0] = "~";
			a[83][0] = ")";

			a[3][1] = "(";
			a[4][1] = "~";
			a[5][1] = "~";
			a[6][1] = "~";
			a[7][1] = "~";
			a[8][1] = ")";

			a[27][1] = "(";
			a[28][1] = "~";
			a[29][1] = "~";
			a[30][1] = "~";
			a[31][1] = "~";
			a[32][1] = ")";

			a[40][1] = "(";
			a[41][1] = "~";
			a[42][1] = "~";
			a[43][1] = "~";
			a[44][1] = ")";

			a[60][1] = "(";
			a[61][1] = "~";
			a[62][1] = "~";
			a[63][1] = ")";

			a[73][1] = "(";
			a[74][1] = "~";
			a[75][1] = "~";
			a[76][1] = ")";
		}

		//начальный кактус
		a[37][9] = "#"; a[38][9] = "#";
		a[37][10] = "#"; a[38][10] = "#";

		//начальное дрэво
		a[61][8] = "{"; a[62][8] = "~"; a[63][8] = "~"; a[64][8] = "}";
		a[61][9] = "{"; a[62][9] = "~"; a[63][9] = "~"; a[64][9] = "}";
		a[62][10] = "|"; a[63][10] = "|";

		//конструктор драго
		loose = drago_constructor(drago_1, a, h/**/, 11, 13, loose);
		loose = drago_constructor(drago_2, a, h + 1, 5, 14, loose);
		loose = drago_constructor(drago_3, a, h + 2, 6, 14, loose);
		loose = drago_constructor(drago_4, a, h + 3, 9, 11, loose);

		print(a, h, zad, score, style);

		//деструктор драго
		drago_destructor(a, h, 11, 13);
		drago_destructor(a, h + 1, 5, 14);
		drago_destructor(a, h + 2, 6, 14);
		drago_destructor(a, h + 3, 9, 11);

		/*
		cout << "Choose the style" << endl;
		Sleep(800);
		setConsoleColor(BLACK, WHITE);
		*/

		//выбор сложности
		//int dif;
		int height_of_jump;
		int time_of_hanging;
		if (once){ cout << "Choose the level of difficulty (1 - easy, 2 - medium, 3 - hard, 4 - xxxtra hard)"
			<< "\n Use arrows to change style" << endl; }

		if (once)
		{
			do
			{
				dif = _getch();
				if ((dif == Right) || (dif == Left))
				{
					dif == Right ? style++ : style--;
					if (style < 0) { style = 2; }
					if (style > 2) { style = 0; }

					//конструктор драго
					loose = drago_constructor(drago_1, a, h/**/, 11, 13, loose);
					loose = drago_constructor(drago_2, a, h + 1, 5, 14, loose);
					loose = drago_constructor(drago_3, a, h + 2, 6, 14, loose);
					loose = drago_constructor(drago_4, a, h + 3, 9, 11, loose);

					print(a, h, zad, score, style);

					//деструктор драго
					drago_destructor(a, h, 11, 13);
					drago_destructor(a, h + 1, 5, 14);
					drago_destructor(a, h + 2, 6, 14);
					drago_destructor(a, h + 3, 9, 11);

					cout << "Choose the level of difficulty to play again (1 - easy, 2 - medium, 3 - hard, 4 - xxxtra hard)"
						<< "\nUse arrows to change style" << endl;
					cout << "Стиль изменён на " << style << endl;
				}

			} while ((dif < 49) || (dif > 53));
		}

		if (dif == 49) // клавиша 1
		{
			height_of_jump = 5;
			time_of_hanging = 9;
		}
		else if (dif == 50) // клавиша 2
		{
			height_of_jump = 5;
			time_of_hanging = 8;
		}
		else if (dif == 51) // клавиша 3
		{
			height_of_jump = 5;
			time_of_hanging = 7;
		}
		else if (dif == 52) // клавиша 4
		{
			height_of_jump = 5;
			time_of_hanging = 6;
		}
		

		dc0 = 0 + rand() % 4;
		dc1 = 0 + rand() % 4;
		for (int i = 0; i < 1000; i++)
		{
			time_t ti;
			int seconds = time(&ti);
			
			if (style != 0)
			{
				if (dc0 == 0)
				{
					dc0 = 7 + rand() % 23;
					rc0 = 2 + rand() % 3;
				}
				dc0--;
				if (rc0 == 2)
				{
					//спавн облака 2
					a[85][0] = cloud_two[cloud0];
					cloud0++;
					if (cloud0 == 4)
					{
						cloud0 = 0;
						rc0 = 0;
					}
				}
				if (rc0 == 3)
				{
					//спавн облака 3
					a[85][0] = cloud_three[cloud0];
					cloud0++;
					if (cloud0 == 5)
					{
						cloud0 = 0;
						rc0 = 0;
					}
				}
				if (rc0 == 4)
				{
					//спавн облака 4
					a[85][0] = cloud_four[cloud0];
					cloud0++;
					if (cloud0 == 6)
					{
						cloud0 = 0;
						rc0 = 0;
					}
				}

				if (dc1 == 0)
				{
					dc1 = 7 + rand() % 23;
					rc1 = 2 + rand() % 3;
				}
				dc1--;
				if (rc1 == 2)
				{
					//спавн облака 2
					a[85][1] = cloud_two[cloud1];
					cloud1++;
					if (cloud1 == 4)
					{
						cloud1 = 0;
						rc1 = 0;
					}
				}
				if (rc1 == 3)
				{
					//спавн облака 3
					a[85][1] = cloud_three[cloud1];
					cloud1++;
					if (cloud1 == 5)
					{
						cloud1 = 0;
						rc1 = 0;
					}
				}
				if (rc1 == 4)
				{
					//спавн облака 4
					a[85][1] = cloud_four[cloud1];
					cloud1++;
					if (cloud1 == 6)
					{
						cloud1 = 0;
						rc1 = 0;
					}
				}
			}

			if ((i < 923) || (r != 0))
			{
				if (d == 0)
				{
					if (dif == 49) { d = 20 + rand() % 6; }
					else if (dif == 50) { d = 19 + rand() % 7; }
					else if (dif == 51) { d = 18 + rand() % 8; }
					else { d = 17 + rand() % 9; }
					r = 1 + rand() % 4;
				}
				d--;
				if (r == 1)
				{
					//спавн кактуса
					a[85][9] = kaktus_1[kaktus];
					a[85][10] = kaktus_2[kaktus];
					kaktus++;
					if (kaktus == 2)
					{
						kaktus = 0;
						r = 0;
					}
				}
				if (r == 2)
				{
					//спавн птиц
					a[85][4] = birds_1[birds];
					a[85][5] = birds_2[birds];
					a[85][6] = birds_3[birds];
					birds++;
					if (birds == 10)
					{
						birds = 0;
						r = 0;
					}
				}
				if (r == 3)
				{
					//спавн куста
					a[85][9] = brunch_1[brunch];
					a[85][10] = brunch_1[brunch];
					brunch++;
					if (brunch == 4)
					{
						brunch = 0;
						r = 0;
					}
				}
				if (r == 4)
				{
					//спавн древа
					a[85][8] = drevo_1[drevo];
					a[85][9] = drevo_2[drevo];
					a[85][10] = drevo_3[drevo];
					drevo++;
					if (drevo == 4)
					{
						drevo = 0;
						r = 0;
					}
				}
			}

			//конструктор драго
			loose = drago_constructor(drago_1, a, h/**/, 11, 13, loose);
			loose = drago_constructor(drago_2, a, h + 1, 5, 14, loose);
			loose = drago_constructor(drago_3, a, h + 2, 6, 14, loose);
			loose = drago_constructor(drago_4, a, h + 3, 9, 11, loose);

			if (loose)
			{
				a[11][h + 1] = "x";
				a[13][h + 1] = "x";
			}

			score++;

			print(a, h, zad, score, style);

			//деструктор драго
			drago_destructor(a, h, 11, 13);
			drago_destructor(a, h + 1, 5, 14);
			drago_destructor(a, h + 2, 6, 14);
			drago_destructor(a, h + 3, 9, 11);

			if (loose)
			{
				cout << "RIP" << endl;
				cout << "Your score: " << score << endl;
				break;
			}

			//течение
			stream(a);

			//определяемся с высотой
			if (_kbhit())
			{
				int kl = _getch();
				if ((kl == 32) && (t == 0)) // клавиша space
				{
					jump = true;
					t = 2 * height_of_jump + time_of_hanging - 1;
				}
				if ((kl == Right) || (kl == Left))
				{
					kl == Right ? style++ : style--;
					if (style < 0) { style = 2; }
					if (style > 2) { style = 0; }
				}
			}
			if (jump)
			{
				if (t >= height_of_jump + time_of_hanging)
				{
					h--;
				}
				else if (t <= height_of_jump)
				{
					h++;
				}
				t--;
				if (t == 0) { jump = false; }
			}

			//задержка
			if (zad != 0)
			{
				Sleep(zad);
				int seconds2 = time(&ti);
				if (seconds != seconds2) 
				{ zad -= 1; }
			}
		}
		if (!loose)
		{
			cout << "Congrats! You are alive" << endl;
			cout << "Your score: " << score << endl;

		}

		once = false;

		cout << "Choose the level of difficulty to play again (1 - easy, 2 - medium, 3 - hard, 4 - xxxtra hard), 5 - exit" 
			 <<"\nUse arrows to change style" << endl;
		do
		{
			dif = _getch();
			if ((dif == Right) || (dif == Left))
			{
				dif == Right ? style++ : style--;
				if (style < 0) { style = 2; }
				if (style > 2) { style = 0; }

				//конструктор драго
				loose = drago_constructor(drago_1, a, h/**/, 11, 13, loose);
				loose = drago_constructor(drago_2, a, h + 1, 5, 14, loose);
				loose = drago_constructor(drago_3, a, h + 2, 6, 14, loose);
				loose = drago_constructor(drago_4, a, h + 3, 9, 11, loose);

				print(a, h, zad, score, style);

				//деструктор драго
				drago_destructor(a, h, 11, 13);
				drago_destructor(a, h + 1, 5, 14);
				drago_destructor(a, h + 2, 6, 14);
				drago_destructor(a, h + 3, 9, 11);

				cout << "Choose the level of difficulty to play again (1 - easy, 2 - medium, 3 - hard, 4 - xxxtra hard), 5 - exit"
					<< "\n Use arrows to change style" << endl;
				cout << "Стиль изменён на " << style << endl;
			}

		} while ((dif < 49) || (dif > 53));

		if (dif == 53) // клавиша 5
		{
			break;
		}
	}


	/*
	cout << "_________________________________________________________________________________" << endl;
	for (int i = 0; i < SIZE; i++) { cout << bg1[i]; } cout << endl;
	for (int i = 0; i < SIZE; i++) { cout << bg1[i]; } cout << endl;
	cout << "                                                                                       " << endl;
	cout << "                                                                                       " << endl;//4
	cout << "                                                                                       " << endl;//5
	cout << "                                                                                       " << endl;//6
	cout << "          ___                                                     {~~~~}               " << endl;//7
	cout <<"    \\  __(o_o)                                ##                  {~~~~}               " << endl;//8
	cout <<"     \\(_____)~~               ##              ##                    ||                 " << endl;//9
	cout << "        | |                   ||              ||                    ||                 " << endl;//10
	cout << "\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'\"'" << endl;
	*/

	system("pause");
	return 0;
}