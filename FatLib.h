#include <stdio.h>
#include <stdint.h>
#include <math.h>

#ifndef _ROOT_DIRECTORY_H
#define _ROOT_DIRECTORY_H

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

#define FILE_NAME_SIZE			8
#define FILE_EXTENSION_SIZE		3
#define FILE_ATTRIBTE_SIZE		1
#define RESERVED_SIZE			10
#define TIME_SIZE				2
#define DATE_SIZE				2
#define CLUSTER_NUM_SIZE		2
#define FILE_SIZE_SIZE			4

typedef struct
{
	uint8_t FileName[FILE_NAME_SIZE];
	uint8_t FileExtension[FILE_EXTENSION_SIZE];
	uint8_t FileAttribute[FILE_ATTRIBTE_SIZE];
	uint8_t Reserved[RESERVED_SIZE];
	uint8_t Time[TIME_SIZE];
	uint8_t Date[DATE_SIZE];
	uint8_t ClusterNum[CLUSTER_NUM_SIZE];
	uint8_t FileSize[FILE_SIZE_SIZE];
} Entries;

typedef enum
{
	FAT_OK				= 0U,
	FAT_FILE_NOT_FOUND	= 1U,
	FAT_INVALID_INPUT	= 3U
}Fat_Status;

Fat_Status FAT_Open(char *fileDir);
void FAT_Close();
void FAT_ReadEntries(uint32_t startAddr, uint8_t *EntriesNum, Entries entriesArr[]);
uint8_t FAT_EntriesCountAll(uint32_t startAddr);
uint32_t FAT_ClusterAddr(uint32_t startCluster, uint16_t clusterNum);
uint16_t FAT_RootStartAddr();
uint16_t FAT_DataStartAddr();
void read_sector(uint32_t sector_number, char *buffer) ;
uint32_t get_next_cluster_number(uint32_t clusterAddr) ;

void ArrFlip(uint8_t input[], uint8_t output[], uint8_t Len);
uint32_t ArrToNum(uint8_t input[], uint8_t Len);
uint32_t ArrFlipToNum(uint8_t input[], uint8_t Len);

#endif
