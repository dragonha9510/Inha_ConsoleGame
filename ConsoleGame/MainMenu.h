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
	{
		return mainmenu->m_iCursorPos;
	}

	return MENU;
}

int MenuLateUpdate(CMainMenu* mainmenu)
{
	gotoxy(26 + (mainmenu->m_iCursorPos * 26), 28);
	if (mainmenu->m_iCursorBlink)
	{
		printf("▶");
		mainmenu->m_iCursorBlink = false;
	}
	else
	{
		printf("▷");
		mainmenu->m_iCursorBlink = true;
	}

	return _TRUE;
}

int MenuRender(CMainMenu* mainmenu)
{
	printf("======================================================================================================================================================\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                _______.__           ___     ____    ____                            _______..______   __.  ______       _______                  ||\n");
	printf("||              /       ||  |         /   \\    \\   \\  /   /                           /       ||   _  \\ |  | |   _  \\     |   ____|                 ||\n");
	printf("||             |   (----`|  |        /  ^  \\    \\   \\/   /                           |   (----`| | _) | |  | |  |_)  |    |  |__                    ||\n");
	printf("||              \\   \\    |  |       /  /_\\  \\    \\_    _/                             \\   \\    |  ___/  |  | |      /     |   __|                   ||\n");
	printf("||          .----)   |   |  `----. / _____   \\     |  |                           .----)   |   | |      |  | | |\\  \\----. |  |____                  ||\n");
	printf("||          |_______/    |_______|/__ /    \\__\\    |__|      _    _               | _______/   |_|      |__| |_| `._____| |_______|                 ||\n");
	printf("||                                                          | |  | |                                                                                ||\n");
	printf("||                                                          | |_ | |__    ___                                                                       ||\n");
	printf("||                                                          | __|| '_ \\  / _ \\                                                                      ||\n");
	printf("||                                                          | |_ | | | ||  __ /                                                                     ||\n");
	printf("||                                                          \\__ ||_| |_| \\___|                                                                      ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                              새로운 모험               이어하기                  도전과제                  종료하기                              ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("||                                                                                                                                                  ||\n");
	printf("======================================================================================================================================================\n");

	return _TRUE;
}