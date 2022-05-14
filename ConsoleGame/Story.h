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
	int iRan = rand() % 3;

	switch (storytype)
	{
	case FIGHT:
	case FIGHTEND:
		if (!*end)
		{
			bReturn = FightStory(iRan);
			*end = true;
		}
		break;
	case SHOP:
	case SHOPEND:
		//bReturn = ShopStory(0);
		//break;
	case REST:
	case RESTEND:
		bReturn = RestStory(iRan);
		break;
	case NORMAL:
	case NORMALEND:
		bReturn = NormalStory();
		break;
	case STORYEND:
		return _ENDGAME;
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
	PrintStoryMessage("따듯한 모닥불이 ", "보인다.");
	Sleep(1000);
	PrintStoryMessage("방금까지 다른 사람이 ", "있었던 것 같다.");
	Sleep(1000);
	PrintStoryMessage("하지만 그 흔적은 찾을 수 없다.", " 그저 불을 바라볼 뿐이다.");
	Sleep(1000);

	return false;
}

bool FightStory(int ran)
{
	// 몬스터가 플레이어에게

	switch (ran)
	{
	case 0:
		PrintStoryMessage("몬스터 (을)를", " 마주쳤다.");
		Sleep(1000);
		PrintStoryMessage("칼을 꺼내들며 ", "(NULL) 에게 다가온다.");
		Sleep(1000);
		break;
	case 1:
		PrintStoryMessage("그저 지나가는 짐승이길 ", "바랬건만");
		Sleep(1000);
		PrintStoryMessage("날카로운 송곳니를 들어낸 ", "얼굴이 일글어진 몬스터였다..");
		Sleep(1000);
		break;
	case 2:
		PrintStoryMessage("지쳤다, ", "끊임없이 이어지는 몬스터를 상대하는데에");
		Sleep(1000);
		PrintStoryMessage("(NULL) (은)는 ", "칼을 꺼내들며 몬스터에게 향했다.");
		Sleep(1000);
		break;
	}

	return false;
}

bool NormalStory()
{
	char Temp[MAXBUFFER];

	GetStoryLine(iStoryCnt++, Temp, "NormalStory.txt");

	memset(Temp, 0, sizeof(Temp));

	return false;
}