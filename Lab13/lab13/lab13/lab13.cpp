// lab13.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// защита информации (пароль)

#include "pch.h"
#include <iostream>
#include <windows.h>
#include <cstdio>
#include <fstream>
#include <cstdlib>
#include "string.h"
#include "conio.h"

#define STRLEN(x) (sizeof(x)/sizeof(TCHAR)-1)

using namespace std;

ifstream file("F:\\6 семестр\\ОСиСП\\лабы\\Lab13\\output.txt");
HANDLE output;
COORD cursor;
int x = 3;
int y = 3;
const TCHAR szMsg[] = L"Введите пароль:";
char carr[5], password[6];
DWORD dwCount = 0;
int main()
{
	setlocale(NULL, "RUS");
	output = GetStdHandle(STD_OUTPUT_HANDLE);
	cursor.X = x;
	cursor.Y = y;
	SetConsoleCursorPosition(output, cursor);
	WriteConsole(output, &szMsg, STRLEN(szMsg), &dwCount, NULL);
	cursor.Y++;
	SetConsoleCursorPosition(output, cursor);
	char ch;
	file.getline(password, 6);
	file.close();
	int i = 0;
	bool priz = true;
	for (i; i < 5; i++)
	{
		ch = getchar();
		carr[i] = ch;
		switch (i)
			{
			case 0:
				if (!(ch == password[i])) {
					priz = false;
					break;
				}
				break;

			case 1:
				if (!(ch == password[i])) {
					priz = false;
					break;
				}
				break;
			case 2:
				if (!(ch == password[i])) {
					priz = false;
					break;
				}
				break;

			case 3:
				if (!(ch == password[i])) {
					priz = false;
					break;
				}
				break;
			case 4:
				if (!(ch == password[i])) {
					priz = false;
					break;
				}
				break;
			default: {
				priz = false;
				break;
			}
			}

		ch = '*';

		SetConsoleCursorPosition(output, cursor);
		printf("%c", ch);

		cursor.X++;
	}

	if (priz)
	{
		cursor.Y++;
		SetConsoleCursorPosition(output, cursor);
		cout << "OK! Пароли совпадают." << std::endl;
	}
	else
	{
		cursor.Y++;
		SetConsoleCursorPosition(output, cursor);
		cout << "GAME OVER! Введенный пароль не соответствует паролю из файла." << std::endl;
	}
	return 0;
}
