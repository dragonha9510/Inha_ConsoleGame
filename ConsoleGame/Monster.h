#pragma once

#include "stdafx.h"

typedef struct monster
{
	int m_iHP;
	int m_iShield;
	int m_iDmg;
	int m_iGold;
}CMonster;

CMonster* MakeMonster(int hp, int shiled, int dmg, int gold);


CMonster* MakeMonster(int hp, int shiled, int dmg, int gold)
{
	CMonster* pMonster = (CMonster*)malloc(sizeof(CMonster));

	pMonster->m_iHP = hp;
	pMonster->m_iShield = shiled;
	pMonster->m_iDmg = dmg;
	pMonster->m_iGold = gold;

	return pMonster;
}