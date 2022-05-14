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
	PrintStoryMessage("������ ��ں��� ", "���δ�.");
	Sleep(1000);
	PrintStoryMessage("��ݱ��� �ٸ� ����� ", "�־��� �� ����.");
	Sleep(1000);
	PrintStoryMessage("������ �� ������ ã�� �� ����.", " ���� ���� �ٶ� ���̴�.");
	Sleep(1000);

	return false;
}

bool FightStory(int ran)
{
	// ���Ͱ� �÷��̾��

	switch (ran)
	{
	case 0:
		PrintStoryMessage("���� (��)��", " �����ƴ�.");
		Sleep(1000);
		PrintStoryMessage("Į�� ������� ", "(NULL) ���� �ٰ��´�.");
		Sleep(1000);
		break;
	case 1:
		PrintStoryMessage("���� �������� �����̱� ", "�ٷ��Ǹ�");
		Sleep(1000);
		PrintStoryMessage("��ī�ο� �۰��ϸ� �� ", "���� �ϱ۾��� ���Ϳ���..");
		Sleep(1000);
		break;
	case 2:
		PrintStoryMessage("���ƴ�, ", "���Ӿ��� �̾����� ���͸� ����ϴµ���");
		Sleep(1000);
		PrintStoryMessage("(NULL) (��)�� ", "Į�� ������� ���Ϳ��� ���ߴ�.");
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