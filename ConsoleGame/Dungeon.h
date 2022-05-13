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

#define MONSTERMAX		10

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
	int m_iCurStory;

	bool m_bRender;
	bool m_bStoryMode;
	bool m_bActiveStory;
	bool m_bStory;
	bool m_bEndTurn;
	bool m_bMonsterDie;

	CPlayer* m_pPlayer;
	CMonster* m_pMonsterList[MONSTERMAX];
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
		dungeon->m_iCurStory = NORMAL;

		dungeon->m_bActiveStory = true;
	}

	for (int i = 0; i < MONSTERMAX; ++i)
	{
		if(NULLCHECKRETURN(dungeon->m_pMonsterList[i]))
			dungeon->m_pMonsterList[i] = MakeMonster(10 * (i + 1), 5 * (i + 1), 5 * (i + 1), 5 * (i + 1));
	}

	return _OK;
}

int DungeonUpdate(CDungeon* dungeon)
{
	if (!dungeon->m_bActiveStory)
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
				if (dungeon->m_iCursorPos > dungeon->m_pPlayer->m_iHandCard - 1)
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

		if (!dungeon->m_bStoryMode)
		{
			PlayerUpdate(dungeon->m_pPlayer);
		}


		if (!dungeon->m_bStory)
		{
			switch (chMessage)
			{
			case SPACE:
				gotoxy(STORYCURSORX + STORYINTERVAL * dungeon->m_iStoryCursorPos, STORYCURSORY);
				printf("  ");

				switch (dungeon->m_iStoryCursorPos)
				{
				case ENDTURN:
					dungeon->m_bEndTurn = true;
					dungeon->m_bActiveStory = true;
					break;
				case ENDGAME:
					return MENU;
				}
				break;
			}
		}

	}
	else
	{
		// 스토리진행
		int iCheckStoryEnd = StoryRender(dungeon->m_iCurStory, 0);
		
		if (iCheckStoryEnd == _ENDGAME)
			return MENU;

		dungeon->m_bActiveStory = iCheckStoryEnd;
		dungeon->m_bStoryMode = true;
		dungeon->m_bStory = false;

		// 몬스터 공격 주고 받기

		// 몬스터가 죽으면
		dungeon->m_bMonsterDie = true;
	}

	return PLAY;
}

int DungeonLateUpdate(CDungeon* dungeon)
{
	if (dungeon->m_bEndTurn)
	{
		PlayerNewTurn(dungeon->m_pPlayer);
		dungeon->m_bStory = true;
		dungeon->m_bStoryMode = false;
		dungeon->m_iStoryCursorPos = 0;
		dungeon->m_iCursorPos = 0;
		if (PlayerDeadReturn(dungeon->m_pPlayer))
			dungeon->m_iCurStory = STORYEND;
		else
			dungeon->m_iCurStory = FIGHT;

		dungeon->m_bEndTurn = false;

		if (dungeon->m_bMonsterDie)
		{
			dungeon->m_iCurStory = NORMAL;
			dungeon->m_bMonsterDie = false;
		}
	}

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
		for (int i = 0; i < MONSTERMAX; ++i)
		{
			NULLCHECKFREE(dungeon->m_pMonsterList[i]);
		}
		ReleasePlayer(dungeon->m_pPlayer);
		NULLCHECKFREE(dungeon->m_pPlayer);
	}
}