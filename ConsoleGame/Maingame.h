#pragma once
#include "stdafx.h"


typedef struct MainGame
{
	int m_iCheckScene;

	CMainMenu* m_pMenu;
	bool m_bMenu;

	CDungeon* m_pDungeon;
	bool m_bDungeon;
}CMainGame;

int InitMain(CMainGame* maingame)
{
	if (!maingame)
	{
		maingame = (CMainGame*)malloc(sizeof(CMainGame));
		NULLCHECK(maingame);

		memset(maingame, 0, sizeof(CMainGame));
	}

	if (!maingame->m_pMenu)
	{
		maingame->m_pMenu = (CMainMenu*)malloc(sizeof(CMainMenu));

		if (NULLCHECKRETURN(maingame->m_pMenu))
		{
			free(maingame);
			exit(-1);
		}

		memset(maingame->m_pMenu, 0, sizeof(CMainMenu));
	}

	if (!maingame->m_pDungeon)
	{
		maingame->m_pDungeon = (CDungeon*)malloc(sizeof(CDungeon));

		if (NULLCHECKRETURN(maingame->m_pDungeon))
		{
			free(maingame);
			exit(-1);
		}

		memset(maingame->m_pDungeon, 0, sizeof(CDungeon));
	}

	maingame->m_iCheckScene = MENU;

	return _TRUE;
}

int Progress(CMainGame* maingame)
{
	switch (maingame->m_iCheckScene)
	{
	case PLAY:
		if (!maingame->m_bDungeon)
		{
			system("cls");
			DungeonRender();
			maingame->m_bDungeon = true;
		}
		maingame->m_iCheckScene = DungeonUpdate(maingame->m_pDungeon);
		DungeonLateUpdate(maingame->m_pDungeon);

		if (maingame->m_iCheckScene != PLAY)
			maingame->m_bDungeon = false;
		break;
	case LOAD:

		break;
	case CHALLENGE:

		break;
	case MENUEND:
		return _EXIT;
	case MENU:
		if (!maingame->m_bMenu)
		{
			system("cls");
			MenuRender(maingame->m_pMenu);
			maingame->m_bMenu = true;
		}
		
		maingame->m_iCheckScene = MenuUpdate(maingame->m_pMenu);

		if (maingame->m_iCheckScene != MENU)
			maingame->m_bMenu = false;

		MenuLateUpdate(maingame->m_pMenu);
		break;
	case _EXIT:
		return _EXIT;
	default:
		return _ERROR;
	}
	return _TRUE;
}

int Release(CMainGame* maingame)
{
	if(!NULLCHECKRETURN(maingame->m_pMenu))
		free(maingame->m_pMenu);
	if (!NULLCHECKRETURN(maingame->m_pDungeon))
		free(maingame->m_pDungeon);
	if(!NULLCHECKRETURN(maingame)) 
		free(maingame);

	return _TRUE;
}