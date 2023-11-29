#include "FatDisplay.h"

void FAT_Display(char *file)
{
	Fat_Status status;
	status = FAT_Open(file);
	
	if(status != FAT_FILE_NOT_FOUND)
	{
		char inputStr[4];
		uint32_t curAddr = FAT_RootStartAddr(), listLen = 0;
		uint8_t entriesNum = FAT_EntriesCountAll(curAddr), i, inFile = 0, inputNum;
		Entries *entriesArr = (Entries*)malloc(entriesNum*32);
		
		List_Create(sizeof(curAddr));
		
		while(1)
		{
			FAT_ReadEntries(curAddr, &entriesNum, entriesArr);
			
			if(inFile == 0)
			{
				FAT_Print_header();
				for(i=0; i<entriesNum; i++)
				{
					printf("%d. ", i+1);
					FAT_Print_List_Files(entriesArr[i]);
				}
			}
			
			printf("\n");
			if(status == FAT_INVALID_INPUT)
			{
				printf("INVALID INPUT, ENTER AGAIN\n");
			}
			
			if(listLen == 0)
			{
				printf("Enter entry number (0 to exit): ");
			}
			else
			{
				printf("Enter entry number (0 to return): ");
			}
			
			fflush(stdin);
			scanf("%s", &inputStr);
			system("cls");
			
			// Input check
			status = InputCheck(inputStr, entriesNum, &inputNum);
			if(status == FAT_INVALID_INPUT)
			{
				continue;
			}
			
			if(inputNum != 0)
			{
				// add current address into list
				List_AddFirst(&curAddr);
				listLen = List_GetLen();
				
				if(entriesArr[inputNum-1].FileAttribute[0] == 0x10)
				{
					// enter sub-folder
					curAddr = FAT_ClusterAddr(FAT_DataStartAddr(), ArrFlipToNum(entriesArr[inputNum-1].ClusterNum, CLUSTER_NUM_SIZE));
					entriesNum = FAT_EntriesCountAll(curAddr);
					free(entriesArr);
					entriesArr = (Entries*)malloc(entriesNum*32);
				}
				else
				{
					// read file
					inFile = 1;
					read_file_content(entriesArr[inputNum-1]);
					printf("\n");
				}
			}
			else
			{
				if(listLen > 0)
				{
					// 0 to return
					inFile = 0;
					List_GetData(&curAddr, 0);
					List_Delete(0);
					listLen = List_GetLen();
					
					entriesNum = FAT_EntriesCountAll(curAddr);
					free(entriesArr);
					entriesArr = (Entries*)malloc(entriesNum*32);
				}
				else
				{
					// 0 to exit
					free(entriesArr);
					FAT_Close();
					printf("Exit program");
					break;
				}
			}
		}
	}
	else
	{
		printf("FILE NOT FOUND");
	}
}

void FAT_Print_header()
{
		// Print header
    printf("   Name                 Type                    Size                    Date                    Time\n");
    printf("------------------------------------------------------------------------------------------------------------\n");
}

void FAT_Print_List_Files(Entries entriesArr)
{

    // Iterate through root directory entries and print information
        PrintArray(entriesArr.FileName, FILE_NAME_SIZE, "%c");  
        
		printf("\t\t");     
		if (entriesArr.FileAttribute[0] == 0x10)
		{
			printf("File Folder");
		}
        else
        {
        	PrintArray(entriesArr.FileExtension, FILE_EXTENSION_SIZE, "%c");
        	printf(" File");
		}
        	
        printf("\t\t");
		if(ArrFlipToNum(entriesArr.FileSize, FILE_SIZE_SIZE) > 0)
        {
        	printf("%d",ArrFlipToNum(entriesArr.FileSize, FILE_SIZE_SIZE));
        	printf(" B");
		}
		
		if(ArrFlipToNum(entriesArr.FileSize, FILE_SIZE_SIZE) > 99999)
        {
       		printf("\t\t");
		}
		else
		{
			printf("\t\t\t");
		}
		printf("%02u/",(ArrFlipToNum(entriesArr.Date, DATE_SIZE)) & 0x1F); 
        printf("%02u/",(ArrFlipToNum(entriesArr.Date, DATE_SIZE) >> 5) & 0x0F);
        printf("%d", ((ArrFlipToNum(entriesArr.Date, DATE_SIZE) >> 9) & 0x7F)+1980  );  
        
        printf("\t\t");
        printf("%02u:",(ArrFlipToNum(entriesArr.Time, TIME_SIZE) >> 11) & 0x1F); 
        printf("%02u:",(ArrFlipToNum(entriesArr.Time, TIME_SIZE) >> 5) & 0x3F); 
		printf("%02u\n", ArrFlipToNum(entriesArr.Time, TIME_SIZE)  & 0x1F); 
}

// Function to read the content of a file
void read_file_content(Entries entry) 
{
    uint32_t cluster_number = ArrFlipToNum(entry.ClusterNum, CLUSTER_NUM_SIZE);
    char buffer[SECTOR_SIZE];
    while (cluster_number < 0xFFF)
    {
    	read_sector(31+cluster_number, buffer);
		
		PrintArray(buffer, SECTOR_SIZE, "%c");
		
		cluster_number = get_next_cluster_number(cluster_number); // Move to the next cluster
    }
}

void PrintArray(uint8_t input[], uint16_t Len, char *type)
{
	uint16_t i;
	for(i=0; i<Len; i++)
	{
		printf(type, input[i]);
	}
}

Fat_Status InputCheck(char *input, uint8_t maxNum, uint8_t *returnNum)
{
	Fat_Status status = FAT_OK;
	uint8_t i=0, len=0;
	
	// check if all character are number and counting
	while(input[i] != 0)
	{
		if((input[i] >= '0' && input[i] <= '9'))
		{
			i++;
			len++;
		}
		else
		{
			len = 0;
			status = FAT_INVALID_INPUT;
			break;
		}
	}
	
	if(status == FAT_OK)
	{
		*returnNum = 0;
		
		// turn arr to number
		for(i=0; i<len; i++)
		{
			*returnNum += (input[i] - '0') * pow(10, (len-i-1));
		}
		
		if(*returnNum > maxNum)
		{
			status = FAT_INVALID_INPUT;
		}
	}
	
	return status;
}
