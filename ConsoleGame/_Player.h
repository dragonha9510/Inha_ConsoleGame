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
#define HANDCARDMAX			10

int arr[HANDCARDMAX] = {-1, -1, -1, -1, -1, -1, -1, -1, -1, -1};

typedef struct Player
{
	char m_chName[MAXBUFFER];

	int m_iOriForce;
	int m_iOriShield;
	int m_iOriMaxHp;

	int m_iForce;
	int m_iShield;
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
	CCard* m_HandCard[HANDCARDMAX];

	int m_iUseCardType;

	bool m_bAttack;

	bool m_bChangeCard;
	bool m_bHandChange;
	bool m_bUseCard[HANDCARDMAX];
	bool m_bRender;
}CPlayer;

void ShuffleNewCard(CCard* handarr[], CCard* allcard, int cnt, int maxcardcnt);
void AddNewCard(CCard* handarr[], CCard* allcard, int cnt, int maxcardcnt, int curcnt);
int CheckWithCard(CPlayer* player, CCard card);
void PlayerNewTurn(CPlayer* player);

int InitPlayer(CPlayer* player)
{
	player->m_pAllCard = (CCard*)malloc(sizeof(CCard) * MAXCARDKINDS);
	GetCardInfo("CardInfo.txt", player->m_pAllCard);

	player->m_pCard = (CCard*)malloc(sizeof(CCard) * PLAYERSTARTCARD);
	InitPlayerCard(player->m_pCard, player->m_pAllCard, PLAYERSTARTCARD, MAXCARDKINDS);

	player->m_iCard = PLAYERSTARTCARD;

	strcpy(player->m_chName, "TESTPLAYER");

	player->m_iForce	= player->m_iOriForce	= 5;
	player->m_iShield	= player->m_iOriShield	= 0;
	player->m_iMaxHP	= player->m_iOriMaxHp	= 100;
	player->m_iHP								= 100;
	player->m_iGold								= 0;
	player->m_iCost								= 3;
	player->m_iMaxCost							= 3;
	player->m_bHandChange						= true;

	player->m_iHandCard = HANDCOUNT;

	ShuffleNewCard(player->m_HandCard, player->m_pCard, HANDCOUNT, MAXCARDKINDS);

	player->m_bChangeCard = true;

	return _TRUE;
}

