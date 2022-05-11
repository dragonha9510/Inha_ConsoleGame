#pragma once

#include "stdafx.h"

enum CARTTYPE { ATTACK, SHILED, BUFF, DEBUFF, SHUFFLE, PLUSCOST, CARDTYPE_END };

typedef struct Card
{
	char m_chCardName[MAXBUFFER];
	int m_iCardType;
	int m_iCost;

	//Attack
	int m_iDmg;

	//Shiled
	int m_iShiled;

	//Buff
	int m_iBuffHP;
	int m_iBuffForce;

	//Debuff
	int m_iDebuffShiled;
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
				*(playercard + i) = *(allcard + j);
		}
	}

	return _TRUE;
}