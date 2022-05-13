#pragma once

#include "stdafx.h"

typedef struct monster
{
	int m_iHP;
	int m_iShield;
	int m_iDmg;
	int m_iGold;

	FIGHTACT m_FightInfo;
}CMonster;

int			SetFightInfoToMonster(CMonster* monster, FIGHTACT fight);
FIGHTACT	SetMonsterFightInfo(CMonster* monster);
CMonster*	MakeMonster(int hp, int shield, int dmg, int gold);



int SetFightInfoToMonster(CMonster* monster, FIGHTACT fight)
{
	monster->m_iShield = monster->m_iShield < 0 ? 0 : monster->m_iShield - fight.GiveDebuffShield;


	if (monster->m_iShield < fight.GiveDmg)
	{
		monster->m_iHP -= fight.GiveDmg - monster->m_iShield;
		monster->m_iShield = 0;
	}
	else
		monster->m_iShield -= fight.GiveDmg;

	monster->m_iDmg -= fight.GiveDebuffForce;

	return _TRUE;
}

FIGHTACT	SetMonsterFightInfo(CMonster* monster)
{
	FIGHTACT* fightinfo = &(monster->m_FightInfo);

	fightinfo->Type = 0;
	fightinfo->GiveDmg = monster->m_iDmg;

	return *fightinfo;
}

CMonster* MakeMonster(int hp, int shield, int dmg, int gold)
{
	CMonster* pMonster = (CMonster*)malloc(sizeof(CMonster));

	pMonster->m_iHP = hp;
	pMonster->m_iShield = shield;
	pMonster->m_iDmg = dmg;
	pMonster->m_iGold = gold;

	return pMonster;
}