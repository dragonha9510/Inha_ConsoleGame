#pragma once

#include "stdafx.h"

enum STORYTYPE { STORY, SHOP, EMERGENCE, REST, STORY_END };

typedef struct story
{
	int m_iShopCnt;
	int m_iRestCnt;
	int m_iEmerCnt;
}CStory;

CStory str = { 0,0,0 };

int StoryRender(int storytype, CPlayer* player, CMonster* monster);
bool ShopStory(int ran);
bool RestStory(int ran);
bool EmerStory(int ran);

int StoryRender(int storytype, CPlayer* player, CMonster* monster)
{
	int iNum = rand() % STORY_END;
	bool bReturn = true;

	switch (storytype)
	{
	case STORY:
		
		break;
	case SHOP:
		++(str.m_iShopCnt);
		str.m_iEmerCnt = 0;
		bReturn = ShopStory(iNum);
		break;
	case REST:
		++(str.m_iRestCnt);
		str.m_iEmerCnt = 0;
		bReturn = RestStory(iNum);
		break;
	case EMERGENCE:
		str.m_iShopCnt = 0;
		str.m_iRestCnt = 0;
		++(str.m_iEmerCnt);
		bReturn = EmerStory(iNum);
		break;
	}

	return bReturn;
}


bool ShopStory(int ran)
{
	return false;
}
bool RestStory(int ran)
{
	return false;
}
bool EmerStory(int ran)
{
	PrintStoryMessage("Test", " (을)를 출력.");

	switch (ran)
	{
	case 0:
		break;
	case 1:
		break;
	case 2:
		break;
	case 3:
		break;
	}
	return true;
}