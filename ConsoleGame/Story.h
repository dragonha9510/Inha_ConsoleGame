#pragma once

#include "stdafx.h"

enum STORYTYPE { FIGHT, FIGHTEND, SHOP, SHOPEND, REST, RESTEND, NORMAL, NORMALEND, STORYEND };

typedef struct story
{
	int m_iShopCnt;
	int m_iRestCnt;
	int m_iEmerCnt;
	int m_iNormalCnt;
}CStory;

CStory str = { 0,0,0 };

int StoryRender(int storytype, bool* end);
bool ShopStory(int ran);
bool RestStory(int ran);
bool FightStory(int ran);
bool NormalStory();

int StoryRender(int storytype, bool* end)
{
	bool bReturn = false;

	switch (storytype)
	{
	case FIGHT:
	case FIGHTEND:
		bReturn = FightStory(0);
		break;
	case SHOP:
	case SHOPEND:
		bReturn = ShopStory(0);
		break;
	case REST:
	case RESTEND:
		bReturn = RestStory(0);
		break;
	case NORMAL:
	case NORMALEND:
		bReturn = NormalStory();
		break;
	}

	if (iStoryCnt == MAXSTAGESTORY)
	{
		iStoryCnt = 0;
		return _ENDGAME;
	}

	return bReturn;
}

bool ShopStory(int ran)
{
	PrintStoryMessage("Shop", " story");

	return false;
}

bool RestStory(int ran)
{
	PrintStoryMessage("Rest", " story");

	return false;
}

bool FightStory(int ran)
{
	// 몬스터가 플레이어에게
	PrintStoryMessage("Fight", " story");
	
	return false;
}

bool NormalStory()
{
	char Temp[MAXBUFFER];

	GetStoryLine(iStoryCnt++, Temp, "NormalStory.txt");

	memset(Temp, 0, sizeof(Temp));

	return false;
}