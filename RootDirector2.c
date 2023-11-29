#include "RootDirectory.h"

void FAT_ReadEntries(FILE *pFile, uint32_t startAddr, Entries entriesArr[])
{
	Entries entries;
	uint8_t i=0;
	
	fseek(pFile, startAddr, SEEK_SET);
	while(1)
	{
		fseek(pFile, 0x0b, SEEK_CUR);
		if(fgetc(pFile) != 0x10)
		{
			fseek(pFile, 0x14, SEEK_CUR);
			fgets(&entries, sizeof(entries), pFile);
			
			PrintArray(entries.FileName, 8, "%c");
		}
		else
		{
			fseek(pFile, -0x0c, SEEK_CUR);
			fgets(&entries, sizeof(entries), pFile);
			
			PrintArray(entries.FileName, 8, "%c");
		}
		fseek(pFile, 0x01, SEEK_CUR);
		
		if(ArrToNum(entries.ClusterNum, 2) == 0)
		{
			break;
		}
		else
		{
			entriesArr[i] = entries;
			i++;
		}
	}
}

uint8_t FAT_EntriesCount(FILE *pFile, uint32_t startAddr)
{
	uint8_t count=1, attribute;
	
	fseek(pFile, startAddr, SEEK_SET);
	while(1)
	{
		fseek(pFile, 0x0b, SEEK_CUR);
		attribute = fgetc(pFile);
		if(attribute == 0x00)
		{
			break;
		}
		else if(attribute != 0x10)
		{
			fseek(pFile, 0x33, SEEK_CUR);
			count++;
			
			printf("%x\n", attribute);
		}
		else
		{
			fseek(pFile, 0x13, SEEK_CUR);
			count++;
		}
	}
	
	return count;
}

void ArrFlip(uint8_t input[], uint8_t output[], uint8_t Len)
{
	uint8_t i;
	
	for(i=0; i<Len; i++)
	{
		output[Len-i-1] = input[i];
	}
}

uint32_t ArrToNum(uint8_t input[], uint8_t Len)
{
	uint32_t result = 0;
	uint8_t i;
	
	for(i=0; i<Len; i++)
	{
		result += input[i] * pow(0x10, (Len-i-1)*2);
	}
	
	return result;
}

void PrintArray(uint8_t input[], uint8_t Len, char *type)
{
	uint8_t i;
	for(i=0; i<Len; i++)
	{
		printf(type, input[i]);
	}
	printf("\n");
}
