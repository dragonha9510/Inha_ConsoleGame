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
	CCard* m_pCard;
	CCard* m_pAllCard;

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

	return _TRUE;
}

int PlayerUpdate(CPlayer* player)
{
	return _TRUE;
}

int PlayerLateUpdate(CPlayer* player)
{
	return _TRUE;
}

int PlayerRender(CPlayer* player)
{

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