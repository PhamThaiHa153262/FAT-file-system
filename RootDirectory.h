#ifndef _ROOT_DIRECTORY_H
#define _ROOT_DIRECTORY_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#pragma pack(1)

typedef struct
{
	uint8_t FileName[8];
	uint8_t FileExtension[3];
	uint8_t FileAttribute[1];
	uint8_t Reserved[10];
	uint8_t Time[2];
	uint8_t Date[2];
	uint8_t ClusterNum[2];
	uint8_t FileSize[4];
} Entries;

void FAT_ReadEntries(FILE *pFile, uint32_t startAddr, uint8_t entriesNum, Entries entriesArr[]);
uint8_t FAT_EntriesCount(FILE *pFile, uint32_t startAddr);
uint32_t FAT_ClusterAddr(uint32_t startCluster, uint16_t clusterNum);
void ArrFlip(uint8_t input[], uint8_t output[], uint8_t Len);
uint32_t ArrToNum(uint8_t input[], uint8_t Len);
uint32_t ArrFlipToNum(uint8_t input[], uint8_t Len);
void PrintArray(uint8_t input[], uint8_t Len, char *type);

#endif
