#pragma once

#include "stdafx.h"

#define MAXCARDKINDS		10
#define PLAYERSTARTCARD		10

#define PLAYERINFOPOSX		104
#define PLAYERINFOPOSY		32
#define PLAYERINFOINTERVAL	17

#define CARDPOSX			10
#define FIRSTCARDPOSY		5

typedef struct Player
{
	char m_chName[MAXBUFFER];

	int m_iForce;
	int m_iShiled;
	int m_iHP;
	int m_iGold;
	int m_iMaxHP;
	int m_iCost;
	int m_iCard;

	int m_iCursorPos;

	CCard* m_pCard;
	CCard* m_pAllCard;
	CCard* m_HandCard[5];

	bool m_bChangeCard;
	bool m_bHandChange;
	bool m_bUseCard[5];
	bool m_bRender;
}CPlayer;

int InitPlayer(CPlayer* player)
{
	player->m_pAllCard = (CCard*)malloc(sizeof(CCard) * MAXCARDKINDS);
	GetCardInfo("CardInfo.txt", player->m_pAllCard);

	player->m_pCard = (CCard*)malloc(sizeof(CCard) * PLAYERSTARTCARD);
	InitPlayerCard(player->m_pCard, player->m_pAllCard, PLAYERSTARTCARD, MAXCARDKINDS);

	player->m_iCard = PLAYERSTARTCARD;

	strcpy(player->m_chName, "TESTPLAYER");
	player->m_iForce = 5;
	player->m_iShiled = 0;
	player->m_iHP = 100;
	player->m_iGold = 0;
	player->m_iMaxHP = 100;
	player->m_iCost = 3;

	player->m_bHandChange = true;

	int arr[5] = { -1, -1, -1, -1, -1 };
	bool SameNum = false;

	for (int i = 0; i < 5;)
	{
		int iCnt = rand() % 10;

		for (int j = 0; j < 5; ++j)
		{
			if (arr[j] == iCnt)
			{
				SameNum = true;
				break;
			}
		}

		if (SameNum)
		{
			SameNum = false;
			continue;
		}

		arr[i] = iCnt;
		player->m_HandCard[i] = (player->m_pCard + arr[i]);
		++i;
	}

	player->m_bChangeCard = true;

	return _TRUE;
}

int PlayerUpdate(CPlayer* player)
{
	if (chMessage == SPACE)
	{
		player->m_bUseCard[player->m_iCursorPos] = true;
		player->m_bChangeCard = true;
	}
	return _TRUE;
}

int PlayerLateUpdate(CPlayer* player)
{
	return _TRUE;
}

int PlayerRender(CPlayer* player)
{
	if (player->m_bHandChange || player->m_bChangeCard)
	{
		PrintCardName(player->m_HandCard, 5, player->m_bUseCard);
		player->m_bHandChange = false;
	}

	PrintCardInfo(*(player->m_HandCard[player->m_iCursorPos]));

	return _TRUE;
}

int PlayerBaseRender(CPlayer* player)
{
	int x = PLAYERINFOPOSX;
	int y = PLAYERINFOPOSY;
	int Xinterval = PLAYERINFOINTERVAL;

	gotoxy(x + Xinterval, y);
	printf("HP / Max : %d / %d", player->m_iHP, player->m_iMaxHP);
	gotoxy(x, y++);
	printf("%s", player->m_chName);
	gotoxy(x, ++y);
	printf("Str    : %d", player->m_iForce);
	gotoxy(x + Xinterval, y);
	printf("Gold  : %d", player->m_iGold);
	gotoxy(x, ++y);
	printf("Shield : %d", player->m_iShiled);
	gotoxy(x, ++y);
	printf("Card   : %d", player->m_iCard);

	return _TRUE;
}

int ReleasePlayer(CPlayer* player)
{
	NULLCHECKFREE(player->m_pAllCard);
	NULLCHECKFREE(player->m_pCard);
	return _TRUE;
}