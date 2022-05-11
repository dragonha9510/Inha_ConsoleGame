#pragma once

#include "stdafx.h"

#define MAXCARDKINDS		10
#define PLAYERSTARTCARD		10

#define PLAYERINFOPOSX		104
#define PLAYERINFOPOSY		32
#define PLAYERINFOINTERVAL	17

#define CARDPOSX			10
#define FIRSTCARDPOSY		5

#define HANDCOUNT			5

typedef struct Player
{
	char m_chName[MAXBUFFER];

	int m_iOriForce;
	int m_iOrishiled;
	int m_iOriMaxHp;

	int m_iForce;
	int m_iShiled;
	int m_iHP;
	int m_iGold;
	int m_iMaxHP;
	int m_iCost;
	int m_iMaxCost;

	int m_iCard;
	int m_iHandCard;

	int m_iCursorPos;

	CCard* m_pCard;
	CCard* m_pAllCard;
	CCard* m_HandCard[HANDCOUNT];

	int m_iUseCardType;

	bool m_bChangeCard;
	bool m_bHandChange;
	bool m_bUseCard[HANDCOUNT];
	bool m_bRender;
}CPlayer;

int CheckWithCard(CPlayer* player, CCard card)
{
	player->m_iUseCardType = card.m_iCardType;
	switch (card.m_iCardType)
	{
	case SHILED:
		player->m_iShiled += card.m_iShiled;
		break;
	case BUFF:
		break;
	case SHUFFLE:
		break;
	case PLUSCOST:
		break;
	default:
		return _TRUE;
	}

	player->m_bRender = false;

	return _TRUE;
}

int InitPlayer(CPlayer* player)
{
	player->m_pAllCard = (CCard*)malloc(sizeof(CCard) * MAXCARDKINDS);
	GetCardInfo("CardInfo.txt", player->m_pAllCard);

	player->m_pCard = (CCard*)malloc(sizeof(CCard) * PLAYERSTARTCARD);
	InitPlayerCard(player->m_pCard, player->m_pAllCard, PLAYERSTARTCARD, MAXCARDKINDS);

	player->m_iCard = PLAYERSTARTCARD;

	strcpy(player->m_chName, "TESTPLAYER");
	player->m_iForce = player->m_iOriForce = 5;
	player->m_iShiled = player->m_iOrishiled = 0;
	player->m_iHP = 100;
	player->m_iGold = 0;
	player->m_iMaxHP = player->m_iOriMaxHp = 100;
	player->m_iCost = 3;
	player->m_iMaxCost = 3;
	player->m_bHandChange = true;

	player->m_iHandCard = HANDCOUNT;

	int arr[10];

	memset(arr, -1, sizeof(arr));
	bool SameNum = false;

	for (int i = 0; i < player->m_iHandCard;)
	{
		int iCnt = rand() % PLAYERSTARTCARD;

		for (int j = 0; j < player->m_iHandCard; ++j)
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
		if (!player->m_bUseCard[player->m_iCursorPos])
		{
			player->m_bUseCard[player->m_iCursorPos] = true;
			player->m_iCost -= (player->m_HandCard[player->m_iCursorPos])->m_iCost;
			player->m_bChangeCard = true;
			CheckWithCard(player, *(player->m_HandCard[player->m_iCursorPos]));
		}
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
		PrintCardName(player->m_HandCard, HANDCOUNT, player->m_bUseCard);
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
	printf("Str    : %d (+%d)", player->m_iOriForce, player->m_iForce - player->m_iOriForce);
	gotoxy(x + Xinterval, y);
	printf("Gold  : %d", player->m_iGold);
	gotoxy(x, ++y);
	printf("Shield : %d (+%d)", player->m_iOrishiled, player->m_iShiled - player->m_iOrishiled);
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
