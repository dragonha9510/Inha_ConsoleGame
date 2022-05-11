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
	bool bFailtoInit = false;

	if (NULLCHECKRETURN(maingame))
	{
		maingame = (CMainGame*)malloc(sizeof(CMainGame));
		NULLCHECK(maingame);

		memset(maingame, 0, sizeof(CMainGame));
	}

	if (NULLCHECKRETURN(maingame->m_pMenu) && !bFailtoInit)
	{
		maingame->m_pMenu = (CMainMenu*)malloc(sizeof(CMainMenu));

		if (bFailtoInit = NULLCHECKRETURN(maingame->m_pMenu));
		else
			memset(maingame->m_pMenu, 0, sizeof(CMainMenu));
	}

	if (NULLCHECKRETURN(maingame->m_pDungeon) && !bFailtoInit)
	{
		maingame->m_pDungeon = (CDungeon*)malloc(sizeof(CDungeon));

		if (bFailtoInit = NULLCHECKRETURN(maingame->m_pDungeon));
		else
			memset(maingame->m_pDungeon, 0, sizeof(CDungeon));
	}

	if (bFailtoInit) 
	{
		NULLCHECKFREE(maingame->m_pMenu)
		NULLCHECKFREE(maingame->m_pDungeon)

		free(maingame);

		exit(_ERROR);
	} 
	// exit(_ERROR);

	maingame->m_iCheckScene = MENU;

	return _TRUE;
}

int Progress(CMainGame* maingame)
{
	switch (maingame->m_iCheckScene)
	{
	case PLAY:
		InitDungeon(maingame->m_pDungeon);
		if (!maingame->m_pDungeon->m_bRender)
		{
			system("cls");
			DungeonBaseRender(maingame->m_pDungeon);
			maingame->m_pDungeon->m_bRender = true;
		}
		maingame->m_iCheckScene = DungeonUpdate(maingame->m_pDungeon);
		DungeonLateUpdate(maingame->m_pDungeon);
		DungeonRender(maingame->m_pDungeon);

		if (maingame->m_iCheckScene != PLAY)
		{
			ReleaseDungeon(maingame->m_pDungeon);
			maingame->m_pDungeon->m_bRender = false;
		}
		break;
	case LOAD:

		break;
	case CHALLENGE:

		break;
	case MENUEND:
		return _EXIT;
	case MENU:
		if (!maingame->m_pMenu->m_bRender)
		{
			system("cls");
			MenuBaseRender();
			maingame->m_pMenu->m_bRender = true;
		}
		
		maingame->m_iCheckScene = MenuUpdate(maingame->m_pMenu);
		MenuLateUpdate(maingame->m_pMenu);
		MenuRender(maingame->m_pMenu);

		if (maingame->m_iCheckScene != MENU)
			maingame->m_pMenu->m_bRender = false;
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
	NULLCHECKFREE(maingame->m_pMenu);
	if (!NULLCHECKRETURN(maingame->m_pDungeon))
	{
		ReleaseDungeon(maingame->m_pDungeon);
		NULLCHECKFREE(maingame->m_pDungeon);
	}
	NULLCHECKFREE(maingame);

	return _TRUE;
}