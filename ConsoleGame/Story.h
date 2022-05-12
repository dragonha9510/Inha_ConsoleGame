#pragma once

#include "stdafx.h"

enum STORYTYPE { STORY, SHOP, EMERGENCE, REST, STORY_END };

typedef struct story
{
	int m_iShopCnt;
	int m_iRestCnt;
	int m_iEmerCnt;
}CStory;

int StoryRender()
{
	return 0;
}