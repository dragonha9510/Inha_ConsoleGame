#include "stdafx.h"


int main()
{
	system("mode con lines=40 cols=150");
	system("title Slay the Spire");

	g_CIN = GetStdHandle(STD_INPUT_HANDLE);
	g_COUT = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConsoleCursor;
	ConsoleCursor.bVisible = 0;
	ConsoleCursor.dwSize = 1;
	SetConsoleCursorInfo(g_COUT, &ConsoleCursor);
	//
	int iCheckMessage = 0;
	//
	CMainGame* pMain = NULL;
	pMain = (CMainGame*)malloc(sizeof(CMainGame));
	NULLCHECK(pMain);

	memset(pMain, 0, sizeof(CMainGame));
	//

	IFERROREXIT(InitMain(pMain));

	while (true)
	{
		rewind(stdin);
		chMessage = GetKeyInputMessage();

		iCheckMessage = Progress(pMain);

		if (IFERRORRETURN(iCheckMessage))
		{
			system("cls");
			Release(pMain);
			exit(_ERROR);
		}

		if (iCheckMessage == _EXIT)
			break;

		if (chMessage == ESCAPE)
			break;
	}

	system("cls");

	Release(pMain);

	return 0;
}