#pragma once

#include "stdafx.h"

#define HANDCARDPOSX		15
#define HANDCARDPOSY		5
#define HANDCARDINTERVAL	25

#define CARDINFOPOSX		7
#define CARDINFOPOSY		34
#define ERASEWITHCURSOR		HANDCARDPOSX - 5

enum CARTTYPE { ATTACK, SHIELD, BUFF, DEBUFF, SHUFFLE, PLUSCOST, CARDTYPE_END };

typedef struct Card
{
	char m_chCardName[MAXBUFFER];
	int m_iCardType;
	int m_iCost;

	//Attack
	int m_iDmg;

	//Shield
	int m_iShield;

	//Buff
	int m_iBuffHP;
	int m_iBuffForce;

	//Debuff
	int m_iDebuffShield;
	int m_iDebuffForce;

	//
	int m_iPercent;

	char m_chCardInfo[MAXBUFFER];
}CCard;

int InitPlayerCard(CCard* playercard, CCard* allcard, int cnt, int MaxCardNum)
{
	int iMaximum = 0;

	for (int i = 0; i < MaxCardNum; ++i)
		iMaximum += (allcard + i)->m_iPercent;

	for (int i = 0; i < cnt; ++i)
	{
		int iCardNum = rand() % iMaximum;
		int iPercent = 0;

		for (int j = 0; j < MaxCardNum; ++j)
		{
			iPercent += (*(allcard + j)).m_iPercent;
			if (iCardNum < iPercent)
			{
				*(playercard + i) = *(allcard + j);
				iPercent = 0;
				break;
			}
		}
	}

	return _TRUE;
}

int PrintCardName(CCard* card[], int cnt, bool arr[])
{
	for (int i = 4; i < 29; ++i)
	{
		gotoxy(ERASEWITHCURSOR, i);
		printf("                                 ");
	}

	for (int i = 0; i < cnt; ++i)
	{
		gotoxy(HANDCARDPOSX, HANDCARDPOSY + ((HANDCARDINTERVAL / cnt) * i));
		if (arr[i])
			textcolor(RED);
		printf("%s (%d)", card[i]->m_chCardName, card[i]->m_iCost);
		if (arr[i])
			textcolor(WHITE);
	}

	return _TRUE;
}

int PrintCardInfo(CCard card)
{
	char chTempInfo[MAXBUFFER];

	strcpy(chTempInfo, card.m_chCardInfo);

	if (card.m_iCardType == ATTACK)
	{
		strcat(chTempInfo, " (으)로 공격한다.");
	}
	else if (card.m_iCardType == SHIELD)
	{
		strcat(chTempInfo, " 만큼 증가한다.");
	}
	gotoxy(CARDINFOPOSX, CARDINFOPOSY);
	printf("                                                                     ");
	gotoxy(CARDINFOPOSX, CARDINFOPOSY);
	printf("%s", chTempInfo);

	return _TRUE;
}