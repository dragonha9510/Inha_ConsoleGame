#pragma once

#include "stdafx.h"

typedef struct Dungeon
{
	int m_iCursorPos;
	CPlayer* m_pPlayer;
}CDungeon;

int DungeonUpdate(CDungeon* dungeon)
{
	if (chMessage == ARROWKEY)
	{
		chMessage = _getch();

		switch (chMessage)
		{
		case UP:
			gotoxy(10, 5 + (dungeon->m_iCursorPos * 2));
			printf("  ");
			--(dungeon->m_iCursorPos);
			break;
		case DOWN:
			gotoxy(10, 5 + (dungeon->m_iCursorPos * 2));
			printf("  ");
			++(dungeon->m_iCursorPos);
			break;
		default:
			return _ERROR;
		}

		if (dungeon->m_iCursorPos < 0)
			dungeon->m_iCursorPos = 9;
		else if (dungeon->m_iCursorPos > 9)
			dungeon->m_iCursorPos = 0;
	}
	else if (chMessage == ENTER || chMessage == SPACE)
		return MENU;

	return PLAY;
}

int DungeonLateUpdate(CDungeon* dungeon)
{
	gotoxy(10, 5 + (dungeon->m_iCursorPos * 2));
	printf("¢º");

	return _TRUE;
}

int DungeonRender()
{
	gotoxy(0, 0);
	PrintASCIIImage("Dungeon.txt");

	return _TRUE;
}