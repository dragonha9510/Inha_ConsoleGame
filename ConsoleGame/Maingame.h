#include "stdafx.h"


typedef struct MainGame
{
	CMainMenu* m_pMenu;
	bool m_bMenu;
	int m_iCheckScene;
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

	maingame->m_iCheckScene = MENU;
	maingame->m_bMenu = true;

	return _TRUE;
}

int Progress(CMainGame* maingame)
{
	switch (maingame->m_iCheckScene)
	{
	case PLAY:
		DungeonRender();
		maingame->m_iCheckScene = DungeonUpdate(NULL);
		DungeonLateUpdate();
		break;
	case LOAD:
		break;
	case CHALLENGE:
		break;
	case MENUEND:
		return _EXIT;
	case MENU:
		if (maingame->m_bMenu)
		{
			MenuRender(maingame->m_pMenu);
			maingame->m_bMenu = false;
		}
		
		maingame->m_iCheckScene = MenuUpdate(maingame->m_pMenu);

		if (maingame->m_iCheckScene != MENU)
			maingame->m_bMenu = true;

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
	if(!NULLCHECKRETURN(maingame)) 
		free(maingame);

	return _TRUE;
}