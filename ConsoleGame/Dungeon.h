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

#define MONSTERMAX		20

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
	int m_iChooseNum;

	int m_iMonsterCnt;

	bool m_bRender;
	bool m_bStoryMode;
	bool m_bActiveStory;
	bool m_bStory;
	bool m_bEndTurn;
	bool m_bMonsterDie;

	bool m_bMeetMonster;

	CStory m_cStoryCnt;
	CPlayer* m_pPlayer;
	CMonster* m_pMonsterList[MONSTERMAX];
}CDungeon;

int StoryLogic(CDungeon* dungeon)
{
	while(true)
	{
		if (dungeon->m_iCurStory == STORYEND)
			break;

		int RanStory = rand() % STORYEND;
	
		switch (RanStory)
		{
		case FIGHT:
		case FIGHTEND:
			if (dungeon->m_cStoryCnt.m_iEmerCnt < 3)
			{
				++dungeon->m_cStoryCnt.m_iEmerCnt;
				dungeon->m_cStoryCnt.m_iRestCnt = 0;
				dungeon->m_cStoryCnt.m_iShopCnt = 0;
				dungeon->m_cStoryCnt.m_iNormalCnt = 0;
				return RanStory;
			}
			break;
		case SHOP:
		case SHOPEND:
			if (!dungeon->m_cStoryCnt.m_iShopCnt)
			{
				++dungeon->m_cStoryCnt.m_iShopCnt;
				dungeon->m_cStoryCnt.m_iNormalCnt = 0;
				return RanStory;
			}
			break;
		case REST:
		case RESTEND:
			if (!dungeon->m_cStoryCnt.m_iRestCnt)
			{
				++dungeon->m_cStoryCnt.m_iRestCnt;
				dungeon->m_cStoryCnt.m_iNormalCnt = 0;
				return RanStory;
			}
			break;
		case NORMAL:
		case NORMALEND:
			if (!dungeon->m_cStoryCnt.m_iNormalCnt)
			{
				++dungeon->m_cStoryCnt.m_iNormalCnt;
				dungeon->m_cStoryCnt.m_iEmerCnt = 0;
				dungeon->m_cStoryCnt.m_iRestCnt = 0;
				dungeon->m_cStoryCnt.m_iShopCnt = 0;
				return RanStory;
			}
			break;
		}
	}

	return dungeon->m_iCurStory;
}

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
		dungeon->m_iMonsterCnt = 0;
		iStoryCnt = 0;
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
	if (MAXSTAGESTORY - iStoryCnt == 9)
	{
		gotoxy(2, 2);
		printf("              ");
	}
	gotoxy(2, 2);
	printf("남은 이야기 %d", MAXSTAGESTORY - iStoryCnt);

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
				default:
					dungeon->m_iChooseNum = dungeon->m_iStoryCursorPos - 1;
					break;
				}
				break;
			}
		}
	}
	else
	{
		// 스토리진행
		int iCheckStoryEnd = StoryRender(dungeon->m_iCurStory, &dungeon->m_bMeetMonster);
		
		if (iCheckStoryEnd == _ENDGAME)
			return MENU;

		if (dungeon->m_iCurStory == REST || dungeon->m_iCurStory == RESTEND)
		{
			PlayerRestHP(dungeon->m_pPlayer);

			PlayerBaseRender(dungeon->m_pPlayer);
		}

		else if ((dungeon->m_iCurStory == FIGHT) || (dungeon->m_iCurStory == FIGHTEND))
		{
			// Monster Info 출력
			MonsterInfoRender(dungeon->m_pMonsterList[dungeon->m_iMonsterCnt]);
		}
		dungeon->m_bActiveStory = iCheckStoryEnd;
		dungeon->m_bStoryMode = true;
		dungeon->m_bStory = false;
	}

	// 몬스터 공격 주고 받기
	if (dungeon->m_pPlayer->m_bAttack)
	{
		SetFightInfoToMonster(dungeon->m_pMonsterList[dungeon->m_iMonsterCnt], dungeon->m_pPlayer->m_FightInfo);
		dungeon->m_pPlayer->m_bAttack = false;

		// Monster Info 변경해서 출력
		MonsterInfoRenderClear();
		MonsterInfoRender(dungeon->m_pMonsterList[dungeon->m_iMonsterCnt]);
	}

	// 몬스터가 죽으면
	if (MonsterDeadReturn(dungeon->m_pMonsterList[dungeon->m_iMonsterCnt]))
	{
		PrintStoryMessage("(NULL) (은)는", "몬스터 (을)를 상대로 승리했다.");
		++dungeon->m_iMonsterCnt;
		dungeon->m_bMonsterDie = true;
		dungeon->m_bMeetMonster = false;
	}

	if (dungeon->m_iCurStory == SHOP || dungeon->m_iCurStory == SHOPEND)
	{
		if (0 <= dungeon->m_iChooseNum && dungeon->m_iChooseNum < 3)
		{

		}
	}

	return PLAY;
}

int DungeonLateUpdate(CDungeon* dungeon)
{
	if (dungeon->m_bEndTurn)
	{
		if(dungeon->m_bMeetMonster && !dungeon->m_bMonsterDie)
			SetFightInfoToPlayer(dungeon->m_pPlayer, GetMonsterFightInfo(dungeon->m_pMonsterList[dungeon->m_iMonsterCnt]));

		PlayerNewTurn(dungeon->m_pPlayer);
		dungeon->m_bStory = true;
		dungeon->m_bStoryMode = false;
		dungeon->m_iStoryCursorPos = 0;
		dungeon->m_iCursorPos = 0;


		// 플레이어 죽었으면 겜끝
		if (PlayerDeadReturn(dungeon->m_pPlayer))
			dungeon->m_iCurStory = STORYEND;
		else
			dungeon->m_iCurStory = FIGHT;

		dungeon->m_bEndTurn = false;

		// 몬스터 죽었으면 새로운 스토리라인 출력
		if (dungeon->m_bMonsterDie)
		{
			// Monster Info 삭제
			MonsterInfoRenderClear();

			dungeon->m_iCurStory = StoryLogic(dungeon);
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