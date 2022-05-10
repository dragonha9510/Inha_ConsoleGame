#pragma once

#include "stdafx.h"

typedef struct MAINMENU
{
	int m_iCursorPos;
	int m_iCursorBlink;
}CMainMenu;

int MenuUpdate(CMainMenu* mainmenu)
{
	if (chMessage == ARROWKEY)
	{
		chMessage = _getch();

		switch (chMessage)
		{
		case LEFT:
			gotoxy(26 + (mainmenu->m_iCursorPos * 26), 28);
			printf("  ");
			--(mainmenu->m_iCursorPos);
			break;
		case RIGHT:
			gotoxy(26 + (mainmenu->m_iCursorPos * 26), 28);
			printf("  ");
			++(mainmenu->m_iCursorPos);
			break;
		default:
			return _ERROR;
			break;
		}
		mainmenu->m_iCursorBlink = TRUE;

		if (mainmenu->m_iCursorPos < PLAY)
			mainmenu->m_iCursorPos = MENUEND;
		if (mainmenu->m_iCursorPos > MENUEND)
			mainmenu->m_iCursorPos = PLAY;
	}
	else if (chMessage == ENTER || chMessage == SPACE)
		return mainmenu->m_iCursorPos;

	return MENU;
}

int MenuLateUpdate(CMainMenu* mainmenu)
{
	gotoxy(26 + (mainmenu->m_iCursorPos * 26), 28);
	if (mainmenu->m_iCursorBlink)
	{
		printf("¢º");
		mainmenu->m_iCursorBlink = false;
	}
	else
	{
		printf("¢¹");
		mainmenu->m_iCursorBlink = true;
	}

	return _TRUE;
}

int MenuRender(CMainMenu* mainmenu)
{
	PrintASCIIImage("Menu.txt");

	return _TRUE;
}