#include <stdio.h>
#include <stdint.h>
#include <math.h>

#include "RootDirectory.h"

typedef struct
{
	uint8_t part[3];
	uint8_t desc[8];
	uint8_t bytesPerBlock[2];
	uint8_t blockPerAllocUnit[1];
	uint8_t reserveBlock[2];
	uint8_t FATnum[1];
	uint8_t rootNum[2];
	uint8_t blockNum1[2];
	uint8_t mediaDescriptor[1];
	uint8_t FATblocks[2];
	uint8_t blockPerTrack[2];
	uint8_t headNum[2];
	uint8_t hiddenBlockNum[4];
	uint8_t blockNum2[4];
	uint8_t driveNum[2];
	uint8_t recordSignature[1];
	uint8_t volSerialNum[4];
	uint8_t volLabel[11];
	uint8_t identifier[8];
	uint8_t remainder[0x1c0];
	uint8_t bootSignature[2];
} BootBlock;

void main()
{
	BootBlock bootBlock;
	
	FILE *pFile = fopen("floppy.img", "r");
	fseek(pFile, 0x0, SEEK_SET);
	fgets(&bootBlock, sizeof(bootBlock), pFile);
	
	// Calculating starting address of root directory
	uint8_t FATnum = bootBlock.FATnum[0];
	uint32_t rootStart = (ArrFlipToNum(bootBlock.FATblocks, 2) * FATnum + 0x1) * 0x200;
	
	// Calculating starting address of data area
	uint32_t dataStart = (rootStart/0x200) + (ArrFlipToNum(bootBlock.rootNum, 2)*32/512) - 2, clusterAddr;
	
	uint8_t entriesNum = FAT_EntriesCount(pFile, rootStart), i;
	Entries *entriesArr = (Entries*)malloc(entriesNum*32);
	FAT_ReadEntries(pFile, rootStart, entriesNum, entriesArr);
	
	uint8_t userInput;
	do
	{
		for(i=0; i<entriesNum; i++)
		{
			printf("%d ", i+1);
			PrintArray(entriesArr[i].FileName, 8, "%c");
			printf(" ");
			PrintArray(entriesArr[i].FileExtension, 3, "%c");
			printf(" %x\n", FAT_ClusterAddr(dataStart, ArrFlipToNum(entriesArr[i].ClusterNum, 2)));
		}
		
		scanf("%d", &userInput);
		
		if(userInput != 0)
		{
			if(entriesArr[userInput-1].FileAttribute[0] == 0x10)
			{
				// enter sub-folder
				clusterAddr = FAT_ClusterAddr(dataStart, ArrFlipToNum(entriesArr[userInput-1].ClusterNum, 2));
				entriesNum = FAT_EntriesCount(pFile, clusterAddr);
				free(entriesArr);
				Entries *entriesArr = (Entries*)malloc(entriesNum*32);
				FAT_ReadEntries(pFile, clusterAddr, entriesNum, entriesArr);
			}
			else
			{
				printf("This is a file\n");
			}	
		}
	}
	while(userInput != 0);
	
	
}
