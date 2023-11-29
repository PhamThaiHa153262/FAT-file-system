#include "FatLib.h"

static BootBlock bootBlock;
static FILE *pFile;
static uint16_t RootStartAddr;
static uint16_t DataStartAddr;

void FAT_Open(char *fileDir)
{
	pFile = fopen(fileDir, "rb");
	fseek(pFile, 0x0, SEEK_SET);
	fgets(&bootBlock, sizeof(bootBlock), pFile);
	
	RootStartAddr = (ArrFlipToNum(bootBlock.FATblocks, 2) * bootBlock.FATnum[0] + 0x1) * 0x200;;
	DataStartAddr = (RootStartAddr/0x200) + (ArrFlipToNum(bootBlock.rootNum, 2)*32/512) - 2;
}

void FAT_Close()
{
	fclose(pFile);
}

void FAT_ReadEntries(uint32_t startAddr, uint8_t *EntriesNum, Entries entriesArr[])
{
	Entries entries;
	uint8_t i, totalEntries = FAT_EntriesCountAll(startAddr);
	*EntriesNum = totalEntries;
	
	fseek(pFile, startAddr, SEEK_SET);
	for(i=0; i<totalEntries; i++)
	{
//		fgets(&entries, sizeof(entries), pFile);
//		entriesArr[i] = entries;
//		fseek(pFile, 0x01, SEEK_CUR);

		fseek(pFile, 0x0b, SEEK_CUR);
		if(fgetc(pFile) == 0x0f) 			// Long file name
		{
			fseek(pFile, 0x14, SEEK_CUR);
			fgets(&entries, sizeof(entries), pFile);
			(*EntriesNum)--;
		}
		else
		{
			fseek(pFile, -0x0c, SEEK_CUR);
			if(fgetc(pFile) == '.')			// Current folder indicator
			{
				fseek(pFile, 0x3f, SEEK_CUR);
				fgets(&entries, sizeof(entries), pFile);
				(*EntriesNum) -= 2;
			}
			else
			{
				fseek(pFile, -0x01, SEEK_CUR);
				fgets(&entries, sizeof(entries), pFile);
			}
		}
		entriesArr[i] = entries;
		fseek(pFile, 0x01, SEEK_CUR);
	}
	
}

uint8_t FAT_EntriesCountAll(uint32_t startAddr)
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

uint8_t FAT_EntriesCount(uint32_t startAddr)
{
	uint8_t count = 0, attribute;
	
	fseek(pFile, startAddr, SEEK_SET);
	
	
	return count;
}

// Calculating address from cluster number
uint32_t FAT_ClusterAddr(uint32_t startCluster, uint16_t clusterNum)
{
	return (startCluster + clusterNum)*0x200;
}

uint16_t FAT_RootStartAddr()
{
	return RootStartAddr;
}

uint16_t FAT_DataStartAddr()
{
	return DataStartAddr;
}

//Function to read a sector from the disk
void read_sector(uint32_t sector_number, uint8_t *buffer) 
{
    fseek(pFile, sector_number * SECTOR_SIZE, SEEK_SET);
    fread(buffer, 1, SECTOR_SIZE, pFile);
}

// Function to get the next cluster number from the FAT
uint32_t get_next_cluster_number(uint32_t current_cluster) 
{
    uint32_t fat_offset = current_cluster + (current_cluster >> 1); // Each entry is 12 bits, so 2 entries per 3 bytes
   // uint32_t fat_sector = 1 + fat_offset / SECTOR_SIZE; // FAT starts from sector 1
    //uint32_t fat_entry_offset = fat_offset % SECTOR_SIZE;
    
    uint8_t buffer[2];
    //read_sector(pfile, 1, buffer);
    fseek(pFile, 1*SECTOR_SIZE + fat_offset, SEEK_SET);
    fgets(buffer,3,pFile);

    // Extract the cluster number based on whether it's an even or odd entry
    if (current_cluster % 2 == 0) 
    {
        return ((buffer[1] & 0xF) << 8) | buffer[0];
    } 
    else
    {
        return (buffer[1] << 4) | ((buffer[0] & 0xF0) >> 4);
    }
}

// Function to read the content of a file
void read_file_content(Entries entry) 
{
    uint32_t cluster_number = ArrFlipToNum(entry.ClusterNum, 2);
    uint8_t buffer[SECTOR_SIZE];
    while (cluster_number != 0xFFF)
    {
    	read_sector(31+cluster_number, buffer);
	  //  printf("\n\n%x\n",cluster_number); // Test cluster_number
		//printf("%.*s", SECTOR_SIZE, buffer);
		
		PrintArray(buffer, SECTOR_SIZE, "%c");
		
		cluster_number = get_next_cluster_number(cluster_number); // Move to the next cluster
	     //printf("%X\n",cluster_number);
//		if(cluster_number == 0x7f)
//		{
//			printf("\n%d\n", 1);
//		}
    }
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

void PrintArray(uint8_t input[], uint16_t Len, char *type)
{
	uint16_t i;
	for(i=0; i<Len; i++)
	{
		printf(type, input[i]);
	}
//	printf("\n");
}
