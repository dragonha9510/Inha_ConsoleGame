#pragma once

#include "stdafx.h"

#define MENUCURSORX		26
#define MENUCURSORY		28
#define MENUINTERVAL	26

typedef struct MAINMENU
{
	int m_iCursorPos;
	int m_iCursorBlinkTime;
	bool m_bRender;
}CMainMenu;

int MenuUpdate(CMainMenu* mainmenu)
{
	if (chMessage == ARROWKEY)
	{
		chMessage = _getch();

		switch (chMessage)
		{
		case LEFT:
			gotoxy(MENUCURSORX + (mainmenu->m_iCursorPos * MENUINTERVAL), MENUCURSORY);
			printf("  ");
			--(mainmenu->m_iCursorPos);
			break;
		case RIGHT:
			gotoxy(MENUCURSORX + (mainmenu->m_iCursorPos * MENUINTERVAL), MENUCURSORY);
			printf("  ");
			++(mainmenu->m_iCursorPos);
			break;
		default:
			return _ERROR;
			break;
		}
		mainmenu->m_iCursorBlinkTime = 0;

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
	gotoxy(MENUCURSORX + (mainmenu->m_iCursorPos * MENUINTERVAL), MENUCURSORY);

	return _TRUE;
}

int MenuRender(CMainMenu* mainmenu)
{
	if (CheckBlink(&(mainmenu->m_iCursorBlinkTime), 300))
		printf("¢º");
	else
		printf("¢¹");

	return _TRUE;
}

void MenuBaseRender()
{
	PrintASCIIImage("Menu.txt");
}