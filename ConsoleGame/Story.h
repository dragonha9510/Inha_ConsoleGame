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
		PrintStoryMessage("������ ��ں��� ", "���δ�.");
		Sleep(1000);
		PrintStoryMessage("��ݱ��� �ٸ� ����� ", "�־��� �� ����.");
		Sleep(1000);
		PrintStoryMessage("������ �� ������ ã�� �� ����.", " ���� ���� �ٶ� ���̴�.");
		Sleep(1000);
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		break;
	case 1:
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		PrintStoryMessage("�ƴ��� ���̴� ������ ", "�߰��ߴ�.");
		Sleep(1000);
		PrintStoryMessage("��ó��� �� ��Ӱ� �߿� ������ ", "��� �� �ְڴ�..");
		Sleep(1000);
		PrintStoryMessage("�����ϴ� ", "���� �ۿ��� �帣�� �ٶ��Ҹ����� ����´�.");
		Sleep(1000);
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		break;
	case 2:
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		PrintStoryMessage("������ �갣�� ���δ�.", " ");
		Sleep(1000);
		PrintStoryMessage("�ƹ��� �湮���� �ʾҴ��� ", "�Ź��ٰ� ������ ������ �ݱ��.");
		Sleep(1000);
		PrintStoryMessage("������ ������ ��������, ", "�Ƿ� ����� �˾ƺ� �� ����.");
		Sleep(1000);
		PrintStoryMessage("----- Rest", " -----");
		Sleep(1000);
		break;
	}

	return false;
}

bool FightStory(int ran)
{
	// ���Ͱ� �÷��̾��
	PrintStoryMessage("----- Fight Story", " -----");
	Sleep(1000);

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