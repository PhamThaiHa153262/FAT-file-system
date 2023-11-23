#include "RootDirectory.h"

void FAT_ReadEntries(FILE *pFile, uint32_t startAddr, uint8_t entriesNum, Entries entriesArr[])
{
	Entries entries;
	uint8_t i;
	
	fseek(pFile, startAddr, SEEK_SET);
	for(i=0; i<entriesNum; i++)
	{
		fgets(&entries, sizeof(entries), pFile);
		entriesArr[i] = entries;
		fseek(pFile, 0x01, SEEK_CUR);
	}
}

uint8_t FAT_EntriesCount(FILE *pFile, uint32_t startAddr)
{
	uint8_t count = 0, attribute;
	
	fseek(pFile, startAddr, SEEK_SET);
	while(1)
	{
		if(fgetc(pFile) != 0x00)
		{
			count++;
			fseek(pFile, 31, SEEK_CUR);
		}
		else
		{
			break;
		}
	}
	
	return count;
}

// Calculating address from cluster number
uint32_t FAT_ClusterAddr(uint32_t startCluster, uint16_t clusterNum)
{
	return (startCluster + clusterNum)*0x200;
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

// Flipping array and convert them to number
uint32_t ArrFlipToNum(uint8_t input[], uint8_t Len)
{
	uint32_t result = 0;
	uint8_t i;
	
	for(i=0; i<Len; i++)
	{
		result += input[i] * pow(0x10, i*2);
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
//	printf("\n");
}
