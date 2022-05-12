#pragma once

#include "stdafx.h"

#define CARDCURSORX		10
#define CARDCURSORY		5
#define CARDINTERVAL	25
#define CARDMINNUM		0
#define CARDMAXNUM		4

#define STORYCURSORX	47
#define STORYCURSORY	27
#define STORYINTERVAL	20

#define ENDTURN			0
#define CHOOSE1			1
#define CHOOSE2			2
#define CHOOSE3			3
#define ENDGAME			4

typedef struct Dungeon
{
	int m_iCursorPos;
	int m_iStoryCursorPos;
	int m_iCursorBlinkTime;
	bool m_bRender;
	bool m_bStoryMode;
	bool m_bStory;
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
		dungeon->m_iCursorPos = 0;
		dungeon->m_iStoryCursorPos = -1;
		dungeon->m_pPlayer->m_iCursorPos = dungeon->m_iCursorPos;
		dungeon->m_bStoryMode = false;
	}

	return _OK;
}

int DungeonUpdate(CDungeon* dungeon)
{
	if (chMessage == ARROWKEY)
	{
		chMessage = _getch();

		gotoxy(CARDCURSORX, CARDCURSORY + (dungeon->m_iCursorPos * (CARDINTERVAL / dungeon->m_pPlayer->m_iHandCard)));
		printf("  ");

		gotoxy(STORYCURSORX + STORYINTERVAL * dungeon->m_iStoryCursorPos, STORYCURSORY);
		printf("  ");

		switch (chMessage)
		{
		case UP:
			if (!dungeon->m_bStoryMode)
				--(dungeon->m_iCursorPos);
			break;
		case DOWN:
			if (!dungeon->m_bStoryMode)
				++(dungeon->m_iCursorPos);
			break;
		case LEFT:
			if (dungeon->m_bStoryMode)
			{
				if (--dungeon->m_iStoryCursorPos < 0)
				{
					dungeon->m_iStoryCursorPos = -1;
					dungeon->m_bStoryMode = false;
				}
			}
			break;
		case RIGHT:
			if (++dungeon->m_iStoryCursorPos >= 0)
			{
				dungeon->m_bStoryMode = true;
			}
			if (dungeon->m_iStoryCursorPos > ENDGAME)
				dungeon->m_iStoryCursorPos = ENDGAME;
			break;
		default:
			return _ERROR;
		}

		if (chMessage == LEFT || chMessage == RIGHT)
		{
			if(dungeon->m_iCursorPos > dungeon->m_pPlayer->m_iHandCard - 1)
				dungeon->m_bStoryMode = true;
		}
		else
		{
			if (dungeon->m_iCursorPos < CARDMINNUM)
				dungeon->m_iCursorPos = dungeon->m_pPlayer->m_iHandCard - 1;
			else if (dungeon->m_iCursorPos > dungeon->m_pPlayer->m_iHandCard - 1)
				dungeon->m_iCursorPos = CARDMINNUM;
		}
	}

	if(!dungeon->m_bStoryMode)
		PlayerUpdate(dungeon->m_pPlayer);

	else if(dungeon->m_bStoryMode)
	{
		switch (chMessage)
		{
		case SPACE:
			gotoxy(STORYCURSORX + STORYINTERVAL * dungeon->m_iStoryCursorPos, STORYCURSORY);
			printf("  ");

			switch (dungeon->m_iStoryCursorPos)
			{
			case ENDTURN:
				PlayerNewTurn(dungeon->m_pPlayer);
				dungeon->m_bStory = true;
				dungeon->m_bStoryMode = false;
				dungeon->m_iStoryCursorPos = -1;
				break;
			case ENDGAME:
				return MENU;
			}
			break;
		}
	}

	return PLAY;
}

int DungeonLateUpdate(CDungeon* dungeon)
{
	if (dungeon->m_pPlayer->m_iCursorPos != dungeon->m_iCursorPos 
		&& (dungeon->m_iCursorPos < dungeon->m_pPlayer->m_iHandCard))
	{
		dungeon->m_pPlayer->m_iCursorPos = dungeon->m_iCursorPos;
		dungeon->m_pPlayer->m_bChangeCard = true;
	}


	if (dungeon->m_bStoryMode)
	{
		gotoxy(CARDCURSORX, CARDCURSORY + (dungeon->m_iCursorPos * (CARDINTERVAL / dungeon->m_pPlayer->m_iHandCard)));

		printf("  ");

		gotoxy(STORYCURSORX + STORYINTERVAL * dungeon->m_iStoryCursorPos, STORYCURSORY);
	}
	else
	{
		gotoxy(STORYCURSORX + STORYINTERVAL * dungeon->m_iStoryCursorPos, STORYCURSORY);

		printf("  ");

		gotoxy(CARDCURSORX, CARDCURSORY + (dungeon->m_iCursorPos * (CARDINTERVAL / dungeon->m_pPlayer->m_iHandCard)));
	}

	return _TRUE;
}

int DungeonRender(CDungeon* dungeon)
{
	if (!dungeon->m_bStoryMode)
	{
		if (CheckBlink(&(dungeon->m_iCursorBlinkTime), 250))
			printf("▶");
		else
			printf("▷");

		if (dungeon->m_pPlayer->m_bChangeCard)
		{
			PlayerRender(dungeon->m_pPlayer);
			dungeon->m_pPlayer->m_bChangeCard = false;
		}

		if (!dungeon->m_pPlayer->m_bRender)
		{
			PlayerBaseRender(dungeon->m_pPlayer);
			dungeon->m_pPlayer->m_bRender = true;
		}
	}
	else
	{
		if (CheckBlink(&(dungeon->m_iCursorBlinkTime), 250))
			printf("▶");
		else
			printf("▷");
	}

	return _TRUE;
}

void DungeonBaseRender(CDungeon* dungeon)
{
	gotoxy(0, 0);
	PrintASCIIImage("Dungeon.txt");

	gotoxy(STORYCURSORX + 5, STORYCURSORY);
	printf("턴 종료");
	
	gotoxy(STORYCURSORX + STORYINTERVAL + 5, STORYCURSORY);
	printf("선택 (1)");

	gotoxy(STORYCURSORX + (STORYINTERVAL * 2) + 5, STORYCURSORY);
	printf("선택 (2)");

	gotoxy(STORYCURSORX + (STORYINTERVAL * 3) + 5, STORYCURSORY);
	printf("선택 (3)");

	gotoxy(STORYCURSORX + (STORYINTERVAL * 4) + 5, STORYCURSORY);
	printf("게임 종료");
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