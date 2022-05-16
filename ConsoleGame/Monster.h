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
FIGHTACT	GetMonsterFightInfo(CMonster* monster);
CMonster*	MakeMonster(int hp, int shield, int dmg, int gold);
void		MonsterInfoRender(CMonster* monster);


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

bool MonsterDeadReturn(CMonster* monster)
{
	if (monster->m_iHP <= 0)
		return true;

	return false;
}

FIGHTACT GetMonsterFightInfo(CMonster* monster)
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
	
	// FIGHT INFO 입력 필요
	pMonster->m_FightInfo.Type = 0;
	pMonster->m_FightInfo.GiveDebuffForce = 0;
	pMonster->m_FightInfo.GiveDebuffShield = 0;
	pMonster->m_FightInfo.GiveDmg = pMonster->m_iDmg;

	return pMonster;
}

#define MONSTERSTATEX 110
#define MONSTERSTATEY 3

void MonsterInfoRender(CMonster* monster)
{
	int monsterPos = MONSTERSTATEY;

	gotoxy(MONSTERSTATEX, monsterPos);
	printf("Monster State");

	gotoxy(MONSTERSTATEX, ++monsterPos);
	printf("Dmg    : %d", monster->m_iDmg);

	gotoxy(MONSTERSTATEX, ++monsterPos);
	printf("Shiled : %d", monster->m_iShield);

	gotoxy(MONSTERSTATEX, ++monsterPos);
	printf("HP     : %d", monster->m_iHP);
}

void MonsterInfoRenderClear()
{
	int monsterPos = MONSTERSTATEY;
	gotoxy(MONSTERSTATEX, monsterPos);
	printf("                ");
	gotoxy(MONSTERSTATEX, ++monsterPos);
	printf("               ");
	gotoxy(MONSTERSTATEX, ++monsterPos);
	printf("               ");
	gotoxy(MONSTERSTATEX, ++monsterPos);
	printf("               ");
}