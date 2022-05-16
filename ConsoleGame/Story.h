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
bool ShopStory();
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
		bReturn = ShopStory();
		break;
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

void func(void (*fp)(int), int a)
{
	fp(a);
}

bool ShopStory()
{
	int iSel = 0;
	PrintStoryMessage("----- Shop", " -----");

	void* vp = NULL;

	for (int i = 0; i < 3; ++i)
	{
		iSel = rand() % 4;

		switch (iSel)
		{
		case 0:
			func(AddCard, i + 1);
			break;
		case 1:
			func(AddForce, i + 1);
			break;
		case 2:
			func(AddMaxHP, i + 1);
			break;
		default:
			func(RecoveryHP, i + 1);
			break;
		}

		Sleep(750);
	}
	
	PrintStoryMessage("----- Shop", " -----");
	return false;
}

bool RestStory(int ran)
{
	switch (ran)
	{
	case 0:
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		PrintStoryMessage("따듯한 모닥불이 ", "보인다.");
		Sleep(1000);
		PrintStoryMessage("방금까지 다른 사람이 ", "있었던 것 같다.");
		Sleep(1000);
		PrintStoryMessage("하지만 그 흔적은 찾을 수 없다.", " 그저 불을 바라볼 뿐이다.");
		Sleep(1000);
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		break;
	case 1:
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		PrintStoryMessage("아늑해 보이는 동굴을 ", "발견했다.");
		Sleep(1000);
		PrintStoryMessage("잠시나마 이 어둡고 추운 곳에서 ", "벗어날 수 있겠다..");
		Sleep(1000);
		PrintStoryMessage("조용하다 ", "동굴 밖에서 흐르는 바람소리만이 들려온다.");
		Sleep(1000);
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		break;
	case 2:
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		PrintStoryMessage("버려진 헛간이 보인다.", " ");
		Sleep(1000);
		PrintStoryMessage("아무도 방문하지 않았는지 ", "거미줄과 쾌쾌한 먼지가 반긴다.");
		Sleep(1000);
		PrintStoryMessage("버려진 사진이 보였지만, ", "피로 얼룩져 알아볼 수 없다.");
		Sleep(1000);
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		break;
	}

	return false;
}

bool FightStory(int ran)
{
	// 몬스터가 플레이어에게
	PrintStoryMessage("----- Fight Story", " -----");
	Sleep(1000);

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

	PrintStoryMessage("----- Fight", " -----");
	Sleep(1000);

	return false;
}

bool NormalStory()
{
	char Temp[MAXBUFFER];

	PrintStoryMessage("----- Story", " -----");
	Sleep(1000);

	GetStoryLine(iStoryCnt++, Temp, "NormalStory.txt");

	memset(Temp, 0, sizeof(Temp));

	PrintStoryMessage("----- Story", " -----");
	Sleep(1000);

	return false;
}