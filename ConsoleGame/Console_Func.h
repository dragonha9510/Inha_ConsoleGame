#pragma once

#include "stdafx.h"

#ifndef _CONSOLE_FUNC_
#define _CONSOLE_FUNC_

enum ColorType {
	BLACK,  	//0
	DARKBLUE,	//1
	DARKGREEN,	//2
	DARKSKYBLUE,//3
	DARKRED,  	//4
	DARKPURPLE,	//5
	DARKYELLOW,	//6
	GRAY,		//7
	DARKGRAY,	//8
	BLUE,		//9
	GREEN,		//10
	SKYBLUE,	//11
	RED,		//12
	PURPLE,		//13
	YELLOW,		//14
	WHITE		//15
} COLOR;

void textcolor(int colorNum)
{
	SetConsoleTextAttribute(g_COUT, colorNum);
}

void clearconsole()
{
	COORD Coor = { 0, 0 };
	DWORD dw;
	FillConsoleOutputCharacter(g_COUT, ' ', 800 * 600, Coor, &dw); // 콘솔창 화면을 지운다.
}

void SetConsoleInputMode(DWORD* mode, int process)
{
	// Console Input Mode Get
	GetConsoleMode(g_CIN, mode);
	// Console Input Mode Change ( to Mouse )
	SetConsoleMode(g_CIN, *mode | process);
}

DWORD CheckMouseInput(INPUT_RECORD* mouse)
{
	INPUT_RECORD input_record;
	DWORD input_count;

	PeekConsoleInput(g_CIN, &input_record, 1, &input_count);
	return input_count;
}

int GetMousePos(COORD* mousePos)
{
	INPUT_RECORD cinRec;	// Input Record
	DWORD input_count;

	ReadConsoleInput(g_CIN, &cinRec, 1, &input_count);

	mousePos->X = cinRec.Event.MouseEvent.dwMousePosition.X;
	mousePos->Y = cinRec.Event.MouseEvent.dwMousePosition.Y;

	return cinRec.EventType;
}

DWORD GetMouseEvent()
{
	INPUT_RECORD input_record;
	DWORD input_count;

	ReadConsoleInput(g_CIN, &input_record, 1, &input_count);
	if (input_record.EventType == MOUSE_EVENT)
	{
		if (input_record.Event.MouseEvent.dwButtonState & FROM_LEFT_1ST_BUTTON_PRESSED)
		{
			CONSOLE_SCREEN_BUFFER_INFO csbi;

			GetConsoleScreenBufferInfo(g_COUT, &csbi);

			return MOUSE_EVENT;
		}
	}

	return 0;
}

void gotoxy(int x, int y)      // 좌표 보내기 gotoxy
{
	COORD Cur;
	Cur.X = x;
	Cur.Y = y;
	SetConsoleCursorPosition(g_COUT, Cur);
}

int GetKeyInputMessage()
{
	if (_kbhit())
	{
		chMessage = _getch();
	}
	else
		return '\0';

	return chMessage;
}

int CheckBlink(int* time, int blinktime)
{
	if (!(*time))
		(*time) = (int)GetTickCount64();

	if ((int)GetTickCount64() - (*time) < blinktime)
		return 1;
	else if ((int)GetTickCount64() - (*time) > DOUBLE(blinktime))
	{
		(*time) = 0;
		return 1;
	}
	else
		return 0;
}

#endif // _CONSOLE_FUNC_