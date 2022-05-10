#pragma once

#include "stdafx.h"

int PrintASCIIImage(const char* filename)
{
	char charr[255];
	char chFiletag[255];

	FILE* fp;

	strcpy(chFiletag, "..\\Image\\");
	strcat(chFiletag, filename);

	fp = (FILE*)fopen(chFiletag, "rb");

	if (NULLCHECKRETURN(fp))
	{
		printf("fopen error.\n");
		return _ERROR;
	}

	gotoxy(0, 0);

	while (1)
	{
		fgets(charr, sizeof(charr), fp);

		printf("%s", charr);

		if (feof(fp))
			break;
	}

	fclose(fp);

	return _TRUE;
}