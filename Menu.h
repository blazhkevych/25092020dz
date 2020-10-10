#pragma once
#include <iostream>
#include <Windows.h>
#include <ctime>
#include <conio.h>
using namespace std;
#define MENUTOP 3
#define MENULEFT 20
#define BACKGROUND 16
#define FOREGROUND 8
#define SELECTITEM 9

void Gotorc(short r, short c) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(handle, { c,r });
}
void Color(unsigned short Back, unsigned short Forg) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	unsigned short c = ((Back & 0x0F) << 4) + (Forg & 0x0F);
	SetConsoleTextAttribute(handle, c);
}
void Paintmenu(const char** s, int sizem, int  pm) {
	system("cls");
	Gotorc(MENUTOP, MENULEFT);
	Color(BACKGROUND, FOREGROUND);
	for (size_t i = 0; i < sizem; i++)
	{
		Gotorc(MENUTOP + i + 1, MENULEFT);
		cout << (i == pm ? Color(BACKGROUND, SELECTITEM), "=>" : "  ");
		cout << s[i] << endl;
		Color(BACKGROUND, FOREGROUND);
	}
}
int Menu(const char** s, int sizem, int  pm = 0) {
	char c = 80;
	while (true)
	{
		if (c == 72 || c == 80) Paintmenu(s, sizem, pm);
		c = _getch();
		switch (c)
		{
		case 27: //esc
			return -1;
		case 80: //down
			pm++;
			if (pm == sizem) pm = 0;
			break;
		case 72: //up
			if (pm == 0) pm = sizem;
			pm--;
			break;
		case 13: //enter
			return pm;
		}
	}
}