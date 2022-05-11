#pragma once

#ifndef __STDAFX_H__
#define __STDAFX_H__

#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#include <vld.h>

extern HANDLE g_CIN = 0;		// console Input
extern HANDLE g_COUT = 0;		// console Output

#define ESCAPE		27
#define LEFT		75
#define RIGHT		77
#define UP			72
#define DOWN		80
#define ARROWKEY	-32
#define ENTER		13
#define SPACE		32

#define _ERROR		-1
#define _EXIT		-2
#define _FALSE		0
#define _TRUE		1
#define _OK			0
#define _FAIL		1

#define IFERROREXIT(t)		if(t == _ERROR) exit(-1);
#define IFERRORRETURN(t)	(t == _ERROR) ? 1 : 0

#define NULLCHECK(t)		if(t == NULL) exit(-1);
#define NULLCHECKRETURN(t)	(t == NULL) ? 1 : 0

#define NULLCHECKFREE(t) if(!NULLCHECKRETURN(t)) free(t); t = NULL;

#define MAXBUFFER	255
#define DOUBLE(t)	t * 2

enum MENU_ENUM { PLAY = 0, LOAD, CHALLENGE, MENUEND , MENU, ENUM_END };

extern char chMessage = '\0';

#include "Card.h"
#include "Console_Func.h"
#include "FileIO.h"
#include "_Player.h"
#include "MainMenu.h"
#include "Dungeon.h"
#include "SaveLoad.h"

#include "Maingame.h"


#endif // __STDAFX_H__
