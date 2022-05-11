#pragma once

#include "stdafx.h"

#define CARDCURSORX		10
#define CARDCURSORY		5
#define CARDINTERVAL	2
#define CARDMINNUM		0
#define CARDMAXNUM		9

typedef struct Dungeon
{
	int m_iCursorPos;
	int m_iCursorBlinkTime;
	bool m_bRender;
	CPlayer* m_pPlayer;
}CDungeon;

int InitDungeon(CDungeon* dungeon)
{
	if (NULLCHECKRETURN(dungeon->m_pPlayer))
	{
		dungeon->m_pPlayer = (CPlayer*)malloc(sizeof(CPlayer));
		
		if (NULLCHECKRETURN(dungeon->m_pPlayer))
			return _FAIL;

		memset(dungeon->m_pPlayer, 0, sizeof(CPlayer));

		InitPlayer(dungeon->m_pPlayer);
	}

	return _OK;
}

int DungeonUpdate(CDungeon* dungeon)
{
	if (chMessage == ARROWKEY)
	{
		chMessage = _getch();

		switch (chMessage)
		{
		case UP:
			gotoxy(CARDCURSORX, CARDCURSORY + (dungeon->m_iCursorPos * CARDINTERVAL));
			printf("  ");
			--(dungeon->m_iCursorPos);
			break;
		case DOWN:
			gotoxy(CARDCURSORX, CARDCURSORY + (dungeon->m_iCursorPos * CARDINTERVAL));
			printf("  ");
			++(dungeon->m_iCursorPos);
			break;
		default:
			return _ERROR;
		}

		if (dungeon->m_iCursorPos < CARDMINNUM)
			dungeon->m_iCursorPos = CARDMAXNUM;
		else if (dungeon->m_iCursorPos > CARDMAXNUM)
			dungeon->m_iCursorPos = CARDMINNUM;
	}
	else if (chMessage == ENTER || chMessage == SPACE)
	{
		return MENU;
	}

	return PLAY;
}

int DungeonLateUpdate(CDungeon* dungeon)
{
	gotoxy(CARDCURSORX, CARDCURSORY + (dungeon->m_iCursorPos * CARDINTERVAL));

	return _TRUE;
}

int DungeonRender(CDungeon* dungeon)
{
	if (CheckBlink(&(dungeon->m_iCursorBlinkTime), 300))
		printf("¢º");
	else
		printf("¢¹");

	if (!dungeon->m_pPlayer->m_bRender)
	{
		PlayerBaseRender(dungeon->m_pPlayer);
		dungeon->m_pPlayer->m_bRender = true;
	}

	return _TRUE;
}

void DungeonBaseRender(CDungeon* dungeon)
{
	gotoxy(0, 0);
	PrintASCIIImage("Dungeon.txt");
}

void SetDungeonRenderFalse(CDungeon* dungeon)
{
	dungeon->m_pPlayer->m_bRender = false;
}

void ReleaseDungeon(CDungeon* dungeon)
{
	if (!NULLCHECKRETURN(dungeon->m_pPlayer))
	{
		ReleasePlayer(dungeon->m_pPlayer);
		NULLCHECKFREE(dungeon->m_pPlayer);
	}
}