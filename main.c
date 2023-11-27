#include "FatLib.h"

void main()
{
	FAT_Open("floppy.img");
	
	uint32_t clusterAddr;
	uint8_t entriesNum = FAT_EntriesCountAll(FAT_RootStartAddr()), i, userInput;
	Entries *entriesArr = (Entries*)malloc(entriesNum*32);
	FAT_ReadEntries(FAT_RootStartAddr(), &entriesNum, entriesArr);
	
	do
	{
		for(i=0; i<entriesNum; i++)
		{
			printf("%d\t", i+1);
			PrintArray(entriesArr[i].FileName, 8, "%c");
			printf("\t");
			PrintArray(entriesArr[i].FileExtension, 3, "%c");
			printf("\t%x\n", FAT_ClusterAddr(FAT_DataStartAddr(), ArrFlipToNum(entriesArr[i].ClusterNum, 2)));
		}
		
		scanf("%d", &userInput);
		system("cls");
		
		if(userInput != 0)
		{
			if(entriesArr[userInput-1].FileAttribute[0] == 0x10)
			{
				// enter sub-folder
				clusterAddr = FAT_ClusterAddr(FAT_DataStartAddr(), ArrFlipToNum(entriesArr[userInput-1].ClusterNum, 2));
				entriesNum = FAT_EntriesCountAll(clusterAddr);
				free(entriesArr);
				Entries *entriesArr = (Entries*)malloc(entriesNum*32);
				FAT_ReadEntries(clusterAddr, &entriesNum, entriesArr);
			}
			else
			{
				read_file_content(entriesArr[userInput-1]);
				printf("\n");
			}	
		}
		else
		{
			FAT_Close();
		}
	}
	while(userInput != 0);
	
	
}