int PlayerUpdate(CPlayer* player)
{
	if (chMessage == SPACE)
	{
		if (!player->m_bUseCard[player->m_iCursorPos]
			&& player->m_iCost - (player->m_HandCard[player->m_iCursorPos])->m_iCost >= 0)
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
		PrintCardName(player->m_HandCard, player->m_iHandCard, player->m_bUseCard);
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
	printf("Shield : %d (+%d)", player->m_iOriShield, player->m_iShield - player->m_iOriShield);
	gotoxy(x, ++y);
	printf("Card   : %d", player->m_iCard - player->m_iHandCard);
	gotoxy(x + Xinterval, y);
	printf("Cost   : %d / %d", player->m_iCost, player->m_iMaxCost);

	return _TRUE;
}

int ReleasePlayer(CPlayer* player)
{
	NULLCHECKFREE(player->m_pAllCard);
	NULLCHECKFREE(player->m_pCard);
	return _TRUE;
}

int CheckWithCard(CPlayer* player, CCard card)
{
	char temp[10];
	int iDmg = card.m_iDmg + player->m_iForce;
	player->m_iUseCardType = card.m_iCardType;
	PrintStoryMessage(card.m_chCardName, " (을)를 사용했다.");

	switch (card.m_iCardType)
	{
	case ATTACK:
		player->m_bAttack = true;
		break;
	case SHIELD:
		player->m_iShield += card.m_iShield;
		break;
	case BUFF:
		break;
	case SHUFFLE:
		if (player->m_iHandCard == HANDCARDMAX)
		{
			player->m_bUseCard[player->m_iCursorPos] = false;
			player->m_iCost += card.m_iCost;
			player->m_bChangeCard = false;
			return _TRUE;
		}
		AddNewCard(player->m_HandCard, player->m_pCard, card.m_iDmg, player->m_iCard, player->m_iHandCard);
		player->m_iHandCard += card.m_iDmg;

		iDmg = card.m_iDmg;

		if (player->m_iHandCard > HANDCARDMAX)
		{
			iDmg = card.m_iDmg - HANDCARDMAX - player->m_iHandCard;
			player->m_iHandCard = HANDCARDMAX;
		}

		sprintf(temp, "%d", iDmg);
		PrintStoryMessage(temp, " 장 (을)를 뽑았다.");
		break;
	case PLUSCOST:
		player->m_iCost += card.m_iCost * 2;
		break;
	default:
		break;
	}

	if (card.m_iDmg != 0 && card.m_iCardType != SHUFFLE)
	{
		sprintf(temp, "%d", iDmg);
		PrintStoryMessage(temp, " 만큼 공격했다.");
	}
	if (card.m_iShield != 0)
	{
		sprintf(temp, "%d", card.m_iShield);
		PrintStoryMessage(temp, " 만큼 Shield(방어력) (을)를 얻었다.");
	}
	if (card.m_iDebuffForce != 0)
	{
		sprintf(temp, "%d", card.m_iDebuffForce);
		PrintStoryMessage(temp, " 만큼 상대의 Str(힘) (을)를 감소시켰다.");
	}
	if (card.m_iDebuffShield != 0)
	{
		sprintf(temp, "%d", card.m_iDebuffShield);
		PrintStoryMessage(temp, " 만큼 상대의 Shield(방어력) (을)를 감소시켰다.");
	}
	if (card.m_iBuffForce != 0)
	{
		sprintf(temp, "%d", card.m_iBuffForce);
		PrintStoryMessage(temp, " 만큼 Str(힘) (을)를 얻었다.");
	}
	if (card.m_iBuffHP != 0)
	{
		sprintf(temp, "%d", card.m_iBuffHP);
		PrintStoryMessage(temp, " 만큼 HP(체력) (을)를 얻었다");
	}

	player->m_bRender = false;

	return _TRUE;
}

void ShuffleNewCard(CCard* handarr[], CCard* allcard, int cnt, int maxcardcnt)
{
	bool SameNum = false;

	for (int i = 0; i < cnt;)
	{
		int iCnt = rand() % maxcardcnt;

		for (int j = 0; j < cnt; ++j)
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
		handarr[i] = (allcard + arr[i]);
		++i;
	}
}

void AddNewCard(CCard* handarr[], CCard* allcard, int cnt, int maxcardcnt, int curcnt)
{
	int iNowHand = curcnt + cnt;

	if (iNowHand > HANDCARDMAX)
		iNowHand = HANDCARDMAX;

	bool SameNum = false;

	for (int i = curcnt; i < iNowHand;)
	{
		int iCnt = rand() % maxcardcnt;

		for (int j = 0; j < iNowHand; ++j)
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
		handarr[i] = (allcard + arr[i]);
		++i;
	}
}

void PlayerNewTurn(CPlayer* player)
{
	player->m_iForce = player->m_iOriForce;
	player->m_iShield = player->m_iOriShield;
	player->m_iMaxHP = player->m_iOriMaxHp;
	player->m_iCost = player->m_iMaxCost;

	player->m_iHandCard = HANDCOUNT;

	for (int i = 0; i < HANDCARDMAX; ++i)
	{
		arr[i] = -1;
		player->m_bUseCard[i] = false;
	}

	ShuffleNewCard(player->m_HandCard, player->m_pCard, HANDCOUNT, MAXCARDKINDS);

	player->m_bRender = false;
	player->m_bHandChange = true;
	player->m_bChangeCard = true;
}