#pragma once

#include "stdafx.h"

typedef struct Dungeon
{
	int iTest;
}CDungeon;

int DungeonUpdate(CDungeon* dungeon)
{
	if (chMessage == ENTER || chMessage == SPACE)
	{
		return MENU;
	}
	return PLAY;
}

int DungeonLateUpdate()
{
	return _TRUE;
}

int DungeonRender()
{
	system("cls");
	return _TRUE;
}