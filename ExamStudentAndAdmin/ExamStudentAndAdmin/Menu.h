#pragma once
#include <vector>
#include <iostream>
#include<iomanip>
#include <string>
#include <conio.h>

#include "Functions.h"


class Menu
{
public:
	static int32_t select_vertical(std::vector <std::string> menu, HorizontalAlignment ha, short y = 12)
	{
		HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_SCREEN_BUFFER_INFO start_attribute;
		GetConsoleScreenBufferInfo(hStdOut, &start_attribute);
		short backColor = start_attribute.wAttributes & 15;
		short textColor = (start_attribute.wAttributes >>= 4) & 15;
		short maxLen = 0;
		for (int32_t i = 0; i < menu.size(); i++)
		{
			menu[i] = " " + menu[i] + " ";
			if (menu[i].length() > maxLen)
				maxLen = menu[i].length();
		}
		short x = 0;
		switch (ha)
		{
		case Center: x = 57 - maxLen / 2; break;
		case Left:   x = 0;	              break;
		case Right:  x = 80 - maxLen;     break;
		}
		char c{};
		short pos = 0;
		do
		{
			for (short i = 0; i < menu.size(); i++)
			{
				if (i == pos)
				{
					SetColor(textColor, backColor);
					gotoxy(x, y + i);
					std::cout << std::setw(maxLen) << std::left;
					gotoxy(x, y + i);
					std::cout << menu[i] << std::endl;
					SetColor(backColor, textColor);
				}
				else
				{
					SetColor(backColor, textColor);
					gotoxy(x, y + i);
					std::cout << std::setw(maxLen) << std::left;
					gotoxy(x, y + i);
					std::cout << menu[i] << std::endl;
					SetColor(textColor, backColor);
				}
			}
			c = _getch();
			switch (c)
			{
			case 72: if (pos > 0)               pos--; break; // up
			case 80: if (pos < menu.size() - 1) pos++; break; // down
			case 13: break;
			}
		} while (c != 13);

		for (short i = 0; i < 2; i++)
		{
			SetColor(backColor, textColor);
			gotoxy(x, y + pos);
			std::cout << std::setw(maxLen) << std::left;
			gotoxy(x, y + pos);
			std::cout << menu[pos] << std::endl;
			Sleep(200);
			SetColor(textColor, backColor);
			gotoxy(x, y + pos);
			std::cout << std::setw(maxLen) << std::left;
			gotoxy(x, y + pos);
			std::cout << menu[pos] << std::endl;
			SetColor(backColor, textColor);
			Sleep(200);
		}
		SetColor(backColor, textColor);
		system("cls");
		return pos;
	}

	short select_gorizontal(std::vector<std::string> menu)
	{
		size_t max_len = 0;
		for (short i = 0; i < menu.size(); i++)
			max_len += menu[i].length();
		if (max_len > 80 - menu.size() - 1)
			short a = 1;
	}
};