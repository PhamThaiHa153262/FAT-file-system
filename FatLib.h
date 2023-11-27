#ifndef _ROOT_DIRECTORY_H
#define _ROOT_DIRECTORY_H

#include <stdio.h>
#include <stdint.h>
#include <math.h>

#define SECTOR_SIZE 0x200

#pragma pack(1)

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

void FAT_Open(char *fileDir);
void FAT_Close();
void FAT_ReadEntries(uint32_t startAddr, uint8_t *EntriesNum, Entries entriesArr[]);
uint8_t FAT_EntriesCountAll(uint32_t startAddr);
uint32_t FAT_ClusterAddr(uint32_t startCluster, uint16_t clusterNum);
uint16_t FAT_RootStartAddr();
uint16_t FAT_DataStartAddr();
void read_sector(uint32_t sector_number, char *buffer) ;
uint32_t get_next_cluster_number(uint32_t clusterAddr) ;
void read_file_content(Entries entry) ;

void ArrFlip(uint8_t input[], uint8_t output[], uint8_t Len);
uint32_t ArrToNum(uint8_t input[], uint8_t Len);
uint32_t ArrFlipToNum(uint8_t input[], uint8_t Len);
void PrintArray(uint8_t input[], uint16_t Len, char *type);

#endif
