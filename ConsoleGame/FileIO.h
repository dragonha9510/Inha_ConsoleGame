#pragma once

#include "stdafx.h"

int PrintASCIIImage(const char* filename)
{
	char charr[MAXBUFFER];
	char chFiletag[MAXBUFFER];

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

	while (true)
	{
		fgets(charr, sizeof(charr), fp);

		printf("%s", charr);

		if (feof(fp))
			break;
	}

	fclose(fp);

	return _TRUE;
}

int GetCardInfo(const char* filename, CCard* card)
{
	char charr[MAXBUFFER];
	char chFiletag[MAXBUFFER];

	FILE* fp;

	strcpy(chFiletag, "..\\Data\\");
	strcat(chFiletag, filename);

	fp = (FILE*)fopen(chFiletag, "rb");

	if (NULLCHECKRETURN(fp))
	{
		printf("fopen error.\n");
		return _ERROR;
	}

	int i = 0;

	while (true)
	{
		fgets(charr, sizeof(charr), fp);
		 
		char* ptr = strtok(charr, "/");
		strcpy((card + i)->m_chCardName, ptr);
		
		ptr = strtok(NULL, "/");
		(card + i)->m_iCardType = atoi(ptr);
		
		ptr = strtok(NULL, "/");
		(card + i)->m_iCost = atoi(ptr);

		ptr = strtok(NULL, "/");
		(card + i)->m_iDmg = atoi(ptr);

		ptr = strtok(NULL, "/");
		(card + i)->m_iShield = atoi(ptr);

		ptr = strtok(NULL, "/");
		(card + i)->m_iBuffHP = atoi(ptr);

		ptr = strtok(NULL, "/");
		(card + i)->m_iBuffForce = atoi(ptr);

		ptr = strtok(NULL, "/");
		(card + i)->m_iDebuffShield = atoi(ptr);

		ptr = strtok(NULL, "/");
		(card + i)->m_iDebuffForce = atoi(ptr);

		ptr = strtok(NULL, "/");
		(card + i)->m_iPercent = atoi(ptr); 

		ptr = strtok(NULL, "/");
		strcpy((card + i)->m_chCardInfo, ptr);

		++i;

		if (feof(fp))
			break;
	}

	fclose(fp);

	return _TRUE;
}

int GetStoryLine(int line, char* dest,const char* filename)
{
	char charr[MAXBUFFER];
	char chFiletag[MAXBUFFER];

	FILE* fp;

	strcpy(chFiletag, "..\\Data\\");
	strcat(chFiletag, filename);

	fp = (FILE*)fopen(chFiletag, "rb");

	if (NULLCHECKRETURN(fp))
	{
		printf("fopen error.\n");
		return _ERROR;
	}

	int i = 0;


	while (true)
	{
		if (i == 0 + (line * 3))
		{
			for (int j = 0; j < 3; ++j)
			{
				fgets(charr, sizeof(charr), fp);
				strcpy(dest, charr);
				PrintStoryMessage(dest, "");
				Sleep(1000);
			}
		}
		fgets(charr, sizeof(charr), fp);

		if (feof(fp))
			break;

		++i;
	}

	fclose(fp);

	return _TRUE;

}