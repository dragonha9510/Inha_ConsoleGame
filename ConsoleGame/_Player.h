#pragma once

#include "stdafx.h"

typedef struct Card
{
	int iTest;
}CCard;

typedef struct Player
{
	int iTest;
	bool bTest;
	CCard* m_pCard;
}CPlayer;

int InitPlayer()
{
	return _TRUE;
}